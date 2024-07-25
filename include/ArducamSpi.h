
/*
 * This file is part of the Arducam SPI Camera project.
 *
 * Copyright 2021 Arducam Technology co., Ltd. All Rights Reserved.
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 */

#ifndef __ARDUCAMSPI_H
#define __ARDUCAMSPI_H

#include "stdint.h"
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrf_delay.h>
#include <nrf_drv_spi.h>
#include <nrfx_spim.h>

#define SPIM_INSTANCE  0 /**< SPIM instance index. */
static const nrfx_spim_t spim = NRFX_SPIM_INSTANCE(SPIM_INSTANCE); /**< SPIM instance. */

static volatile bool spim_xfer_done; /**< Flag used to indicate that SPIM instance completed the transfer. */

#define SPIM_MISO_PIN  NRF_GPIO_PIN_MAP(0,25)  /**< SPIM MISO signal. */
#define SPIM_MOSI_PIN  NRF_GPIO_PIN_MAP(0,26)   /**< SPIM MOSI signal. */
#define SPIM_SCK_PIN   NRF_GPIO_PIN_MAP(0,27)   /**< SPIM SCK signal. */
#define SPIM_SS_PIN    NRF_GPIO_PIN_MAP(1,8)  /**< SPIM CS signal. */

#ifdef __cplusplus
extern "C" {
#endif

void arducamSpiBegin(void);
void arducamSpiUninit(void);
uint8_t arducamSpiTransfer(uint8_t);
// void arducamSpiCsOutputMode(int);
// void arducamSpiCsHigh(int);
// void arducamSpiCsLow(int);
void arducamSpiTransferBlock(uint8_t*,uint16_t);
#ifdef __cplusplus
}
#endif

#endif /*__ARDUCAMSPI_H*/
