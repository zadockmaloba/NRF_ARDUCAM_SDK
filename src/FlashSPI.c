#include <nrfx_spim.h>
#include <nrf_drv_spi.h>
#include <nrf_gpio.h>
#include <string.h>

#include "FlashSPI.h"
#include "debug.h"

#define FLASH_CMD_WRITE_ENABLE  0x06
#define FLASH_CMD_WRITE         0x02
#define FLASH_CMD_READ          0x03
#define FLASH_CMD_READ_STATUS   0x05
#define FLASH_CMD_WRITE_DISABLE 0x04

void flash_write_enable();
void flash_write(uint32_t address, uint8_t* data, size_t length);
bool flash_is_busy();
void flash_read(uint32_t address, uint8_t* buffer, size_t length);

static void flash_spim_event_handler(nrfx_spim_evt_t const * p_event, void * p_context);
static void flash_spim_init(void);

void flashSPIBegin(void) 
{
  flash_spim_init();

  nrf_gpio_pin_set(FLASH_SPIM_SS_PIN);

  flash_write_enable();
}

void flashSPIEnd(void)
{
  nrfx_spim_uninit(&flash_spim);
}

void flashSPIRead(uint32_t address, uint8_t* buffer, size_t length)
{
  flash_read(address, buffer, length);
}

void flashSPIWrite(uint32_t address, uint8_t* data, size_t length)
{
  flash_write(address, data, length);
}

void flash_spim_event_handler(nrfx_spim_evt_t const * p_event, void * p_context)
{
    flash_spim_xfer_done = true;
}

void flash_spim_init(void)
{
    nrfx_spim_config_t spim_config = NRFX_SPIM_DEFAULT_CONFIG;
    spim_config.ss_pin   = NRFX_SPIM_PIN_NOT_USED;
    spim_config.miso_pin = FLASH_SPIM_MISO_PIN;
    spim_config.mosi_pin = FLASH_SPIM_MOSI_PIN;
    spim_config.sck_pin  = FLASH_SPIM_SCK_PIN;
    spim_config.frequency = NRF_SPIM_FREQ_8M;
    spim_config.bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST;

    nrfx_spim_init(&flash_spim, &spim_config, flash_spim_event_handler, NULL);

    nrf_gpio_cfg(
      FLASH_SPIM_SCK_PIN,
      NRF_GPIO_PIN_DIR_OUTPUT,
      NRF_GPIO_PIN_INPUT_DISCONNECT,
      NRF_GPIO_PIN_PULLDOWN,
      NRF_GPIO_PIN_S0H1,
      NRF_GPIO_PIN_NOSENSE);

    nrf_gpio_cfg(
      FLASH_SPIM_SS_PIN,
      NRF_GPIO_PIN_DIR_OUTPUT,
      NRF_GPIO_PIN_INPUT_DISCONNECT,
      NRF_GPIO_PIN_PULLDOWN,
      NRF_GPIO_PIN_S0H1,
      NRF_GPIO_PIN_NOSENSE);

    nrf_gpio_cfg(
      FLASH_SPIM_MISO_PIN,
      NRF_GPIO_PIN_DIR_INPUT,
      NRF_GPIO_PIN_INPUT_CONNECT,
      NRF_GPIO_PIN_NOPULL,
      NRF_GPIO_PIN_S0H1,
      NRF_GPIO_PIN_NOSENSE);

      //NRF_P0->PIN_CNF[SPIM_SS_PIN] |= (NRF_GPIO_PIN_H0H1 << GPIO_PIN_CNF_DRIVE_Pos);
}

uint8_t flashSPITransfer(uint8_t data) {
  uint8_t rx_buf;
  uint8_t tx_buf = data;

  flash_spim_xfer_done = false;
  nrfx_spim_xfer_desc_t xfer = NRFX_SPIM_XFER_TRX(&tx_buf, 1, &rx_buf, 1);
  nrfx_spim_xfer(&flash_spim, &xfer, 0);

  while (!flash_spim_xfer_done)
  {
      __WFE();
  }

  return rx_buf;
}

void flash_write_enable() {
    uint8_t cmd = FLASH_CMD_WRITE_ENABLE;
    nrf_gpio_pin_clear(FLASH_SPIM_SS_PIN);
    nrf_delay_us(20);

    nrfx_spim_xfer_desc_t xfer_desc = NRFX_SPIM_XFER_TX(&cmd, 1);
    nrfx_spim_xfer(&flash_spim, &xfer_desc, 0);

    while (!flash_spim_xfer_done)
    {
        __WFE();
    }

    nrf_gpio_pin_set(FLASH_SPIM_SS_PIN);
}

void flash_write(uint32_t address, uint8_t* data, size_t length) {
    uint8_t tx_buf[4096];
    tx_buf[0] = FLASH_CMD_WRITE;
    tx_buf[1] = (address >> 16) & 0xFF;
    tx_buf[2] = (address >> 8) & 0xFF;
    tx_buf[3] = address & 0xFF;
    memcpy(&tx_buf[4], data, length);

    flash_write_enable();

    nrf_gpio_pin_clear(FLASH_SPIM_SS_PIN);
    nrf_delay_us(20);

    nrfx_spim_xfer_desc_t xfer_desc = NRFX_SPIM_XFER_TX(tx_buf,4096);
    nrfx_spim_xfer(&flash_spim, &xfer_desc, 0);

    flash_spim_xfer_done = false;

    while (!flash_spim_xfer_done)
    {
        __WFE();
    }

    // Wait for the write to complete
    //while (flash_is_busy()) { }

    nrf_gpio_pin_set(FLASH_SPIM_SS_PIN);
}

bool flash_is_busy() {
    uint8_t cmd = FLASH_CMD_READ_STATUS;
    uint8_t status;

    nrf_gpio_pin_clear(FLASH_SPIM_SS_PIN);
    nrf_delay_us(20);

    nrfx_spim_xfer_desc_t xfer_desc = NRFX_SPIM_XFER_TRX(&cmd, 1, &status, 1);
    nrfx_spim_xfer(&flash_spim, &xfer_desc, 0);

    flash_spim_xfer_done = false;

    while (!flash_spim_xfer_done)
    {
        __WFE();
    }

    nrf_gpio_pin_set(FLASH_SPIM_SS_PIN);

    return status & 0x01;
}

void flash_read(uint32_t address, uint8_t* buffer, size_t length) {
    uint8_t cmd[4];
    cmd[0] = FLASH_CMD_READ;
    cmd[1] = (address >> 16) & 0xFF;
    cmd[2] = (address >> 8) & 0xFF;
    cmd[3] = address & 0xFF;

    nrf_gpio_pin_clear(FLASH_SPIM_SS_PIN);
    nrf_delay_us(20);

    nrfx_spim_xfer_desc_t xfer_desc = NRFX_SPIM_XFER_TRX(cmd, 4, buffer, length);
    nrfx_spim_xfer(&flash_spim, &xfer_desc, 0);

    flash_spim_xfer_done = false;

    while (!flash_spim_xfer_done)
    {
        __WFE();
    }

    nrf_gpio_pin_set(FLASH_SPIM_SS_PIN);
}