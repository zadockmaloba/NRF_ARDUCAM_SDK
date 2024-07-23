#include <nrf.h>

#include "ArducamCamera.h"
#include "ArducamSpi.h"

#include "debug.h"
#include "test.h"

ArducamCamera camera;

inline void print_info(void) {
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

inline void print_help_info(void) {
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
            case 'h':
                print(LL_PRINT, "Help info\n");
                break;
            default:
                print(LL_ERROR, "Unkown option: %c\n", input);
                break;
        }
    }

#if 0
    test_hd_jpeg_no_fx_sunny(&camera);
    test_hd_jpeg_no_fx_cloudy(&camera);
    test_hd_jpeg_no_fx_office(&camera);
#endif

    //uint8_t data = arducamSpiTransfer(0x02 & 0x7F);

    return;
}