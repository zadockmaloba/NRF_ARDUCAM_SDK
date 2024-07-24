#include "FlashSPI.h"
#include <nrfx_spim.h>
#include <nrf_drv_spi.h>
#include <nrf_gpio.h>

/**
 * @brief SPIM user event handler.
 * @param event
 */
static void spim_event_handler(nrfx_spim_evt_t const * p_event, void * p_context);

static void spim_init(void);

void flashSPIBegin() {
    spim_init();
}


void spim_event_handler(nrfx_spim_evt_t const * p_event, void * p_context)
{
    spim_xfer_done = true;
}

void spim_init(void)
{
    nrfx_spim_config_t spim_config = NRFX_SPIM_DEFAULT_CONFIG;
    spim_config.ss_pin   = NRFX_SPIM_PIN_NOT_USED;
    spim_config.miso_pin = FLASH_SPIM_MISO_PIN;
    spim_config.mosi_pin = FLASH_SPIM_MOSI_PIN;
    spim_config.sck_pin  = FLASH_SPIM_SCK_PIN;
    spim_config.frequency = NRF_SPIM_FREQ_4M;
    spim_config.bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST;

    nrfx_spim_init(&flash_spim, &spim_config, spim_event_handler, NULL);

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