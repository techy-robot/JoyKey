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
  *    _____________|    KC_A    |_____________|  QK_BOOT   |____________ 
  *  /              '------------'             '------------'    MS_WHLU  \
  * |                                                              _  _    |
  * |   Joystick                                                =        = |
  * |    .-------.    .-----------.-----------.-----------.   =            =
  * |  /    _ _    \  |     F     |     B     |     H     |  =              =
  * | .  .''   ''.  . |           |           |           |  =LAYR_CHNG_TGGL=
  * | | (    K    ) | |-----------+-----------+-----------|   =            =
  * | '  '.._ _..'  ' |     L     |     G     |     M     |     =        = |
  * |  \           /  |           |           |           |        ~  ~    |
  * '    '-------'    '-----------'-----------'-----------'       MS_WHLD  '
  *  \                                                                    /
  *    `-- .________________________________________________________. --'
  */

  [base] = LAYOUT(
      KC_A, KC_B,   QK_BOOT,   MS_WHLU, \
      KC_F, KC_G,   KC_H,   MS_WHLD, \
      KC_K, KC_L,   KC_M,   LAYR_CHNG_TGGL
  )
};

#ifdef RGB_MATRIX_ENABLE
/*led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 9,  2, 10, NO_LED },
  { 1,  6,  3,     4   },
  { 8,  7,  5, NO_LED }
}, {
  // LED Index to Physical Position. For accurate animations I need to scale it to { 0..224, 0..64 }
  { 1,  1 }, { 2,  1 }, { 3,  1 }, { 4,  2 }, { 3,  2 }, { 2,  2 }, { 1,  2 }, { 0,  2 }, { 0,  0 }, { 4,  0 }
}, {
  // LED Index to Flag (bitmask). I enabled all flags just because
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255
} };*/

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { NO_LED,  2, NO_LED, NO_LED },
  {   1   ,  5,  3,     NO_LED },
  { NO_LED,  6,  4,     NO_LED }
}, {
  // LED Index to Physical Position. For accurate animations I need to scale it to { 0..224, 0..64 }
  { 1,  1 }, { 2,  1 }, { 3,  1 }, { 4,  2 }, { 3,  2 }, { 2,  2 }
}, {
  // LED Index to Flag (bitmask). See https://docs.qmk.fm/features/rgb_matrix#flags
  255, 255, 255, 255, 255, 255
} };
#endif

void keyboard_post_init_user(void) {
    layer_change_toggle = false;
    rgb_matrix_enable_noeeprom(); // enables Rgb, without saving settings
    rgb_matrix_sethsv_noeeprom(106, 255, 80);// green, full saturation, low brightness
    rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
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