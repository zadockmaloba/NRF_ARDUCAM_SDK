#ifndef __GPIO_HANDLER_H
#define __GPIO_HANDLER_H

#include <stdbool.h>
#include <nrf.h>
#include <boards.h>

#ifdef BSP_BUTTON_0
    #define PIN_IN BSP_BUTTON_0
#endif
#ifndef PIN_IN
    #error "Please indicate input pin"
#endif

typedef void (*gpio_interrupt_callback_t)(void); 

void set_button0_callback(gpio_interrupt_callback_t callback);

void gpio_handler_init(void);

#endif //__GPIO_HANDLER_H