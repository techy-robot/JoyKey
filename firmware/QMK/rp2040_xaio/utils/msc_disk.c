#include "msc_disk.h"
#include <hal.h>
#include "hal_usb_msd.h" 
#include "ff16/ff.h"
#include "ff16/diskio.h"
#include <string.h>
#include "hardware/flash.h"
#include "hardware/regs/addressmap.h"

// --- Global State ---
bool usb_msc_is_readonly = true;
FATFS fs;
USBMassStorageDriver USBMSD1;

// --- SCSI Inquiry Data ---
static const scsi_inquiry_response_t msd_inquiry_data = {
    .peripheral = 0x00,           // Direct Access Block Device
    .removable = 0x80,            // Removable Media
    .version = 0x02,              // SPC-2
    .response_data_format = 0x02, // Response Data Format
    .additional_length = 0x1F,    // 31 bytes
    .sccstp = 0,
    .bqueetc = 0,
    .cmdque = 0,
    .vendorID = {'Q','M','K',' ',' ',' ',' ',' '},
    .productID = {'R','P','2','0','4','0',' ','M','S','C',' ',' ',' ',' ',' ',' '},
    .productRev = {'1','.','0','0'}
};
// --- Block Device Interface ---
static const struct BaseBlockDeviceVMT flash_disk_vmt;

typedef struct {
    const struct BaseBlockDeviceVMT *vmt;
} FlashDisk;

FlashDisk flash_disk = { &flash_disk_vmt };

// --- Flash Helpers (Now Global for diskio.c) ---
void flash_read_512(uint32_t block_idx, uint8_t *buff) {
    uint32_t addr = FLASH_FS_OFFSET + (block_idx * BLOCK_SIZE);
    memcpy(buff, (void *)(XIP_BASE + addr), BLOCK_SIZE);
}

void flash_write_512(uint32_t block_idx, const uint8_t *buff) {
    uint32_t addr = FLASH_FS_OFFSET + (block_idx * BLOCK_SIZE);
    flash_range_erase(addr, BLOCK_SIZE);
    flash_range_program(addr, buff, BLOCK_SIZE);
}

// --- Block Device Implementation ---
static bool blk_read(void *instance, uint32_t startblk, uint8_t *buffer, uint32_t n) {
    (void)instance;
    for (uint32_t i = 0; i < n; i++) {
        flash_read_512(startblk + i, buffer + (i * BLOCK_SIZE));
    }
    return false;
}

static bool blk_write(void *instance, uint32_t startblk, const uint8_t *buffer, uint32_t n) {
    (void)instance;
    if (usb_msc_is_readonly) return true;
    for (uint32_t i = 0; i < n; i++) {
        flash_write_512(startblk + i, buffer + (i * BLOCK_SIZE));
    }
    return false;
}

static bool blk_sync(void *instance) { (void)instance; return false; }
static bool blk_get_info(void *instance, BlockDeviceInfo *bdip) {
    (void)instance;
    bdip->blk_num = SECTOR_COUNT;
    bdip->blk_size = BLOCK_SIZE;
    return false;
}
static bool blk_is_inserted(void *instance) { (void)instance; return true; }
static bool blk_is_protected(void *instance) { (void)instance; return usb_msc_is_readonly; }
static bool blk_connect(void *instance) { (void)instance; return false; }
static bool blk_disconnect(void *instance) { (void)instance; return false; }

static const struct BaseBlockDeviceVMT flash_disk_vmt = {
    (size_t)0, blk_is_inserted, blk_is_protected, blk_connect, blk_disconnect,
    blk_read, blk_write, blk_sync, blk_get_info
};

// --- Initialization ---
void init_mass_storage(void) {
    if (f_mount(&fs, "", 1) != FR_OK) {
        f_mkfs("", 0, 0, BLOCK_SIZE);
        f_mount(&fs, "", 1);
    }
    msdObjectInit(&USBMSD1);
    static uint8_t msd_buffer[512]; 
    msdStart(&USBMSD1, &USBD1, (BaseBlockDevice*)&flash_disk, msd_buffer, &msd_inquiry_data, NULL);
}

void toggle_msc_mode(void) {
    msdStop(&USBMSD1);
    chThdSleepMilliseconds(100);

    if (usb_msc_is_readonly) {
        f_mount(NULL, "", 0); 
        usb_msc_is_readonly = false;
    } else {
        usb_msc_is_readonly = true;
        f_mount(&fs, "", 1); 
    }
    
    static uint8_t msd_buffer[512];
    msdStart(&USBMSD1, &USBD1, (BaseBlockDevice*)&flash_disk, msd_buffer, &msd_inquiry_data, NULL);
}