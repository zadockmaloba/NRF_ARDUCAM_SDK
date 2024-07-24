
/*
 * This file is part of the Arducam SPI Camera project.
 *
 * Copyright 2021 Arducam Technology co., Ltd. All Rights Reserved.
 *
 * This work is licensed under the MIT license, see the file LICENSE for
 * details.
 * 
 * 
 * Note: Modified for NRF52840 - Zadock
 *
 */

#include "ArducamSpi.h"

/**
 * @brief SPIM user event handler.
 * @param event
 */
static void spim_event_handler(nrfx_spim_evt_t const * p_event, void * p_context);

static void spim_init(void);

uint8_t spim_data_transfer(uint8_t data);

void spim_block_transfer(uint8_t *buff,uint16_t len);

///

void arducamSpiBegin(void)
{
    spim_init();
}

uint8_t arducamSpiTransfer(uint8_t data)
{
    return spim_data_transfer(data);
}

void arducamSpiTransferBlock(uint8_t *buff,uint16_t len) {
    spim_block_transfer(buff,len);
}


void spim_event_handler(nrfx_spim_evt_t const * p_event, void * p_context)
{
    spim_xfer_done = true;
}

void spim_init(void)
{
    nrfx_spim_config_t spim_config = NRFX_SPIM_DEFAULT_CONFIG;
    spim_config.ss_pin   = NRFX_SPIM_PIN_NOT_USED;
    spim_config.miso_pin = SPIM_MISO_PIN;
    spim_config.mosi_pin = SPIM_MOSI_PIN;
    spim_config.sck_pin  = SPIM_SCK_PIN;
    spim_config.frequency = NRF_SPIM_FREQ_8M;
    spim_config.bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST;

    nrfx_spim_init(&spim, &spim_config, spim_event_handler, NULL);

    nrf_gpio_cfg(
      SPIM_SCK_PIN,
      NRF_GPIO_PIN_DIR_OUTPUT,
      NRF_GPIO_PIN_INPUT_DISCONNECT,
      NRF_GPIO_PIN_PULLDOWN,
      NRF_GPIO_PIN_S0H1,
      NRF_GPIO_PIN_NOSENSE);

    nrf_gpio_cfg(
      SPIM_SS_PIN,
      NRF_GPIO_PIN_DIR_OUTPUT,
      NRF_GPIO_PIN_INPUT_DISCONNECT,
      NRF_GPIO_PIN_PULLDOWN,
      NRF_GPIO_PIN_S0H1,
      NRF_GPIO_PIN_NOSENSE);

    nrf_gpio_cfg(
      SPIM_MISO_PIN,
      NRF_GPIO_PIN_DIR_INPUT,
      NRF_GPIO_PIN_INPUT_CONNECT,
      NRF_GPIO_PIN_NOPULL,
      NRF_GPIO_PIN_S0H1,
      NRF_GPIO_PIN_NOSENSE);

      //NRF_P0->PIN_CNF[SPIM_SS_PIN] |= (NRF_GPIO_PIN_H0H1 << GPIO_PIN_CNF_DRIVE_Pos);
}

uint8_t spim_data_transfer(uint8_t data)
{
    uint8_t rx_buf;
    uint8_t tx_buf = data;

    spim_xfer_done = false;
    nrfx_spim_xfer_desc_t xfer = NRFX_SPIM_XFER_TRX(&tx_buf, 1, &rx_buf, 1);
    nrfx_spim_xfer(&spim, &xfer, 0);

    while (!spim_xfer_done)
    {
        __WFE();
    }

    return rx_buf;
}

//Read a specific length of data
//TODO: Verify if this works accordingly
void spim_block_transfer(uint8_t *buff,uint16_t len) 
{
    uint8_t tx_buf = 0x00;

    spim_xfer_done = false;
    nrfx_spim_xfer_desc_t xfer = NRFX_SPIM_XFER_TRX(&tx_buf, len, buff, len);
    nrfx_spim_xfer(&spim, &xfer, 0);

    while (!spim_xfer_done)
    {
        __WFE();
    }
}