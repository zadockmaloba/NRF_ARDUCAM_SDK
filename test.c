#include "test.h"
#include "FlashSPI.h"
#include "InternalFlash.h"
#include "Timer.h"

#define IMG_STORE_ADDR 0x40000

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

    nrf_delay_us(20);
    
    // Reset previous camera settings
    // reset(&camera);
    memset((void*)img_buffer, 0, IMG_BUFF_SIZE * sizeof(img_buffer[0]));

    print(LL_PRINT, "Running take picture command \n");

    //startTimer();
    uint32_t _time = millis();
    //resetMillis();
    print(LL_PRINT, "takePicture start time %d microseconds\n", _time);
    _time = millis();
    //nrf_delay_ms(1);
    //resetMillis();
    takePicture(camera, mode, fmt); //Take picture
    uint32_t elapsed_time_ms = millis();
    SEGGER_RTT_printf(0, "Time taken for takePicture: %d microseconds\n", elapsed_time_ms - _time);

    uint32_t bytes_read = 0;
    uint32_t total_bytes_read = 0;
    uint32_t flash_address = IMG_STORE_ADDR;
    
    // Erase flash pages where image will be stored
    uint32_t num_pages = ((camera->receivedLength - 1) / FLASH_PAGE_SIZE) + 1;
    uint32_t tmp_pg = 0;

    SEGGER_RTT_printf(0, "Erasing flash...");
    //for (uint32_t page = 0; page < num_pages; page++) {
    //     erase_flash_page(IMG_STORE_ADDR + page * FLASH_PAGE_SIZE);
    //     tmp_pg = IMG_STORE_ADDR + page * FLASH_PAGE_SIZE;
    //     //if (((camera.receivedLength - 1) % 12) == 0) SEGGER_RTT_printf(0, ".");
    //}
    erase_flash_pages(IMG_STORE_ADDR, num_pages);
    tmp_pg = IMG_STORE_ADDR + (num_pages * FLASH_PAGE_SIZE);
    SEGGER_RTT_printf(0, "\nFlash erased from %#08x to %#08x\n", IMG_STORE_ADDR, tmp_pg);

    // Read image data in chunks and write to flash
    SEGGER_RTT_printf(0, "Writing image data to flash...");
    do {
        bytes_read = readBuff(camera, img_buffer, IMG_BUFF_SIZE);
        //print(LL_PRINT, "First bytes: %#002x, %#002x", img_buffer[0], img_buffer[1]);
        write_flash(flash_address, img_buffer, IMG_BUFF_SIZE);
        flash_address += bytes_read;
        total_bytes_read += bytes_read;
        //if ((bytes_read % 12) == 0) SEGGER_RTT_printf(0, ".");
    } while (camera->receivedLength > 0);
    nrf_delay_us(10);
    SEGGER_RTT_printf(0, "\nWrite done\n");

    print(LL_PRINT, "*********  Img Size: %d \n", total_bytes_read);

#if PRINT_IMG_DATA
    print(LL_PRINT, "*********  Img Data... \n");
    for (int i = 0; i < IMG_BUFF_SIZE; ++i) {
        SEGGER_RTT_printf(0, "%#02x ", img_buffer[i]);
    }
    print(LL_PRINT, "\n");
#endif // PRINT_IMG_DATA

    print(LL_PRINT, "Image stored to flash address range: %#08x to %#08x\n", IMG_STORE_ADDR, tmp_pg);
    print(LL_PRINT, "----------------------------------------------\n");
}

void test_all_camera_settings(ArducamCamera *camera) {
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