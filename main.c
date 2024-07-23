#include <nrf.h>

#include "ArducamCamera.h"
#include "ArducamSpi.h"

#include "debug.h"
#include "test.h"

ArducamCamera camera;

void print_info(void) {
    //print(LL_PRINT, 
    //    "      ___           ___           ___                       ___           ___     \n"
    //    "     /  /\\         /__/\\         /  /\\        ___          /  /\\         /  /\\    \n"
    //    "    /  /::\\        \\  \\:\\       /  /::\\      /  /\\        /  /::\\       /  /::|   \n"
    //    "   /  /:/\\:\\        \\  \\:\\     /  /:/\\:\\    /  /:/       /  /:/\\:\\     /  /:|:|   \n"
    //    "  /  /:/~/::\\   _____\\__\\:\\   /  /:/~/::\\  /__/::\\      /  /:/~/::\\   /  /:/|:|__ \n"
    //    " /__/:/ /:/\\:\\ /__/::::::::\\ /__/:/ /:/\\:\\ \\__\\/\\:\\__  /__/:/ /:/\\:\\ /__/:/_|::::\\\n"
    //    " \\  \\:\\/:/__\\/ \\  \\:\\~~\\~~\\/ \\  \\:\\/:/__\\/    \\  \\:\\/\\ \\  \\:\\/:/__\\/ \\  \\:\\/:/~~/ \n"
    //    "  \\  \\::/       \\  \\:\\  ~~~   \\  \\::/          \\__\\::/  \\  \\::/       \\  \\::/    \n"
    //    "   \\  \\/        \\  \\:\\        \\  \\:\\          /__/:/    \\  \\:\\        \\  \\:\\    \n"
    //    "    \\  \\:\\        \\  \\:\\        \\  \\:\\         \\__\\/      \\  \\:\\        \\  \\:\\   \n"
    //    "     \\__\\/         \\__\\/         \\__\\/                     \\__\\/         \\__\\/   \n"
    //    "\n"
    //);
    
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
                print(LL_PRINT, "Manually setting image params...\n");
                print(LL_PRINT, "Choose Image mode: \n");
                print(LL_PRINT, "*******************\n");
                print(LL_PRINT,"||    Press '0' for QQVGA (160x120)                               ||\n");
                print(LL_PRINT,"||    Press '1' for QVGA (320x240)                                ||\n");
                print(LL_PRINT,"||    Press '2' for VGA (640x480)                                 ||\n");
                print(LL_PRINT,"||    Press '3' for SVGA (800x600)                                ||\n");
                print(LL_PRINT,"||    Press '4' for HD (1280x720)                                 ||\n");
                print(LL_PRINT,"||    Press '5' for SXGA (1280x960)                               ||\n");
                print(LL_PRINT,"||    Press '6' for UXGA (1600x1200)                              ||\n");
                print(LL_PRINT,"||    Press '7' for FHD (1920x1080)                               ||\n");
                print(LL_PRINT,"||    Press '8' for QXGA (2048x1536)                              ||\n");
                print(LL_PRINT,"||    Press '9' for WQXGA2 (2592x1944)                            ||\n");
                print(LL_PRINT,"||    Press 'a' for 96x96                                         ||\n");
                print(LL_PRINT,"||    Press 'b' for 128x128                                       ||\n");
                print(LL_PRINT,"||    Press 'c' for 320x320                                       ||\n");
                int mode = 0;
                while(!mode){ mode = SEGGER_RTT_GetKey();}

                

                break;
            }
            case 'h':
                print(LL_PRINT, "Help info..\n");
                print_help_info();
                break;
            default:
                print(LL_ERROR, "Unkown option: %c\n", input);
                break;
        }
    }

    return;
}