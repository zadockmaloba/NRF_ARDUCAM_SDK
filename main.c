#include <nrf.h>

#include "ArducamCamera.h"
#include "ArducamSpi.h"

#include "debug.h"
#include "test.h"

ArducamCamera camera;

void print_info(void) { 
    print( LL_PRINT, "  ==============================================================  \n");
    print( LL_PRINT, "||                          TEST SUITE                          ||\n");
    print( LL_PRINT, "||==============================================================||\n");
    print( LL_PRINT, "||    Testing ArduCAM Parameters on Nrf52840DK                  ||\n");
    print( LL_PRINT, "||                                                              ||\n");
    print( LL_PRINT, "||    - Camera Initialization                                   ||\n");
    print( LL_PRINT, "||    - Parameter Validation                                    ||\n");
    print( LL_PRINT, "||    - Communication Protocols                                 ||\n");
    print( LL_PRINT, "||    - Performance Metrics                                     ||\n");
    print( LL_PRINT, "||                                                              ||\n");
    print( LL_PRINT, "||    Powered by ArduCAM and NRF52840DK                         ||\n");
    print( LL_PRINT, "||==============================================================||\n");
    print( LL_PRINT, "||                           GPIO Pinout                        ||\n");
    print( LL_PRINT, "||    P1.08 - CS                                                ||\n");
    print( LL_PRINT, "||    P0.25 - MISO                                              ||\n");
    print( LL_PRINT, "||    P0.26 - MOSI                                              ||\n");
    print( LL_PRINT, "||    P0.27 - SCK                                               ||\n");
    print( LL_PRINT, "||==============================================================||\n");
}

void print_help_info(void) {
    print( LL_PRINT, "  ==============================================================  \n");
    print( LL_PRINT, "||                          TEST OPTIONS                        ||\n");
    print( LL_PRINT, "||==============================================================||\n");
    print( LL_PRINT, "||  Press 'h': To show test options                             ||\n");
    print( LL_PRINT, "||  Press 'a': To run all tests                                 ||\n");
    print( LL_PRINT, "||  Press 'm': To manually setup camera params and test         ||\n");
    print( LL_PRINT, "||==============================================================||\n");

}

void main(void) {
    SEGGER_RTT_Init();
    nrf_delay_ms(20);

    print(LL_PRINT, "Initializing ArduCAM... \n");

    nrf_delay_us(20);
    print_info();

    //Initialize camera instance and start SPI
    camera = createArducamCamera(SPIM_SS_PIN);
    begin(&camera);

    while (1) {
        int input = SEGGER_RTT_GetKey();
        if(input < 1) continue;
        switch (input) {
            case 'a':
                print(LL_PRINT, "Running all tests....\n");
                nrf_delay_us(20);
                test_all_camera_settings(&camera);
                break;
            case 'm': {
                int key = 0;
                uint8_t 
                    mode = 0,
                    format = 0,
                    whitebalance = 0,
                    fx = 0,
                    sharpness = 0
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

                switch (format) {
                    case '1': format = CAM_IMAGE_PIX_FMT_JPG; break;
                    case '2': format = CAM_IMAGE_PIX_FMT_RGB565; break;
                    case '3': format = CAM_IMAGE_PIX_FMT_YUV; break;
                    default: format = CAM_IMAGE_PIX_FMT_NONE; break;
                }key = 0;
                SEGGER_RTT_printf(0, "Selected image pixel format: %d\n", format);
                print(LL_PRINT, "\n");

                print(LL_PRINT, "Chose white balance mode: \n");
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
                }key = 0;
                print(LL_PRINT, "Selected colore effect: %d\n", fx);
                print(LL_PRINT, "\n");

                break;
            }
            case 'h':
                print(LL_PRINT, "Help info..\n");
                print_help_info();
                break;
            default:
                print(LL_ERROR, "Unkown option: %c\n", input);
                print_help_info();
                break;
        }
    }

    return;
}