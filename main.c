#include <nrf.h>

#include "ArducamCamera.h"
#include "ArducamSpi.h"

#include "debug.h"

#define TMP_IMG_BUFF_SIZE 256
#define IMG_BUFF_SIZE 80000
uint8_t temp_img[TMP_IMG_BUFF_SIZE] = {0};
uint8_t img_buffer[IMG_BUFF_SIZE] = {0};

ArducamCamera camera;

void main(void) {
    SEGGER_RTT_Init();
    //arducamSpiBegin();

    //Initialize camera instance and start SPI
    camera = createArducamCamera(SPIM_SS_PIN);
    begin(&camera);

    //Reset previous camera settings
    reset(&camera);

    //Enable autfocus
    setAutoFocus(&camera, 1);

    setAutoWhiteBalance(&camera, 1);

    setAutoWhiteBalanceMode(&camera, CAM_WHITE_BALANCE_MODE_CLOUDY);

    //Disable color effects
    setColorEffect(&camera, CAM_COLOR_FX_NONE);

    //Set image quality
    setImageQuality(&camera, LOW_QUALITY);

    takePicture(&camera, CAM_IMAGE_MODE_HD, CAM_IMAGE_PIX_FMT_JPG);

    int bytes_read = 0;

    while(camera.receivedLength > 0) {
        bytes_read += readBuff(&camera, img_buffer, IMG_BUFF_SIZE);

        /*
        for(int i=0; i<TMP_IMG_BUFF_SIZE; ++i) {
            img_buffer[bytes_read] = temp_img[i];
        }*/
    }

    print(LL_INFO, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        print(LL_DEBUG, "%#02x \n", img_buffer[i]);
    }
    print(LL_INFO, "\n");

    reset(&camera);

    //uint8_t data = arducamSpiTransfer(0x02 & 0x7F);

    return;
}