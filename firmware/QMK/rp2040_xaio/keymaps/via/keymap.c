/* Copyright 2025 Asher Edwards
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include <string.h>
#include "media/fonts/thintel15.qff.c"
#include "utils/keyname_map.c"
#include "utils/gui_elements.c"
#include "utils/settings.c"
#include "dynamic_keymap.h"
#include "via.h"

enum my_keycodes {
  LAYR_CHNG_TGGL = SAFE_RANGE,
};

enum layer_names {
    L0,
    L1,
    L2,
    L3,
    L4,
    L5,
    L6,
    L7,
    L8,
    L9,
    L10,
    L11,
    L12,
    L13,
    L14,
    L15
};

// --- Globals ---
bool layer_change_toggle = false;

// --- Optimization: Track state to prevent unnecessary refreshes ---
bool update_oled;//external variable
static uint8_t last_rgb_mode = 255;
uint8_t via_selected_layer = 0; // Which layer is VIA currently editing?
uint8_t via_selected_key = 0; // Which key is VIA currently editing?

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap 0: Basic layer
  *
  *                 .------------.             .------------.                               
  *    _____________|   MS_BTN1  |_____________|  MS_BTN2   |____________ 
  *  /              '------------'             '------------'    MS_WHLU  \
  * |                                                              _  _    |
  * |   Joystick                                                =        = |
  * |    .-------.    .-----------.-----------.-----------.   =            =
  * |  /    _ _    \  |  MS_WHLL  |   MS_UP   |  MS_WHLR  |  =              =
  * | .  .''   ''.  . |           |           |           |  =LAYR_CHNG_TGGL=
  * | | (    K    ) | |-----------+-----------+-----------|   =            =
  * | '  '.._ _..'  ' |  MS_LEFT  |  MS_DOWN  |  MS_RGHT  |     =        = |
  * |  \           /  |           |           |           |        ~  ~    |
  * '    '-------'    '-----------'-----------'-----------'       MS_WHLD  '
  *  \                                                                    /
  *    `-- .________________________________________________________. --'
  */
  [L0] = LAYOUT(
      MS_BTN1, MS_UP,   MS_BTN2,   MS_WHLU, \
      MS_WHLL, MS_DOWN,   MS_WHLR,   MS_WHLD, \
      KC_K, MS_LEFT,   MS_RGHT,   LAYR_CHNG_TGGL
  ),
  [L1] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L2] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L3] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L4] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L5] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L6] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L7] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L8] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L9] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L10] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L11] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L12] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L13] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L14] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  ),
  [L15] = LAYOUT(
      QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, LAYR_CHNG_TGGL
  )

};

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

    // 48 - 63: VIA UI Key Controls
    id_via_key_select       = 48,
    id_via_key_hue          = 49,
    id_via_key_sat          = 50,
    id_via_key_val          = 51
};

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

        case id_via_key_select:   if(data[3] < KEYNAME_MAP_MAX_KEYS_PER_LAYER) via_selected_key = data[3]; break;
        case id_via_key_hue:      keyname_map[via_selected_layer].keys[via_selected_key].color.h = data[3]; mark_layer_dirty(via_selected_layer); break;
        case id_via_key_sat:      keyname_map[via_selected_layer].keys[via_selected_key].color.s = data[3]; mark_layer_dirty(via_selected_layer); break;
        case id_via_key_val:      keyname_map[via_selected_layer].keys[via_selected_key].color.v = data[3]; mark_layer_dirty(via_selected_layer); break;
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

        case id_via_key_select:   data[3] = via_selected_key; break;
        case id_via_key_hue:      data[3] = keyname_map[via_selected_layer].keys[via_selected_key].color.h; break;
        case id_via_key_sat:      data[3] = keyname_map[via_selected_layer].keys[via_selected_key].color.s; break;
        case id_via_key_val:      data[3] = keyname_map[via_selected_layer].keys[via_selected_key].color.v; break;
        
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

// TODO: Add custom VIA settings & effect per key per layer that can tell you what the key does

// Cannot do encoder map with VIA, because the map overrides our custom menu handling.
// There will be two extra keys in VIA because of this.

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {   6   ,  1,  7 ,    NO_LED },
  {   0   ,  4,  2,     NO_LED },
  { NO_LED,  5,  3,     NO_LED }
}, {
  // LED Index to Physical Position. For accurate animations I need to scale it to { 0..224, 0..64 }
  { 1,  1 }, { 2,  1 }, { 3,  1 }, { 4,  2 }, { 3,  2 }, { 2,  2 }, { 1,  0 }, { 4,  0 }
}, {
  // LED Index to Flag (bitmask). See https://docs.qmk.fm/features/rgb_matrix#flags
  255, 255, 255, 255, 255, 255, 255, 255
} };
#endif

void keyboard_post_init_user(void) {

    keyname_map_init(); // Zero out RAM
    custom_eeprom_load(); // Load from Flash

    layer_change_toggle = false;
    update_oled = true;

    // ---- DEFINE KEYMAP DATA ----
    // If Layer 0 has no name, assume this is a fresh install and apply defaults.
    // We check the first character of the name string.
    if (keyname_map_get_layer_name(0)[0] == '\0') {
        
        // ---- DEFINE DEFAULTS (Only runs once) ----
        
        // Layer 0: Base Layer
        keyname_map_set_layer_name(0, "Base");
        keyname_map_set_key_data(0, 0, "Escape", "esc.bin");
        keyname_map_set_key_data(0, 1, "Tab", "tab.bin");
        keyname_map_set_key_data(0, 14, "Backspace", "bspc.bin");

        // Layer 1: Function Layer
        keyname_map_set_layer_name(1, "Function");
        keyname_map_set_key_data(1, 0, "F1", "f1.bin");
        keyname_map_set_key_data(1, 1, "F2", "f2.bin");
        
        // Save
        mark_layer_dirty(0);
        mark_layer_dirty(1);
        save_requested = true;
    }

    gui_elements_init(oled, default_font);//font_arial_12 option??

}

void LED_indicate_layer(uint8_t layer) {

  // Variables to store the color components and the number of LEDs to light.
  uint8_t target_hue, target_sat, target_val;
  uint8_t leds_to_illuminate;

  // Layers > 5 (rollover): Stacking effect resets, and color changes
  // The stacking count rolls over from 1 to NUM_LAYER_LEDS based on the layer modulo NUM_LAYER_LEDS.
  leds_to_illuminate = (layer % RGB_MATRIX_LED_COUNT) + 1;

  // Calculate the hue based on the layer offset for color cycling.
  uint8_t layer_offset_for_hue = layer / RGB_MATRIX_LED_COUNT;//rounds down naturally with truncate

  // QMK's 0-255 range.
  target_hue = (layer_offset_for_hue * 20) % 255; // 20-point increments, wrap at 255
  target_sat = 255; // Full saturation for vibrant colors
  target_val = 255; // Full brightness
  
  // Iterate through all the layer indicator LEDs.
  for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
      // If the current LED index is less than the number of LEDs we want to light for stacking
      if (i < leds_to_illuminate) {
              // If using HSV, set the color with the calculated HSV values.
              rgb_t rgb = hsv_to_rgb((hsv_t){target_hue, target_sat, target_val});
              rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
      } else {
          // If the current LED index is beyond the number of LEDs to light, turn it off.
          rgb_matrix_set_color(i, 0, 0, 0);
      }
  }
}

bool rgb_matrix_indicators_user(void) {

  uint8_t current_layer = get_highest_layer(layer_state);
  LayerData_t *layer_ptr = &keyname_map[current_layer]; // Use pointer to save stack memory

  // GLOBAL LAYER EFFECT
  // Only update mode/speed/hsv if the mode actually changed.
  // Otherwise, we reset the animation timer constantly, freezing the effect.
  if (last_rgb_mode != layer_ptr->lightingEffect) {
      rgb_matrix_mode_noeeprom(layer_ptr->lightingEffect);
      last_rgb_mode = layer_ptr->lightingEffect;
  }

  rgb_matrix_set_speed_noeeprom(layer_ptr->effectSpeed);
  rgb_matrix_sethsv_noeeprom(layer_ptr->color.h, layer_ptr->color.s, layer_ptr->color.v);

  // PER-KEY OVERRIDES
  // This must run every frame to overlay on top of the active animation
  for (uint8_t i = 0; i < KEYNAME_MAP_MAX_KEYS_PER_LAYER; i++) {
    KeyData_t *key = &layer_ptr->keys[i];

    // Check for "Empty" color (Black). 
    // Assuming 0,0,0 means "Follow Layer Default".
    if (key->color.h == 0 && key->color.s == 0 && key->color.v == 0) {
      continue;
    }

    // Safety check: Ensure we don't go out of bounds of your LED config
    // defined in g_led_config
    uint8_t row = i / MATRIX_COLS;
    uint8_t col = i % MATRIX_COLS;
    
    if (row >= 3) continue; // Safety break

    uint8_t LED_index = g_led_config.matrix_co[row][col];
    
    if (LED_index != NO_LED) {
        // Calculate RGB and set
        rgb_t rgb = hsv_to_rgb(key->color);
        rgb_matrix_set_color(LED_index, rgb.r, rgb.g, rgb.b);
    }
  }

  return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  uint8_t current_layer = get_highest_layer(layer_state);

  if (index == 0) { /* First encoder */
    if (layer_change_toggle) {/* If the encoder changes layers, disable further processing*/

      // Check if we are within the range, if not quit
      if (current_layer > DYNAMIC_KEYMAP_LAYER_COUNT || current_layer < 0) {
        return false;
      }

      uint8_t next_layer;

      if (clockwise) {
        next_layer = (current_layer + 1) % DYNAMIC_KEYMAP_LAYER_COUNT; // Roll over to the next layer
      } else {
        next_layer = (current_layer - 1 + DYNAMIC_KEYMAP_LAYER_COUNT) % DYNAMIC_KEYMAP_LAYER_COUNT; // Roll over to the previous layer
      }
      layer_move(next_layer);

      update_oled = true;//layer chanes need the whole display refreshed, so numbers aren't erased

      return false;
    }

    //VIA handler, gets whatever key on the current layer for the encoder
    if (clockwise) {
      tap_code(dynamic_keymap_get_keycode(current_layer, 1, 3));//lower key
    } else {
      tap_code(dynamic_keymap_get_keycode(current_layer, 0, 3));//upper key
    }
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  update_oled = true;//keycode changes need the display refreshed
  switch (keycode) {
    case LAYR_CHNG_TGGL:
      if (record->event.pressed) {
        // toggles if the encoder changes layers or not
        layer_change_toggle = !layer_change_toggle;
      }
      //return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

void display_task(void) {
  //qp_clear(oled);//clean slate, it may be a little slower but I don't want to do selective overwrite.
  //Note that clear prevents the display from sleeping

  uint8_t current_layer = get_highest_layer(layer_state);

  draw_layer(current_layer);

  qp_flush(oled);
}

void housekeeping_task_user(void) {
  static uint32_t last_draw = 0;

  if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
    last_draw = timer_read32();

    //variable refresh rate, only refresh if something has changed. Cuts down on i2c usage
    if (update_oled) {
      display_task();
      update_oled = false;
    }
  }

  //save data if it changed, make sure it is kept up to date
  refresh_settings();
  
}