#ifndef A8E1C6B4_EF81_43A1_873F_168AC9E554EE
#define A8E1C6B4_EF81_43A1_873F_168AC9E554EE

#include <nrf.h>

#include "ArducamCamera.h"
#include "ArducamSpi.h"

#include "debug.h"

#define TMP_IMG_BUFF_SIZE 256
#define IMG_BUFF_SIZE 80000
static uint8_t temp_img[TMP_IMG_BUFF_SIZE] = {0};
static uint8_t img_buffer[IMG_BUFF_SIZE] = {0};

void test_hd_jpeg_no_fx_sunny(ArducamCamera* camera);

#endif /* A8E1C6B4_EF81_43A1_873F_168AC9E554EE */
