#include <nrf.h>

#include "ArducamCamera.h"
#include "ArducamSpi.h"

#include "debug.h"

#define IMG_BUFF_SIZE 4000
uint8_t img_buffer[IMG_BUFF_SIZE] = {0};

ArducamCamera camera;

void main(void) {
    SEGGER_RTT_Init();
    arducamSpiBegin();

    camera = createArducamCamera(SPIM_SS_PIN);

    begin(&camera);

    reset(&camera);

    setColorEffect(&camera, CAM_COLOR_FX_BW);

    takePicture(&camera, CAM_IMAGE_MODE_96X96, CAM_IMAGE_PIX_FMT_JPG);

    int bytes_read = 0;

    while(camera.receivedLength > 0) {
        bytes_read = readBuff(&camera, img_buffer, IMG_BUFF_SIZE);

        print(LL_INFO, "*********  Img Data... \n");
        for (int i=0; i < IMG_BUFF_SIZE; ++i) {
            print(LL_DEBUG, "%#02x \n", img_buffer[i]);
        }
        print(LL_INFO, "\n");
    }

    reset(&camera);

    //uint8_t data = arducamSpiTransfer(0x02 & 0x7F);

    return;
}