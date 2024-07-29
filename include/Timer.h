#ifndef __ARDUCAM_TIMER_H
#define __ARDUCAM_TIMER_H

#include <nrf.h>
#include <nrf_drv_timer.h>

static const nrf_drv_timer_t TIMER_INSTANCE = NRF_DRV_TIMER_INSTANCE(0);

void timer_init(void);
uint32_t get_elapsed_time_us(void);
uint32_t get_elapsed_time_ms(void);

void startTimer(void);
uint32_t stopTimer(void);

uint32_t millis(void);

// Function to reset the millis counter
void resetMillis(void);

#endif //__ARDUCAM_TIMER_H