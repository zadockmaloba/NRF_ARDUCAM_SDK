#include "test.h"

void test_cam_params(CAM_IMAGE_MODE mode, CAM_IMAGE_PIX_FMT fmt, CAM_WHITE_BALANCE wb, CAM_COLOR_FX fx, CAM_SHARPNESS_LEVEL sh) {
    print(LL_PRINT, "********** CAMERA SETTINGS **********\n");
    print(LL_PRINT, "Mode: %d Fmt: %d WB: %d FX: %d SH: %d\n", mode, fmt, wb, fx, sh);
    
    //Reset previous camera settings
    reset(camera);
    memset((void*)img_buffer, 0, IMG_BUFF_SIZE * sizeof(img_buffer[0]));

    //Enable autfocus
    setAutoFocus(camera, 1);

    setAutoWhiteBalance(camera, 1);

    setAutoWhiteBalanceMode(camera, wb);

    //Disable color effects
    setColorEffect(camera, fx);

    //Set image quality
    setImageQuality(camera, LOW_QUALITY);

    takePicture(camera, mode, fmt);

    uint32_t bytes_read = 0;

    do {
        bytes_read += readBuff(camera, img_buffer, IMG_BUFF_SIZE);
    } while(camera->receivedLength > 0);

    print(LL_PRINT, "*********  Img Size: %d \n", bytes_read);

    print(LL_PRINT, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_PRINT, "\n");

    print(LL_PRINT, "----------------------------------------------\n");
}

void test_all_camera_settings() {
    print(LL_PRINT, "********** ALL CAMERA SETTINGS **********\n");

    for(int i=0; i< CAM_IMAGE_MODE_NONE; ++i)
    for(int j=0; j< CAM_IMAGE_PIX_FMT_NONE; ++j)
    for(int k=0; k< CAM_WHITE_BALANCE_MODE_DEFAULT; ++k)
    for(int l=0; l< CAM_COLOR_FX_NONE; ++l)
    for(int m=0; m< CAM_SHARPNESS_LEVEL_AUTO; ++m) {
        test_all_camera_settings(i, j, k, l, m);
    }
}

void test_hd_jpeg_no_fx_sunny(ArducamCamera* camera) {

    print(LL_PRINT, "********** HD, JPEG, NO FX, SUNNY **********\n");
    //Reset previous camera settings
    reset(camera);
    memset((void*)img_buffer, 0, IMG_BUFF_SIZE * sizeof(img_buffer[0]));

    //Enable autfocus
    setAutoFocus(camera, 1);

    setAutoWhiteBalance(camera, 1);

    setAutoWhiteBalanceMode(camera, CAM_WHITE_BALANCE_MODE_SUNNY);

    //Disable color effects
    setColorEffect(camera, CAM_COLOR_FX_NONE);

    //Set image quality
    setImageQuality(camera, LOW_QUALITY);

    takePicture(camera, CAM_IMAGE_MODE_HD, CAM_IMAGE_PIX_FMT_JPG);

    uint32_t bytes_read = 0;

    do {
        bytes_read += readBuff(camera, img_buffer, IMG_BUFF_SIZE);
    } while(camera->receivedLength > 0);

    print(LL_PRINT, "*********  Img Size: %d \n", bytes_read);

    print(LL_PRINT, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_PRINT, "\n");

    print(LL_PRINT, "----------------------------------------------\n");
}

void test_hd_jpeg_no_fx_cloudy(ArducamCamera* camera) {
    print(LL_PRINT, "********** HD, JPEG, NO FX, CLOUDY **********\n");
    //Reset previous camera settings
    reset(camera);
    memset((void*)img_buffer, 0, IMG_BUFF_SIZE * sizeof(img_buffer[0]));

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

    print(LL_PRINT, "*********  Img Size: %d \n", bytes_read);

    print(LL_PRINT, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_PRINT, "\n");

    print(LL_PRINT, "----------------------------------------------\n");
}

void test_hd_jpeg_no_fx_office(ArducamCamera* camera) {
    print(LL_PRINT, "********** HD, JPEG, NO FX, OFFICE **********\n");
    //Reset previous camera settings
    reset(camera);
    memset((void*)img_buffer, 0, IMG_BUFF_SIZE * sizeof(img_buffer[0]));

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

    print(LL_PRINT, "*********  Img Size: %d \n", bytes_read);

    print(LL_PRINT, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_PRINT, "\n");

    print(LL_PRINT, "----------------------------------------------\n");
}

void test_fhd_jpeg_no_fx_sunny(ArducamCamera* camera) {
    print(LL_PRINT, "********** FHD, JPEG, NO FX, SUNNY **********\n");
    //Reset previous camera settings
    reset(camera);
    memset((void*)img_buffer, 0, IMG_BUFF_SIZE * sizeof(img_buffer[0]));

    //Enable autfocus
    setAutoFocus(camera, 1);

    setAutoWhiteBalance(camera, 1);

    setAutoWhiteBalanceMode(camera, CAM_WHITE_BALANCE_MODE_SUNNY);

    //Disable color effects
    setColorEffect(camera, CAM_COLOR_FX_NONE);

    //Set image quality
    setImageQuality(camera, LOW_QUALITY);

    takePicture(camera, CAM_IMAGE_MODE_FHD, CAM_IMAGE_PIX_FMT_JPG);

    uint32_t bytes_read = 0;

    do {
        bytes_read += readBuff(camera, img_buffer, IMG_BUFF_SIZE);
    } while(camera->receivedLength > 0);

    print(LL_PRINT, "*********  Img Size: %d \n", bytes_read);

    print(LL_PRINT, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_PRINT, "\n");

    print(LL_PRINT, "----------------------------------------------\n");
}

void test_fhd_jpeg_no_fx_cloudy(ArducamCamera* camera) {
    print(LL_PRINT, "********** FHD, JPEG, NO FX, CLOUDY **********\n");
    //Reset previous camera settings
    reset(camera);
    memset((void*)img_buffer, 0, IMG_BUFF_SIZE * sizeof(img_buffer[0]));

    //Enable autfocus
    setAutoFocus(camera, 1);

    setAutoWhiteBalance(camera, 1);

    setAutoWhiteBalanceMode(camera, CAM_WHITE_BALANCE_MODE_CLOUDY);

    //Disable color effects
    setColorEffect(camera, CAM_COLOR_FX_NONE);

    //Set image quality
    setImageQuality(camera, LOW_QUALITY);

    takePicture(camera, CAM_IMAGE_MODE_FHD, CAM_IMAGE_PIX_FMT_JPG);

    uint32_t bytes_read = 0;

    do {
        bytes_read += readBuff(camera, img_buffer, IMG_BUFF_SIZE);
    } while(camera->receivedLength > 0);

    print(LL_PRINT, "*********  Img Size: %d \n", bytes_read);

    print(LL_PRINT, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_PRINT, "\n");

    print(LL_PRINT, "----------------------------------------------\n");
}
void test_fhd_jpeg_no_fx_office(ArducamCamera* camera) {
    print(LL_PRINT, "********** FHD, JPEG, NO FX, OFFICE **********\n");
    //Reset previous camera settings
    reset(camera);
    memset((void*)img_buffer, 0, IMG_BUFF_SIZE * sizeof(img_buffer[0]));

    //Enable autfocus
    setAutoFocus(camera, 1);

    setAutoWhiteBalance(camera, 1);

    setAutoWhiteBalanceMode(camera, CAM_WHITE_BALANCE_MODE_OFFICE);

    //Disable color effects
    setColorEffect(camera, CAM_COLOR_FX_NONE);

    //Set image quality
    setImageQuality(camera, LOW_QUALITY);

    takePicture(camera, CAM_IMAGE_MODE_FHD, CAM_IMAGE_PIX_FMT_JPG);

    uint32_t bytes_read = 0;

    do {
        bytes_read += readBuff(camera, img_buffer, IMG_BUFF_SIZE);
    } while(camera->receivedLength > 0);

    print(LL_PRINT, "*********  Img Size: %d \n", bytes_read);

    print(LL_PRINT, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_PRINT, "\n");

    print(LL_PRINT, "----------------------------------------------\n");
}