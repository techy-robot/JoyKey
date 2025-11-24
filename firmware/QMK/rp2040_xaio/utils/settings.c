#include <string.h>
#include "keyname_map.h"
#include "eeprom.h"


// Define a safe offset. Standard QMK usage rarely exceeds 1KB. 
// 2KB offset is usually safe on large flash chips.
#define CUSTOM_MAP_EEPROM_OFFSET 2048 

// Track which layers have changed since the last save
static bool layer_dirty[KEYNAME_MAP_MAX_LAYERS] = {false};
static bool save_requested = false; // Trigger from VIA

void custom_eeprom_save(void) {
  // Write the entire raw struct to EEPROM
  // NOTE: eeprom_update_block is slow. Only call this when necessary.
  eeprom_update_block(keyname_map, (void*)CUSTOM_MAP_EEPROM_OFFSET, sizeof(keyname_map));
}

void custom_eeprom_load(void) {
  eeprom_read_block(keyname_map, (const void*)CUSTOM_MAP_EEPROM_OFFSET, sizeof(keyname_map));
}

// --- Helper: Mark Dirty ---
void mark_layer_dirty(int layer) {
    if (layer >= 0 && layer < KEYNAME_MAP_MAX_LAYERS) {
        layer_dirty[layer] = true;
        save_requested = true;
    }
}

/**
 * @brief Refresh settings from volatile memory to EEPROM
 *
 * This function checks if a save has been requested and if so,
 * it iterates over all the layers and checks the dirty flag.
 * If the flag is set, it writes the corresponding layer data from
 * volatile memory to EEPROM.
 *
 */
void refresh_settings(void) {
  if (save_requested) {
    save_requested = false; // Reset trigger

    // Base EEPROM address
    uintptr_t base_addr = CUSTOM_MAP_EEPROM_OFFSET;
    size_t layer_size = sizeof(LayerData_t);

    for (int i = 0; i < KEYNAME_MAP_MAX_LAYERS; i++) {
      // ONLY write if this specific layer was touched
      if (layer_dirty[i]) {
        
        // Calculate where this layer lives in EEPROM
        // Address = Base + (LayerIndex * SizeOfLayer)
        void* dest = (void*)(base_addr + (i * layer_size));
        void* src  = (void*)&keyname_map[i];

        // Write just this ~300 byte chunk
        eeprom_update_block(src, dest, layer_size);
        
        // Clear the flag
        layer_dirty[i] = false;
      }
    }
  }
}