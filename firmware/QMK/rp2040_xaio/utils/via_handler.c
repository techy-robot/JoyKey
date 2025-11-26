#include "keyname_map.h" // Include header, NOT .c
#include "settings.h"    // Include header, NOT .c
#include "dynamic_keymap.h"
#include "via.h"

uint8_t via_selected_layer = 0; // Which layer is VIA currently editing?
uint8_t via_selected_key = 0; // Which key is VIA currently editing?

// --- Value IDs (Shared between Web Tool and VIA UI) ---
enum custom_value_ids {
    // 1 - 31: Bulk Data (Web Tool)
    id_bulk_layer_data      = 1,
    id_bulk_key_data        = 2,

    // 32 - 47: VIA UI Layer Controls
    id_via_layer_select     = 32,
    id_via_layer_effect     = 33,
    id_via_layer_speed      = 34,
    id_via_layer_hue        = 35,
    id_via_layer_sat        = 36,
    id_via_layer_val        = 37,
    id_via_layer_color      = 38,

    // 48 - 63: VIA UI Key Controls
    id_via_key_select       = 48,
    id_via_key_hue          = 49,
    id_via_key_sat          = 50,
    id_via_key_val          = 51,
    id_via_key_color        = 52
};

#include "via.h"

// =============================================================================
// HELPER: PROCESS SET (0x07)
// =============================================================================
void process_via_set(uint8_t *data) {
    // Format: [0x07] [Channel(0)] [ValueID] [Data...]
    if (data[1] != 0) return; // Enforce Channel 0
    
    uint8_t value_id = data[2];

    switch (value_id) {
        // --- BULK SET (Web Tool) ---
        case id_bulk_layer_data: {
            uint8_t layer = data[3];
            if (layer >= KEYNAME_MAP_MAX_LAYERS) break;

            char* namePtr = (char*)&data[4];
            char* imgPtr  = (char*)&data[14];

            strncpy(keyname_map[layer].name, namePtr, 10);
            keyname_map[layer].name[9] = '\0';
            strncpy(keyname_map[layer].imageName, imgPtr, 10);
            keyname_map[layer].imageName[9] = '\0';

            keyname_map[layer].lightingEffect = data[24];
            keyname_map[layer].effectSpeed    = data[25];
            keyname_map[layer].color.h        = data[26];
            keyname_map[layer].color.s        = data[27];
            keyname_map[layer].color.v        = data[28];

            mark_layer_dirty(layer);
            break;
        }
        case id_bulk_key_data: {
            uint8_t layer = data[3];
            uint8_t key_idx = data[4];
            if (layer >= KEYNAME_MAP_MAX_LAYERS || key_idx >= KEYNAME_MAP_MAX_KEYS_PER_LAYER) break;

            char* namePtr = (char*)&data[5];
            char* imgPtr  = (char*)&data[15];
            KeyData_t* k = &keyname_map[layer].keys[key_idx];

            strncpy(k->name, namePtr, 10);
            k->name[9] = '\0';
            strncpy(k->imageName, imgPtr, 10);
            k->imageName[9] = '\0';

            k->color.h = data[25];
            k->color.s = data[26];
            k->color.v = data[27];

            mark_layer_dirty(layer);
            break;
        }

        // --- GRANULAR SET (VIA UI) ---
        // Format: [0x07] [0] [ID] [Value]
        case id_via_layer_select: if(data[3] < KEYNAME_MAP_MAX_LAYERS) via_selected_layer = data[3]; break;
        case id_via_layer_effect: keyname_map[via_selected_layer].lightingEffect = data[3]; mark_layer_dirty(via_selected_layer); break;
        case id_via_layer_speed:  keyname_map[via_selected_layer].effectSpeed = data[3]; mark_layer_dirty(via_selected_layer); break;
        case id_via_layer_hue:    keyname_map[via_selected_layer].color.h = data[3]; mark_layer_dirty(via_selected_layer); break;
        case id_via_layer_sat:    keyname_map[via_selected_layer].color.s = data[3]; mark_layer_dirty(via_selected_layer); break;
        case id_via_layer_val:    keyname_map[via_selected_layer].color.v = data[3]; mark_layer_dirty(via_selected_layer); break;

        case id_via_layer_color:
            //Built in VIA color picker sends two bytes
            keyname_map[via_selected_layer].color.h = data[3];
            keyname_map[via_selected_layer].color.s = data[4];
            mark_layer_dirty(via_selected_layer);
            break;

        case id_via_key_select:   if(data[3] < KEYNAME_MAP_MAX_KEYS_PER_LAYER) via_selected_key = data[3]; break;
        case id_via_key_hue:      keyname_map[via_selected_layer].keys[via_selected_key].color.h = data[3]; mark_layer_dirty(via_selected_layer); break;
        case id_via_key_sat:      keyname_map[via_selected_layer].keys[via_selected_key].color.s = data[3]; mark_layer_dirty(via_selected_layer); break;
        case id_via_key_val:      keyname_map[via_selected_layer].keys[via_selected_key].color.v = data[3]; mark_layer_dirty(via_selected_layer); break;
        
        case id_via_key_color:
            //Built in VIA color picker sends two bytes
            keyname_map[via_selected_layer].keys[via_selected_key].color.h = data[3];
            keyname_map[via_selected_layer].keys[via_selected_key].color.s = data[4];
            mark_layer_dirty(via_selected_layer);
            break;
    }
}

// =============================================================================
// HELPER: PROCESS GET (0x08)
// =============================================================================
void process_via_get(uint8_t *data) {
    // Format: [0x08] [Channel(0)] [ValueID] [Data...]
    if (data[1] != 0) return;

    uint8_t value_id = data[2];

    switch (value_id) {
        // --- BULK GET (Web Tool) ---
        case id_bulk_layer_data: {
            uint8_t layer = data[3]; // Request comes with layer index
            if (layer >= KEYNAME_MAP_MAX_LAYERS) break;

            strncpy((char*)&data[4], keyname_map[layer].name, 10);
            strncpy((char*)&data[14], keyname_map[layer].imageName, 10);
            data[24] = keyname_map[layer].lightingEffect;
            data[25] = keyname_map[layer].effectSpeed;
            data[26] = keyname_map[layer].color.h;
            data[27] = keyname_map[layer].color.s;
            data[28] = keyname_map[layer].color.v;
            break;
        }
        case id_bulk_key_data: {
            uint8_t layer = data[3];
            uint8_t key_idx = data[4];
            if (layer >= KEYNAME_MAP_MAX_LAYERS || key_idx >= KEYNAME_MAP_MAX_KEYS_PER_LAYER) break;

            KeyData_t* k = &keyname_map[layer].keys[key_idx];
            strncpy((char*)&data[5], k->name, 10);
            strncpy((char*)&data[15], k->imageName, 10);
            data[25] = k->color.h;
            data[26] = k->color.s;
            data[27] = k->color.v;
            break;
        }

        // --- GRANULAR GET (VIA UI Polling) ---
        // VIA might ask "What is the current value of ID 32?"
        case id_via_layer_select: data[3] = via_selected_layer; break;
        case id_via_layer_effect: data[3] = keyname_map[via_selected_layer].lightingEffect; break;
        case id_via_layer_speed:  data[3] = keyname_map[via_selected_layer].effectSpeed; break;
        case id_via_layer_hue:    data[3] = keyname_map[via_selected_layer].color.h; break;
        case id_via_layer_sat:    data[3] = keyname_map[via_selected_layer].color.s; break;
        case id_via_layer_val:    data[3] = keyname_map[via_selected_layer].color.v; break;

        case id_via_layer_color:
            //Built in VIA color picker receives two bytes
            data[3] = keyname_map[via_selected_layer].color.h;
            data[4] = keyname_map[via_selected_layer].color.s;
            break;

        case id_via_key_select:   data[3] = via_selected_key; break;
        case id_via_key_hue:      data[3] = keyname_map[via_selected_layer].keys[via_selected_key].color.h; break;
        case id_via_key_sat:      data[3] = keyname_map[via_selected_layer].keys[via_selected_key].color.s; break;
        case id_via_key_val:      data[3] = keyname_map[via_selected_layer].keys[via_selected_key].color.v; break;
        
        case id_via_key_color:
            //Built in VIA color picker receives two bytes
            data[3] = keyname_map[via_selected_layer].keys[via_selected_key].color.h;
            data[4] = keyname_map[via_selected_layer].keys[via_selected_key].color.s;
            break;
    }
}

// =============================================================================
// HELPER: PROCESS SAVE (0x09)
// =============================================================================
void process_via_save(uint8_t *data) {
    if (data[1] != 0) return;
    save_requested = true;
}

// =============================================================================
// MAIN DISPATCHER
// =============================================================================
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data[0] contains the Command ID (Set, Get, or Save)
    
    switch (data[0]) {
        case id_custom_set_value: // 0x07
            process_via_set(data);
            break;
            
        case id_custom_get_value: // 0x08
            process_via_get(data);
            break;
            
        case id_custom_save:      // 0x09
            process_via_save(data);
            break;
        
    }
    // Note: No raw_hid_send() here. QMK core handles the return.
}