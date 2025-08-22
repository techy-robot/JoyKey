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
#include "utils/robotomono20.qff.c"

enum my_keycodes {
  LAYR_CHNG_TGGL = SAFE_RANGE,
};

enum layer_names {
    base,
    layer1,
    layer2,
    layer3,
    layer4,
    layer5,
    layer6,
    layer7
};

bool layer_change_toggle = false;

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
  [base] = LAYOUT(
      MS_BTN1, MS_UP,   MS_BTN1,   MS_WHLU, \
      MS_WHLL, KC_MS_DOWN,   MS_WHLR,   MS_WHLD, \
      KC_K, MS_LEFT,   MS_RGHT,   LAYR_CHNG_TGGL
  )
};

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
    layer_change_toggle = false;
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
        next_layer = MAX(current_layer - 1, 0);//ensure that we don't go below 0
      } else {
        next_layer = MIN(current_layer + 1, DYNAMIC_KEYMAP_LAYER_COUNT);//ensure that we don't go above max layer count
      }
      layer_move(next_layer);

      //oled_clear();//layer chanes need the whole display refreshed.

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
  switch (keycode) {
    case LAYR_CHNG_TGGL:
      if (record->event.pressed) {
        // toggles if the encoder changes layers or not
        layer_change_toggle = !layer_change_toggle;
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

/*
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees because its upside down.
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

// Draw to OLED
bool oled_task_user() {
    // Set cursor position to middle top
    oled_set_cursor((oled_max_chars() - 8) / 2, 2); //Max width minus space taken by text, divided by 2

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer:"), false);

    //convert Int to string to show layer number
    char layer_str[10];
    snprintf(layer_str, sizeof(layer_str), "%d", get_highest_layer(layer_state));
    oled_write(layer_str, false);
        
    //write layer name.

    return false;
}

#endif
*/