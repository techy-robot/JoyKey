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

#include "print.h"

enum my_keycodes {
  KC_ENC = SAFE_RANGE,
  KC_SEND_MSG
};

enum layer_names {
    base,
    mod
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [base] = LAYOUT(
        KC_A, KC_B,   QK_BOOT,   KC_ENC, \
        KC_F, KC_G,   KC_H,   KC_ENC, \
        KC_K, DB_TOGG,   KC_SEND_MSG,   KC_N
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
    rgb_matrix_enable_noeeprom(); // enables Rgb, without saving settings
    rgb_matrix_sethsv_noeeprom(106, 255, 80);// green, full saturation, low brightness
    rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    printf("Encoder %d turned %s\n", index, clockwise ? "clockwise" : "counterclockwise");
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SEND_MSG:
      if (record->event.pressed) {
        // Do something when pressed
        print("Hello World!\n");
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}