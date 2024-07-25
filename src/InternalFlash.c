#include "InternalFlash.h"

#include <nrf.h>
#include <nrf_delay.h>
#include <nrf_fstorage.h>
#include <nrf_fstorage_sd.h>
#include <nrf_fstorage_nvmc.h>

#include <string.h>

#include "debug.h"

static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt);
static void print_flash_info(nrf_fstorage_t * p_fstorage);
static void wait_for_flash_ready(nrf_fstorage_t const * p_fstorage);

// NRF_FSTORAGE_DEF(nrf_fstorage_t fstorage) =
// {
//     /* Set a handler for fstorage events. */
//     .evt_handler = fstorage_evt_handler,

//     /* These below are the boundaries of the flash space assigned to this instance of fstorage.
//      * You must set these manually, even at runtime, before nrf_fstorage_init() is called.
//      * The function nrf5_flash_end_addr_get() can be used to retrieve the last address on the
//      * last page of flash available to write data. */
//     .start_addr = 0x3e000,
//     .end_addr   = 0x3ffff,
// };

nrf_fstorage_t fstorage = {0};

static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt)
{
    if (p_evt->result != NRF_SUCCESS)
    {
        print(LL_PRINT, "--> Event received: ERROR while executing an fstorage operation.\n");
        return;
    }

    switch (p_evt->id)
    {
        case NRF_FSTORAGE_EVT_WRITE_RESULT:
        {
            print(LL_PRINT, "--> Event received: wrote %d bytes at address 0x%x.\n",
                         p_evt->len, p_evt->addr);
        } break;

        case NRF_FSTORAGE_EVT_ERASE_RESULT:
        {
            print(LL_PRINT, "--> Event received: erased %d page from address 0x%x.\n",
                         p_evt->len, p_evt->addr);
        } break;

        default:
            break;
    }
}

static void print_flash_info(nrf_fstorage_t * p_fstorage)
{
    print(LL_PRINT, "========| flash info |========\n");
    print(LL_PRINT, "erase unit: \t%d bytes\n",      p_fstorage->p_flash_info->erase_unit);
    print(LL_PRINT, "program unit: \t%d bytes\n",    p_fstorage->p_flash_info->program_unit);
    print(LL_PRINT, "==============================\n");
}


static void wait_for_flash_ready(nrf_fstorage_t const * p_fstorage)
{
    /* While fstorage is busy, sleep and wait for an event. */
    while (nrf_fstorage_is_busy(p_fstorage))
    {
        __WFE();
    }
}

void fstorage_init(void) {
    nrf_fstorage_api_t * p_fs_api;
    p_fs_api = &nrf_fstorage_nvmc;

    fstorage.evt_handler = fstorage_evt_handler;
    fstorage.start_addr = 0x40000; // start address
    fstorage.end_addr   = 0xDFFFF; // end address

    ret_code_t rc = nrf_fstorage_init(&fstorage, p_fs_api, NULL);
    APP_ERROR_CHECK(rc);
}

void write_flash(uint32_t address, uint8_t *data, uint32_t length) {
    ret_code_t rc = nrf_fstorage_write(&fstorage, address, data, length, NULL);
    APP_ERROR_CHECK(rc);

    wait_for_flash_ready(&fstorage);

    nrf_delay_ms(20);
    print(LL_INFO, "Flash write done. \n");
}

void read_flash(uint32_t address, uint8_t *data, uint32_t length) {
    nrf_delay_ms(10);
    memcpy(data, (void*)address, length);
    nrf_delay_ms(10);
}

void erase_flash_page(uint32_t page_address) {
    ret_code_t rc = nrf_fstorage_erase(&fstorage, page_address, 1, NULL);
    APP_ERROR_CHECK(rc);
}