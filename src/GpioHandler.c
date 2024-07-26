#include "GpioHandler.h"

#include <nrf_gpio.h>
#include <nrf_delay.h>
#include <nrfx_gpiote.h>
#include <nrf_drv_gpiote.h>

static gpio_interrupt_callback_t button1_callback = NULL;
static gpio_interrupt_callback_t button2_callback = NULL;

//-------------------------
static void gpio_button1_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action) 
{
    if(button1_callback != NULL) button1_callback();
}

static void gpio_button2_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action) 
{
    if(button2_callback != NULL) button2_callback();
}

//-------------------------
void set_button1_callback(gpio_interrupt_callback_t callback) {
    button1_callback = callback;
}

void set_button2_callback(gpio_interrupt_callback_t callback) {
    button2_callback = callback;
}

void gpio_handler_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
    in_config.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(PIN_IN, &in_config, gpio_button1_handler);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_gpiote_in_init(PIN_IN_2, &in_config, gpio_button2_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_event_enable(PIN_IN, true);
    nrf_drv_gpiote_in_event_enable(PIN_IN_2, true);
}