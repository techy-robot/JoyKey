#pragma once

#include <stdbool.h>
#include <stdint.h>

// --- Flash Configuration (Moved here so diskio.c can see it) ---
#define FLASH_FS_OFFSET (2 * 1024 * 1024)
#define FLASH_FS_SIZE   (1 * 1024 * 1024)
#define BLOCK_SIZE      512
#define SECTOR_COUNT    (FLASH_FS_SIZE / BLOCK_SIZE)

// --- Low-Level Flash Helpers ---
// These interface directly with the RP2040 hardware
void flash_read_512(uint32_t block_idx, uint8_t *buff);
void flash_write_512(uint32_t block_idx, const uint8_t *buff);

// --- High-Level API ---
void init_mass_storage(void);
void toggle_msc_mode(void);
bool is_msc_readonly(void);