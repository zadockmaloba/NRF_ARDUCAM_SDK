#include "Config.h"
#include "ArducamCamera.h"

#include <nrf_delay.h>
#include "debug.h"

void tui_configure_camera(ArducamCamera *camera) {
    int key = 0;
    uint8_t 
        mode = 0,
        format = 0,
        whitebalance = 0,
        fx = 0,
        sharpness = 0,
        quality = 0
        ;
    
    print(LL_PRINT, "Manually setting image params...\n");
    print(LL_PRINT, "Choose Image mode: \n");
    print(LL_PRINT, "*******************\n");
    print(LL_PRINT,"||    Press '0' for QQVGA (160x120)\n");
    print(LL_PRINT,"||    Press '1' for QVGA (320x240)\n");
    print(LL_PRINT,"||    Press '2' for VGA (640x480) \n");
    print(LL_PRINT,"||    Press '3' for SVGA (800x600)\n");
    print(LL_PRINT,"||    Press '4' for HD (1280x720) \n");
    print(LL_PRINT,"||    Press '5' for SXGA (1280x960) \n");
    print(LL_PRINT,"||    Press '6' for UXGA (1600x1200)\n");
    print(LL_PRINT,"||    Press '7' for FHD (1920x1080) \n");
    print(LL_PRINT,"||    Press '8' for QXGA (2048x1536)\n");
    print(LL_PRINT,"||    Press '9' for WQXGA2 (2592x1944)\n");
    print(LL_PRINT,"||    Press 'a' for 96x96 \n");
    print(LL_PRINT,"||    Press 'b' for 128x128 \n");
    print(LL_PRINT,"||    Press 'c' for 320x320 \n");
    
    key = SEGGER_RTT_WaitKey();

    switch (key) {
        case '0': mode = CAM_IMAGE_MODE_QQVGA; break;
        case '1': mode = CAM_IMAGE_MODE_QVGA; break;
        case '2': mode = CAM_IMAGE_MODE_VGA; break;
        case '3': mode = CAM_IMAGE_MODE_SVGA; break;
        case '4': mode = CAM_IMAGE_MODE_HD; break;
        case '5': mode = CAM_IMAGE_MODE_SXGAM; break;
        case '6': mode = CAM_IMAGE_MODE_UXGA; break;
        case '7': mode = CAM_IMAGE_MODE_FHD; break;
        case '8': mode = CAM_IMAGE_MODE_QXGA; break;
        case '9': mode = CAM_IMAGE_MODE_WQXGA2; break;
        case 'a': mode = CAM_IMAGE_MODE_96X96; break;
        case 'b': mode = CAM_IMAGE_MODE_128X128; break;
        case 'c': mode = CAM_IMAGE_MODE_320X320; break;
        default: mode = CAM_IMAGE_MODE_NONE; break;
    } key = 0;
    print(LL_PRINT, "Selected image mode: %d\n", mode);
    print(LL_PRINT, "\n");

    print(LL_PRINT, "Choose pixel format: \n");
    print(LL_PRINT, "*********************\n");
    print(LL_PRINT,"||    Press '0' for none  \n");
    print(LL_PRINT,"||    Press '1' for JPEG format   \n");
    print(LL_PRINT,"||    Press '2' for RGB565 format \n");
    print(LL_PRINT,"||    Press '3' for YUV format    \n");

    key = SEGGER_RTT_WaitKey();

    switch (key) {
        case '0': format = CAM_IMAGE_PIX_FMT_NONE; break;
        case '1': format = CAM_IMAGE_PIX_FMT_JPG; break;
        case '2': format = CAM_IMAGE_PIX_FMT_RGB565; break;
        case '3': format = CAM_IMAGE_PIX_FMT_YUV; break;
        default: format = CAM_IMAGE_PIX_FMT_JPG; break;
    }key = 0;
    SEGGER_RTT_printf(0, "Selected image pixel format: %d\n", format);
    print(LL_PRINT, "\n");

    print(LL_PRINT, "Choose white balance mode: \n");
    print(LL_PRINT, "******************************\n");
    print(LL_PRINT,"||   Press '0' for Auto\n");
    print(LL_PRINT,"||   Press '1' for Sunny\n");
    print(LL_PRINT,"||   Press '2' for Office\n");
    print(LL_PRINT,"||   Press '3' for Cloudy\n");
    print(LL_PRINT,"||   Press '4' for Home\n");

    key = SEGGER_RTT_WaitKey();

    switch(key) {
        case '0': whitebalance = CAM_WHITE_BALANCE_MODE_DEFAULT; break;
        case '1': whitebalance = CAM_WHITE_BALANCE_MODE_SUNNY; break;
        case '2': whitebalance = CAM_WHITE_BALANCE_MODE_OFFICE; break;
        case '3': whitebalance = CAM_WHITE_BALANCE_MODE_CLOUDY; break;
        case '4': whitebalance = CAM_WHITE_BALANCE_MODE_HOME; break;
        default: whitebalance = CAM_WHITE_BALANCE_MODE_DEFAULT; break;
    }key = 0;
    SEGGER_RTT_printf(0, "Selected white balance mode: %d\n", whitebalance);
    print(LL_PRINT, "\n");

    print(LL_PRINT, "Choose color effect: \n");
    print(LL_PRINT, "*********************\n");
    print(LL_PRINT, "||   Press '0' for none\n");
    print(LL_PRINT, "||   Press '1' for Cool light\n");
    print(LL_PRINT, "||   Press '2' for Warm\n");
    print(LL_PRINT, "||   Press '3' for Black&White \n");
    print(LL_PRINT, "||   Press '4' for Sepia\n");
    print(LL_PRINT, "||   Press '5' for Negative\n");
    print(LL_PRINT, "||   Press '6' for Green\n");
    print(LL_PRINT, "||   Press '7' for Over exposure\n");
    print(LL_PRINT, "||   Press '8' for Solarize\n");
    
    key = SEGGER_RTT_WaitKey();

    switch(key) {
        case '0': fx = CAM_COLOR_FX_NONE; break;
        case '1': fx = CAM_COLOR_FX_BLUEISH; break;
        case '2': fx = CAM_COLOR_FX_REDISH; break;
        case '3': fx = CAM_COLOR_FX_BW; break;
        case '4': fx = CAM_COLOR_FX_SEPIA; break;
        case '5': fx = CAM_COLOR_FX_NEGATIVE; break;
        case '6': fx = CAM_COLOR_FX_GRASS_GREEN; break;
        case '7': fx = CAM_COLOR_FX_OVER_EXPOSURE; break;
        default: fx = CAM_COLOR_FX_NONE; break;
    }key = 0;
    print(LL_PRINT, "Selected colour effect: %d\n", fx);
    print(LL_PRINT, "\n");

    print(LL_PRINT, "Choose JPEG Compression level: \n");
    print(LL_PRINT, "*******************************\n");
    print(LL_PRINT, "||   Press '0' for low compression (High Quality)\n");
    print(LL_PRINT, "||   Press '1' for defualt compression\n");
    print(LL_PRINT, "||   Press '2' for high compression (Low Quality)\n");

    key = SEGGER_RTT_WaitKey();

    switch(key) {
        case '0': quality = HIGH_QUALITY; break;
        case '1': quality = DEFAULT_QUALITY; break;
        case '2': quality = LOW_QUALITY; break;
        default: quality = DEFAULT_QUALITY; break;
    } key = 0;
    print(LL_PRINT, "Selected compression level: %d\n", quality);
    print(LL_PRINT, "\n");

    print(LL_PRINT, "Select sharpness level: \n");
    print(LL_PRINT, "************************\n");
    print(LL_PRINT, "||   Press '0' for Auto\n");
    print(LL_PRINT, "||   Press '1' for Sharpness Level 1  \n");
    print(LL_PRINT, "||   Press '2' for Sharpness Level 2  \n");
    print(LL_PRINT, "||   Press '3' for Sharpness Level 3  \n");
    print(LL_PRINT, "||   Press '4' for Sharpness Level 4  \n");
    print(LL_PRINT, "||   Press '5' for Sharpness Level 5  \n");
    print(LL_PRINT, "||   Press '6' for Sharpness Level 6  \n");
    print(LL_PRINT, "||   Press '7' for Sharpness Level 7  \n");
    print(LL_PRINT, "||   Press '8' for Sharpness Level 8  \n");

    key = SEGGER_RTT_WaitKey();

    switch(key) {
        case '0': sharpness = CAM_SHARPNESS_LEVEL_AUTO; break;
        case '1': sharpness = CAM_SHARPNESS_LEVEL_1; break;
        case '2': sharpness = CAM_SHARPNESS_LEVEL_2; break;
        case '3': sharpness = CAM_SHARPNESS_LEVEL_3; break;
        case '4': sharpness = CAM_SHARPNESS_LEVEL_4; break;
        case '5': sharpness = CAM_SHARPNESS_LEVEL_5; break;
        case '6': sharpness = CAM_SHARPNESS_LEVEL_6; break;
        case '7': sharpness = CAM_SHARPNESS_LEVEL_7; break;
        case '8': sharpness = CAM_SHARPNESS_LEVEL_8; break;
        default: sharpness = CAM_SHARPNESS_LEVEL_AUTO; break;
    }key = 0;
    print(LL_PRINT, "Selected sharpness level: %d\n", sharpness);
    print(LL_PRINT, "\n");

    globalCameraConfig.mode = mode;
    globalCameraConfig.format = format;
    globalCameraConfig.fx = fx;
    globalCameraConfig.whitebalance = whitebalance;
    globalCameraConfig.sharpness = sharpness;
    globalCameraConfig.quality = quality;

    // Enable autofocus
    setAutoFocus(camera, 1);

    setAutoWhiteBalance(camera, 1);
    setAutoWhiteBalanceMode(camera, whitebalance);

    // Disable color effects
    setColorEffect(camera, fx);

    // Set sharpness level
    setSharpness(camera, sharpness);

    // Set image quality
    setImageQuality(camera, quality);
}