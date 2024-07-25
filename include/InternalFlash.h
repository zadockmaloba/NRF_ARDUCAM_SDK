#ifndef __INTERNAL_FLASH_H
#define __INTERNAL_FLASH_H

#include <stdint.h>
#include <stdbool.h>

void fstorage_init(void);

void write_flash(uint32_t address, uint8_t *data, uint32_t length);

void read_flash(uint32_t address, uint8_t *data, uint32_t length);

//void wait_for_flash_ready(nrf_fstorage_t const * p_fstorage);


#endif //__INTERNAL_FLASH_H