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


// Each layer has a number (above enum), but this should have a defined name,
// and a name/picture for each key. So at each index in array there is a class defining the
// name, with an array of keys; each key will have a name, a picture, and an orientation (top or front)

/* KeynameMap myKeyboard({
    // Layer 0: Base Layer
    { "L0", { 
        {"Escape", "esc_icon.bin"},
        {"Tab", "tab_icon.bin"}
    }},
    // Layer 1: Function Layer
    { "L1", {
        {"F1", "f1_icon.bin"},
        {"F2", "f2_icon.bin"}
    }}
}); */


bool layer_change_toggle = false;
bool update_oled;//external variable

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

// --- Tunneling Protocol ---
// VIA uses ID 0x07 for "Custom Set Value". 
// We will wrap our commands inside this ID.
// Packet Structure: [0x07] [My_CMD] [Layer] [Key] [Data...]

enum my_custom_commands {
    id_custom_get_layer   = 0x01,
    id_custom_set_layer   = 0x02,
    id_custom_get_key     = 0x03,
    id_custom_set_key     = 0x04,
    id_custom_eeprom_save = 0x05
};

void via_custom_value_command(uint8_t *data, uint8_t length) {
    // Packet Structure: [0x07] [CMD] [Layer] [Data...]
    // Offsets:          0      1     2       3...

    uint8_t my_cmd = data[1];

    update_oled = true;

    switch (my_cmd) {
        // --- GET LAYER ---
        case id_custom_get_layer: {
            uint8_t layer = data[2];
            if (layer >= KEYNAME_MAP_MAX_LAYERS) break;

            // [0]=0x07, [1]=CMD, [2]=Layer
            // Payload starts at byte 3
            strncpy((char*)&data[3], keyname_map[layer].name, 10);
            strncpy((char*)&data[13], keyname_map[layer].imageName, 10);
            break;
        }

        // --- SET LAYER ---
        case id_custom_set_layer: {
            uint8_t layer = data[2];
            if (layer >= KEYNAME_MAP_MAX_LAYERS) break;

            char* namePtr = (char*)&data[3];
            char* imgPtr  = (char*)&data[13];

            strncpy(keyname_map[layer].name, namePtr, 10);
            keyname_map[layer].name[9] = '\0'; 

            strncpy(keyname_map[layer].imageName, imgPtr, 10);
            keyname_map[layer].imageName[9] = '\0';
            break;
        }

        // --- GET KEY ---
        case id_custom_get_key: {
            uint8_t layer = data[2];
            uint8_t key_idx = data[3];
            if (layer >= KEYNAME_MAP_MAX_LAYERS || key_idx >= KEYNAME_MAP_MAX_KEYS_PER_LAYER) break;

            // [0]=0x07, [1]=CMD, [2]=Layer, [3]=Key
            // Payload starts at byte 4
            KeyData_t* k = &keyname_map[layer].keys[key_idx];
            strncpy((char*)&data[4], k->name, 10);
            strncpy((char*)&data[14], k->imageName, 10);
            break;
        }

        // --- SET KEY ---
        case id_custom_set_key: {
            uint8_t layer = data[2];
            uint8_t key_idx = data[3];
            if (layer >= KEYNAME_MAP_MAX_LAYERS || key_idx >= KEYNAME_MAP_MAX_KEYS_PER_LAYER) break;

            char* namePtr = (char*)&data[4];
            char* imgPtr  = (char*)&data[14];

            KeyData_t* k = &keyname_map[layer].keys[key_idx];
            strncpy(k->name, namePtr, 10);
            k->name[9] = '\0';
            
            strncpy(k->imageName, imgPtr, 10);
            k->imageName[9] = '\0';
            break;
        }

        // --- SAVE ---
        case id_custom_eeprom_save:
            custom_eeprom_save();
            break;
    }
}

// TODO: Add custom lighting layer functionality to the keymap.
// TODO: Add custom VIA settings & effect per key per layer that can tell you what the key does

// Cannot do encoder map with VIA, because the map overrides our custom menu handling.
// There will be two extra keys in VIA because of this.

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {   7   ,  2,  8 ,    NO_LED },
  {   1   ,  5,  3,     NO_LED },
  { NO_LED,  6,  4,     NO_LED }
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

    // Layer 0: Base Layer
    keyname_map_set_layer_name(0, "Base");
    keyname_map_set_key_data(0, 0, "Escape", "esc.bin");
    keyname_map_set_key_data(0, 1, "Tab", "tab.bin");
    keyname_map_set_key_data(0, 14, "Backspace", "bspc.bin");

    // Layer 1: Function Layer
    keyname_map_set_layer_name(1, "Function");
    keyname_map_set_key_data(1, 0, "F1", "f1.bin");
    keyname_map_set_key_data(1, 1, "F2", "f2.bin");

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
  if (layer_change_toggle) {
    LED_indicate_layer(get_highest_layer(layer_state));
    return false;
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
    /*if (clockwise) {
      tap_code(dynamic_keymap_get_keycode(current_layer, 1, 3));//lower key
    } else {
      tap_code(dynamic_keymap_get_keycode(current_layer, 0, 3));//upper key
    }*/
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
  /*
  //string to fill and combine
  char layer_str[10];

  //convert Int to string to show layer number
  snprintf(layer_str, sizeof(layer_str), "Layer: %d", current_layer);
  
  //get width
  //default_font->line_height is the way to get the height of the font, like qp_textwidth for width
  int16_t width = qp_textwidth(default_font, layer_str);

  qp_drawtext(oled, (QP_WIDTH - width) / 2, 0, default_font, layer_str);
  */

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
}