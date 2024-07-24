#include "test.h"

void test_cam_params(ArducamCamera *camera, 
                    CAM_IMAGE_MODE mode, 
                    CAM_IMAGE_PIX_FMT fmt, 
                    CAM_WHITE_BALANCE wb, 
                    CAM_COLOR_FX fx, 
                    IMAGE_QUALITY qlty,
                    CAM_SHARPNESS_LEVEL sh) 
{
    print(LL_PRINT, "********** CAMERA SETTINGS **********\n");
    print(LL_PRINT, "Mode: %d, Fmt: %d, WhitBlnce: %d, FX: %d, Qlty: %d, Shrpness: %d\n", mode, fmt, wb, fx, qlty, sh);
    
    //Reset previous camera settings
    reset(camera);
    memset((void*)img_buffer, 0, IMG_BUFF_SIZE * sizeof(img_buffer[0]));

    //Enable autfocus
    setAutoFocus(camera, 1);

    setAutoWhiteBalance(camera, 1);

    setAutoWhiteBalanceMode(camera, wb);

    //Disable color effects
    setColorEffect(camera, fx);

    //Set sharpness level
    setSharpness(camera, sh);

    //Set image quality
    setImageQuality(camera, qlty);

    takePicture(camera, mode, fmt);

    uint32_t bytes_read = 0;
#if PRINT_IMG_DATA
    do {
        bytes_read += readBuff(camera, img_buffer, IMG_BUFF_SIZE);
    } while(camera->receivedLength > 0);
#else
    bytes_read = camera->receivedLength;
#endif

    print(LL_PRINT, "*********  Img Size: %d \n", bytes_read);

#if PRINT_IMG_DATA
    print(LL_PRINT, "*********  Img Data... \n");
    for (int i=0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_PRINT, "\n");
#endif //PRINT_IMG_DATA

    print(LL_PRINT, "----------------------------------------------\n");
}

void test_all_camera_settings(ArducamCamera* camera) {
    print(LL_PRINT, "********** ALL CAMERA SETTINGS **********\n");

    for(int i=0; i< CAM_IMAGE_MODE_NONE; ++i)
    for(int j=0; j< CAM_IMAGE_PIX_FMT_NONE; ++j)
    for(int k=0; k< CAM_WHITE_BALANCE_MODE_HOME; ++k)
    for(int l=0; l< CAM_COLOR_FX_SOLARIZE; ++l)
    //for(int m=0; m< CAM_SHARPNESS_LEVEL_8; ++m) 
    {
        test_cam_params(camera, i, j, k, l, DEFAULT_QUALITY, 6);
    }
}