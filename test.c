#include "test.h"

void test_hd_jpeg_no_fx_sunny(ArducamCamera* camera) {

    print(LL_INFO, "********** HD JPEG NO FX SUNNY **********\n");
    //Reset previous camera settings
    reset(camera);

    //Enable autfocus
    setAutoFocus(camera, 1);

    setAutoWhiteBalance(camera, 1);

    setAutoWhiteBalanceMode(camera, CAM_WHITE_BALANCE_MODE_SUNNY);

    //Disable color effects
    setColorEffect(camera, CAM_COLOR_FX_NONE);

    //Set image quality
    setImageQuality(camera, LOW_QUALITY);

    takePicture(camera, CAM_IMAGE_MODE_HD, CAM_IMAGE_PIX_FMT_JPG);

    int bytes_read = 0;

    do {
        bytes_read += readBuff(camera, img_buffer, IMG_BUFF_SIZE);
    } while(camera->receivedLength > 0);

    print(LL_INFO, "*********  Img Size: %i \n", bytes_read);

    print(LL_INFO, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_INFO, "\n");

    print(LL_INFO, "----------------------------------------------\n");
}

void test_hd_jpeg_no_fx_cloudy(ArducamCamera* camera) {
    print(LL_INFO, "********** HD JPEG NO FX CLOUDY **********\n");
    //Reset previous camera settings
    reset(camera);

    //Enable autfocus
    setAutoFocus(camera, 1);

    setAutoWhiteBalance(camera, 1);

    setAutoWhiteBalanceMode(camera, CAM_WHITE_BALANCE_MODE_CLOUDY);

    //Disable color effects
    setColorEffect(camera, CAM_COLOR_FX_NONE);

    //Set image quality
    setImageQuality(camera, LOW_QUALITY);

    takePicture(camera, CAM_IMAGE_MODE_HD, CAM_IMAGE_PIX_FMT_JPG);

    int bytes_read = 0;

    do {
        bytes_read += readBuff(camera, img_buffer, IMG_BUFF_SIZE);
    } while(camera->receivedLength > 0);

    print(LL_INFO, "*********  Img Size: %i \n", bytes_read);

    print(LL_INFO, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_INFO, "\n");

    print(LL_INFO, "----------------------------------------------\n");
}

void test_hd_jpeg_no_fx_office(ArducamCamera* camera) {
    print(LL_INFO, "********** HD JPEG NO FX OFFICE **********\n");
    //Reset previous camera settings
    reset(camera);

    //Enable autfocus
    setAutoFocus(camera, 1);

    setAutoWhiteBalance(camera, 1);

    setAutoWhiteBalanceMode(camera, CAM_WHITE_BALANCE_MODE_OFFICE);

    //Disable color effects
    setColorEffect(camera, CAM_COLOR_FX_NONE);

    //Set image quality
    setImageQuality(camera, LOW_QUALITY);

    takePicture(camera, CAM_IMAGE_MODE_HD, CAM_IMAGE_PIX_FMT_JPG);

    int bytes_read = 0;

    do {
        bytes_read += readBuff(camera, img_buffer, IMG_BUFF_SIZE);
    } while(camera->receivedLength > 0);

    print(LL_INFO, "*********  Img Size: %i \n", bytes_read);

    print(LL_INFO, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_INFO, "\n");

    print(LL_INFO, "----------------------------------------------\n");
}