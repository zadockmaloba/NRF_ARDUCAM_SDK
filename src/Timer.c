#include "Timer.h"

static void timer_handler(nrf_timer_event_t event_type, void* p_context) {
    // Do nothing
}

void timer_init(void) {
    uint32_t err_code = NRF_SUCCESS;
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    err_code = nrf_drv_timer_init(&TIMER_INSTANCE, &timer_cfg, timer_handler);
    APP_ERROR_CHECK(err_code);
}

uint32_t get_elapsed_time_us(void) {
    return nrf_drv_timer_capture_get(&TIMER_INSTANCE, NRF_TIMER_CC_CHANNEL0);
}

uint32_t get_elapsed_time_ms(void) {
    uint32_t elapsed_us = nrf_drv_timer_capture_get(&TIMER_INSTANCE, NRF_TIMER_CC_CHANNEL0);
    return elapsed_us / 1000;  // Convert microseconds to milliseconds
}

void startTimer(void) {
    nrf_drv_timer_enable(&TIMER_INSTANCE);

    // Start the timer
    nrf_drv_timer_clear(&TIMER_INSTANCE);
}
uint32_t stopTimer(void) {
    // Stop the timer and calculate the elapsed time
    uint32_t elapsed_time = get_elapsed_time_ms();
    nrf_drv_timer_disable(&TIMER_INSTANCE);

    return elapsed_time;
}