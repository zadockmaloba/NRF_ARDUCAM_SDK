#include "GpioHandler.h"

#include <nrf_gpio.h>
#include <nrfx_gpiote.h>
#include <nrf_drv_gpiote.h>

static gpio_interrupt_callback_t button0_callback = NULL;

static void gpio_button0_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action) 
{
    if(button0_callback != NULL) button0_callback();
}

void set_button0_callback(gpio_interrupt_callback_t callback) {
    button0_callback = callback;
}

void gpio_handler_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(false);

    err_code = nrf_drv_gpiote_out_init(PIN_OUT, &out_config);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    in_config.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(PIN_IN, &in_config, in_pin_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_event_enable(PIN_IN, true);
}