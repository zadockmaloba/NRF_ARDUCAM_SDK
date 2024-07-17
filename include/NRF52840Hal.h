#ifndef DE716617_F52C_40FC_BF39_32819E00751D
#define DE716617_F52C_40FC_BF39_32819E00751D

#include "ArducamSpi.h"
#include <nrf_delay.h>
#include <nrf_gpio.h>

#define arducamSpiBegin()                 arducamSpiBegin()
#define arducamSpiTransfer(val)           arducamSpiTransfer(val) //  SPI communication sends a byte
#define arducamSpiReadBlock(p_val, count) arducamSpiTransferBlock(p_val, count)
#define arducamSpiCsPinHigh(pin)          nrf_gpio_pin_set(pin) // Set the CS pin of SPI to high level
#define arducamSpiCsPinLow(pin)           nrf_gpio_pin_clear(pin)  // Set the CS pin of SPI to low level
#define arducamCsOutputMode(pin)          nrf_gpio_cfg( \
                                            pin, \
                                            NRF_GPIO_PIN_DIR_OUTPUT, \
                                            NRF_GPIO_PIN_INPUT_DISCONNECT, \
                                            NRF_GPIO_PIN_PULLDOWN, \
                                            NRF_GPIO_PIN_S0H1, \
                                            NRF_GPIO_PIN_NOSENSE)

#define arducamDelayMs(val)               nrf_delay_ms(val) //  Delay Ms
#define arducamDelayUs(val)               nrf_delay_us(val) // Delay Us

#endif /*__ARDUINOHAL_H*/

#endif /* DE716617_F52C_40FC_BF39_32819E00751D */
