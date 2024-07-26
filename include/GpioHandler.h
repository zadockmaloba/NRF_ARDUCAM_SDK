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

#ifdef BSP_BUTTON_1
    #define PIN_IN_2 BSP_BUTTON_1
#endif
#ifndef PIN_IN
    #error "Please indicate input pin"
#endif

typedef void (*gpio_interrupt_callback_t)(void); 

void set_button1_callback(gpio_interrupt_callback_t callback);

void set_button2_callback(gpio_interrupt_callback_t callback);

void gpio_handler_init(void);

#endif //__GPIO_HANDLER_H