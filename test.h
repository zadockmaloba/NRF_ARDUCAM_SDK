#ifndef A8E1C6B4_EF81_43A1_873F_168AC9E554EE
#define A8E1C6B4_EF81_43A1_873F_168AC9E554EE

#include <nrf.h>
#include <string.h>

#include "ArducamCamera.h"
#include "ArducamSpi.h"

#include "debug.h"

#define TMP_IMG_BUFF_SIZE 256
#define IMG_BUFF_SIZE 160000
static uint8_t temp_img[TMP_IMG_BUFF_SIZE] = {0};
static uint8_t img_buffer[IMG_BUFF_SIZE] = {0};

//********** ALL IMAGE TESTS *********************/
void test_all_camera_settings();

//********** JPEG IMAGE TESTS *********************/
void test_hd_jpeg_no_fx_sunny(ArducamCamera* camera);
void test_hd_jpeg_no_fx_cloudy(ArducamCamera* camera);
void test_hd_jpeg_no_fx_office(ArducamCamera* camera);

void test_fhd_jpeg_no_fx_sunny(ArducamCamera* camera);
void test_fhd_jpeg_no_fx_cloudy(ArducamCamera* camera);
void test_fhd_jpeg_no_fx_office(ArducamCamera* camera);

void test_hd_jpeg_bw_fx_sunny(ArducamCamera* camera);
void test_hd_jpeg_bw_fx_cloudy(ArducamCamera* camera);
void test_hd_jpeg_bw_fx_office(ArducamCamera* camera);

void test_fhd_jpeg_bw_fx_sunny(ArducamCamera* camera);
void test_fhd_jpeg_bw_fx_cloudy(ArducamCamera* camera); 
void test_fhd_jpeg_bw_fx_office(ArducamCamera* camera);

//********** YUV IMAGE TESTS *********************/
void test_hd_yuv_no_fx_sunny(ArducamCamera* camera);
void test_hd_yuv_no_fx_cloudy(ArducamCamera* camera);
void test_hd_yuv_no_fx_office(ArducamCamera* camera);

void test_fhd_yuv_no_fx_sunny(ArducamCamera* camera);
void test_fhd_yuv_no_fx_cloudy(ArducamCamera* camera);
void test_fhd_yuv_no_fx_office(ArducamCamera* camera);

void test_hd_yuv_bw_fx_sunny(ArducamCamera* camera);
void test_hd_yuv_bw_fx_cloudy(ArducamCamera* camera);
void test_hd_yuv_bw_fx_office(ArducamCamera* camera);

void test_fhd_yuv_bw_fx_sunny(ArducamCamera* camera);
void test_fhd_yuv_bw_fx_cloudy(ArducamCamera* camera);
void test_fhd_yuv_bw_fx_office(ArducamCamera* camera);


#endif /* A8E1C6B4_EF81_43A1_873F_168AC9E554EE */
