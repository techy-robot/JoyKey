#pragma once
#include <stdbool.h>
#include <string.h>
#include "keyname_map.h"
#include "eeprom.h"

void custom_eeprom_save(void);
void custom_eeprom_load(void);
void mark_layer_dirty(int layer);
void refresh_settings(void);

// Expose this flag so via_handler.c can set it
extern bool layer_dirty[KEYNAME_MAP_MAX_LAYERS];
extern bool save_requested;