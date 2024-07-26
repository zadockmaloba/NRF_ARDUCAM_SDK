#ifndef __ARDUCAM_CONFIG_H
#define __ARDUCAM_CONFIG_H

#include <stdbool.h>
#include <nrf.h>
#include <ArducamCamera.h>

struct arducam_config_t {
    uint8_t 
    mode = 0,
    format = 0,
    whitebalance = 0,
    fx = 0,
    sharpness = 0;
};

static struct arducam_config_t globalCameraConfig;

void tui_configure_camera(ArducamCamera *camera);

#endif //__ARDUCAM_CONFIG_H