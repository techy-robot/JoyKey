#include <string.h>
#include "keyname_map.h"
#include "eeprom.h"


// Define a safe offset. Standard QMK usage rarely exceeds 1KB. 
// 2KB offset is usually safe on large flash chips.
#define CUSTOM_MAP_EEPROM_OFFSET 2048 

void custom_eeprom_save(void) {
    // Write the entire raw struct to EEPROM
    // NOTE: eeprom_update_block is slow. Only call this when necessary.
    eeprom_update_block(keyname_map, (void*)CUSTOM_MAP_EEPROM_OFFSET, sizeof(keyname_map));
}

void custom_eeprom_load(void) {
    eeprom_read_block(keyname_map, (const void*)CUSTOM_MAP_EEPROM_OFFSET, sizeof(keyname_map));
}