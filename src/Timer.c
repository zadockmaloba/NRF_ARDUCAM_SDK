#include "Timer.h"

#include <app_timer.h>
#include <nrf_drv_rtc.h>
#include <nrf_drv_clock.h>

static volatile uint32_t tick_counts = 0;
static volatile uint32_t tick_start = 0;
static volatile uint32_t millisOffset = 0;

#define COMPARE_COUNTERTIME  (3UL)                                        /**< Get Compare event COMPARE_TIME seconds after the counter starts from 0. */

const nrf_drv_rtc_t rtc = NRF_DRV_RTC_INSTANCE(0); /**< Declaring an instance of nrf_drv_rtc for RTC0. */

static void rtc_handler(nrf_drv_rtc_int_type_t int_type)
{
    if (int_type == NRF_DRV_RTC_INT_COMPARE0)
    {
        //nrf_gpio_pin_toggle(COMPARE_EVENT_OUTPUT);
    }
    else if (int_type == NRF_DRV_RTC_INT_TICK)
    {
       tick_counts += 1;
    }
}

/** @brief Function starting the internal LFCLK XTAL oscillator.
 */
static void lfclk_config(void)
{
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request(NULL);
}

/** @brief Function initialization and configuration of RTC driver instance.
 */
static void rtc_config(void)
{
    uint32_t err_code;

    //Initialize RTC instance
    nrf_drv_rtc_config_t config = NRF_DRV_RTC_DEFAULT_CONFIG;
    //config.prescaler = 4095;
    err_code = nrf_drv_rtc_init(&rtc, &config, rtc_handler);
    APP_ERROR_CHECK(err_code);

    //Enable tick event & interrupt
    nrf_drv_rtc_tick_enable(&rtc,true);

    //Set compare channel to trigger interrupt after COMPARE_COUNTERTIME seconds
    err_code = nrf_drv_rtc_cc_set(&rtc,0, COMPARE_COUNTERTIME * 8,true);
    APP_ERROR_CHECK(err_code);

    //Power on RTC instance
    nrf_drv_rtc_enable(&rtc);
}

static void timer_handler(nrf_timer_event_t event_type, void* p_context) {
    // Do nothing
}

void timer_init(void) {
    lfclk_config();
    rtc_config();
    //uint32_t err_code = NRF_SUCCESS;
    //nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    //timer_cfg.frequency = NRF_TIMER_FREQ_16MHz;
    //err_code = nrf_drv_timer_init(&TIMER_INSTANCE, &timer_cfg, timer_handler);
    //APP_ERROR_CHECK(err_code);
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
    uint32_t elapsed_time = get_elapsed_time_us();
    nrf_drv_timer_disable(&TIMER_INSTANCE);

    return elapsed_time;
}

uint32_t millis(void){
  //return(app_timer_cnt_get() / 32.768);
  uint32_t currentTicks = tick_counts;//app_timer_cnt_get();
  uint32_t currentMillis = currentTicks / 32.768;
  // Subtract the offset value to reset the millis counter
  currentMillis -= millisOffset;
  return currentMillis;
}

void resetMillis(void)
{
  uint32_t currentMillis = millis();
  // Calculate the offset value by subtracting the current millis value
  millisOffset += currentMillis;
}
