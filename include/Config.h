#ifndef __ARDUCAM_CONFIG_H
#define __ARDUCAM_CONFIG_H

#include <stdbool.h>
#include <nrf.h>
#include <ArducamCamera.h>

struct arducam_config_t {
    uint8_t mode;
    uint8_t format;
    uint8_t whitebalance;
    uint8_t fx;
    uint8_t sharpness;
    uint8_t quality;
};

static volatile struct arducam_config_t globalCameraConfig = {
    .mode = CAM_IMAGE_MODE_WQXGA2,
    .format = CAM_IMAGE_PIX_FMT_JPG,
    .whitebalance = CAM_WHITE_BALANCE_MODE_SUNNY,
    .fx = CAM_COLOR_FX_NONE,
    .sharpness = CAM_SHARPNESS_LEVEL_7,
    .quality = DEFAULT_QUALITY,
};

void tui_configure_camera(ArducamCamera *camera);

#endif //__ARDUCAM_CONFIG_H