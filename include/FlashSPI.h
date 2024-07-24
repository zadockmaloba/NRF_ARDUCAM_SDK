#ifndef __FLASH_SPI_H
#define __FLASH_SPI_H

#include <stdint.h>
#include <nrf_delay.h>
#include <nrf_gpio.h>
#include <nrf_drv_spi.h>
#include <nrfx_spim.h>

#define FLASH_SPIM_INSTANCE  1 /**< SPIM instance index. */
static const nrfx_spim_t flash_spim = NRFX_SPIM_INSTANCE(FLASH_SPIM_INSTANCE); /**< SPIM instance. */

typedef uint8_t command_t;

#define SPI_SUCCESS 0

static volatile bool flash_spim_xfer_done; /**< Flag used to indicate that SPIM instance completed the transfer. */

#define FLASH_SPIM_MISO_PIN  NRF_GPIO_PIN_MAP(0,21)  /**< SPIM MISO signal. */
#define FLASH_SPIM_MOSI_PIN  NRF_GPIO_PIN_MAP(0,20)   /**< SPIM MOSI signal. */
#define FLASH_SPIM_SCK_PIN   NRF_GPIO_PIN_MAP(0,19)   /**< SPIM SCK signal. */
#define FLASH_SPIM_SS_PIN    NRF_GPIO_PIN_MAP(0,17)  /**< SPIM CS signal. */
#define FLASH_WP_PIN         NRF_GPIO_PIN_MAP(0,22)  /**< Write protect pin. */
#define FLASH_HOLD_PIN       NRF_GPIO_PIN_MAP(0,23)

void flashSPIBegin();
void flashSPIEnd();

void flashSPIRead(uint32_t address, uint8_t* buffer, size_t length);
void flashSPIWrite(uint32_t address, uint8_t* data, size_t length);

uint32_t flashSPIReadCommand(command_t command, uint8_t *rxBuf, uint32_t len);
uint32_t flashSPIWriteCommand(command_t command, uint8_t *txBuf, uint32_t len);


#endif //__FLASH_SPI_H