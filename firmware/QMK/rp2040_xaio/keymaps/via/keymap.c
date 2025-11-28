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
#include "media/fonts/thintel15.qff.h"
#include "gui.c"
#include "utils/settings.h"
#include "utils/keyname_map.h"
#include "utils/msc_disk.h"

enum my_keycodes {
  LAYR_CHNG_TGGL = SAFE_RANGE,
  KC_USB_MNT, // "USB Maintenance"
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

static uint8_t last_rgb_mode = 255;

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

// Cannot do encoder map with VIA, because the map overrides our custom menu handling.
// There will be two extra keys in VIA because of this.

void keyboard_post_init_user(void) {

    init_mass_storage();
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

    gui_init();//font_arial_12 option??

    painter_image_handle_t img = qp_load_image_mem("joykey_logo.qgf");
    
    if (img) {
        qp_drawimage(oled, 0, 0, img);
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

    case KC_USB_MNT:
      if (record->event.pressed) {
        // Toggle the mode safely
        toggle_msc_mode();
        
        // Visual feedback (Optional but recommended)
        // qp_draw_text(oled, 0, 0, "USB MODE: SWAPPED");
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}

void housekeeping_task_user(void) {
  
  if (save_requested) {
    update_oled = true;//saved changes need the display refreshed
  }
  gui_refresh(layer_change_toggle);
  //save data if it changed, make sure it is kept up to date
  refresh_settings();
  
}