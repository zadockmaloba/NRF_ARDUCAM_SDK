#ifndef __INTERNAL_FLASH_H
#define __INTERNAL_FLASH_H

#include <stdint.h>
#include <stdbool.h>

#define FLASH_PAGE_SIZE 4096

void fstorage_init(void);

void write_flash(uint32_t address, uint8_t *data, uint32_t length);

void read_flash(uint32_t address, uint8_t *data, uint32_t length);

void erase_flash_page(uint32_t page_address);

void erase_flash_pages(uint32_t page_address, uint32_t pages);

//void wait_for_flash_ready(nrf_fstorage_t const * p_fstorage);


#endif //__INTERNAL_FLASH_H