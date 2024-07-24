#include "FlashSPI.h"
#include <nrfx_spim.h>
#include <nrf_drv_spi.h>
#include <nrf_gpio.h>
#include "debug.h"

/**
 * @brief SPIM user event handler.
 * @param event
 */
static void spim_event_handler(nrfx_spim_evt_t const * p_event, void * p_context);

static void spim_init(void);

void flashSPIBegin() 
{
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

uint32_t flashSPIRead(command_t command, uint8_t *rxBuf, uint32_t len)
{
	uint32_t ret = 0;
	uint32_t retryCount=0;
	uint8_t txBuf[3] = {0};
	txBuf[0] = command;

#if SPI_EVENTS_ENABLED == 1
	spiTrCompleteFlag = false;
#endif

    nrf_gpio_pin_clear(FLASH_SPIM_SS_PIN);
	// nrf_delay_us(20);
//		print(LL_ERROR, "SPI tx \n");
	ret = nrf_drv_spi_transfer(&flash_spim, txBuf, sizeof(command_t)+len, rxBuf, len +  sizeof(command_t));
	if(ret != NRF_SUCCESS)
	{
		//print(LL_ERROR, "SPI tx failed\n");
		goto end;
	}

#if SPI_EVENTS_ENABLED == 1
	while (!spiTrCompleteFlag)
	{
		retryCount++;
		if (retryCount >= SPI_RD_WR_RETRY_COUNT)
		{
			ret = NRF_ERROR_TIMEOUT;
			goto end;
		}
	}
#endif

end:

#if SPI_EVENTS_ENABLED == 1
	spiTrCompleteFlag = false;
#endif

    nrf_gpio_pin_set(FLASH_SPIM_SS_PIN);
    if (ret != NRF_SUCCESS)
    {
        //EXCEPTION(ret);
    }
	return ret;
}

uint32_t flashSPIWrite(command_t command, uint8_t *txBuf, uint32_t len)
{
	uint32_t ret = SPI_SUCCESS;
	uint32_t retryCount=0;
	int i = 0;
	//uint8_t *transferBuf = NULL;
	static uint8_t transferBuf[80] = {0};

  nrf_gpio_pin_clear(FLASH_SPIM_SS_PIN);
	nrf_delay_us(20);
	memcpy(transferBuf, &command, sizeof(command_t));
	memcpy(transferBuf + sizeof(command_t), txBuf, len);

#if SPI_EVENTS_ENABLED == 1
	spiTrCompleteFlag = false;
#endif

	ret = nrf_drv_spi_transfer(&flash_spim, transferBuf, len + sizeof(command_t), NULL, 0);
	if(ret != NRF_SUCCESS)
	{
		print(LL_ERROR, "SPI tx failed\n");
		goto end;
	}
	
#if SPI_EVENTS_ENABLED == 1
	while (!spiTrCompleteFlag)
	{
		retryCount++;
		if (retryCount >= SPI_RD_WR_RETRY_COUNT)
		{
			ret = NRF_ERROR_TIMEOUT;
			goto end;
		}
	}
#endif


end:

#if SPI_EVENTS_ENABLED == 1
	spiTrCompleteFlag = false;
#endif

    print(LL_INFO, " EEEENNNNNDDDDD SPI tx failed\n");
//	nrf_delay_ms(250);
//	free(transferBuf);
    nrf_gpio_pin_set(FLASH_SPIM_SS_PIN);
    if (ret != NRF_SUCCESS)
    {
        //EXCEPTION(ret);
    }
	return ret;
}