#include <nrf.h>

#include "ArducamCamera.h"
#include "ArducamSpi.h"

#include "debug.h"
#include "test.h"

ArducamCamera camera;

void main(void) {
    SEGGER_RTT_Init();
    //arducamSpiBegin();

    //Initialize camera instance and start SPI
    camera = createArducamCamera(SPIM_SS_PIN);
    begin(&camera);

    test_all_camera_settings(&camera);

#if 0
    test_hd_jpeg_no_fx_sunny(&camera);
    test_hd_jpeg_no_fx_cloudy(&camera);
    test_hd_jpeg_no_fx_office(&camera);
#endif

    //uint8_t data = arducamSpiTransfer(0x02 & 0x7F);

    return;
}