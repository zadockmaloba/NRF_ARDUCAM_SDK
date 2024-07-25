#ifndef A8E1C6B4_EF81_43A1_873F_168AC9E554EE
#define A8E1C6B4_EF81_43A1_873F_168AC9E554EE

#include <nrf.h>
#include <string.h>

#include "ArducamCamera.h"
#include "ArducamSpi.h"

#include "debug.h"

#define TMP_IMG_BUFF_SIZE 256
#define IMG_BUFF_SIZE 16000
static uint8_t temp_img[TMP_IMG_BUFF_SIZE] = {0};
static uint8_t img_buffer[IMG_BUFF_SIZE] = {0};

void test_all_camera_settings();

void test_cam_params(CAM_IMAGE_MODE mode, 
                    CAM_IMAGE_PIX_FMT fmt, 
                    CAM_WHITE_BALANCE wb, 
                    CAM_COLOR_FX fx, 
                    IMAGE_QUALITY qlty,
                    CAM_SHARPNESS_LEVEL sh);


#endif /* A8E1C6B4_EF81_43A1_873F_168AC9E554EE */
