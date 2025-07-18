/* Copyright 2025 Asher Edwards
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#define KEYNAMES = 

enum layer_names {
    base,
    mod,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [base] = LAYOUT(
        KC_A, KC_B,   KC_C,   KC_D, \
        KC_F, KC_G,   KC_H,   KC_I,  \
        KC_K, KC_L,   KC_M,   KC_N
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
  // LED Index to Flag (bitmask). I enabled all flags just because
  255, 255, 255, 255, 255, 255
} };
#endif

void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom(); // enables Rgb, without saving settings
    rgb_matrix_sethsv_noeeprom(106, 255, 50);// green, full saturation, low brightness
    rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
}

//Encoder main purpose is to switch key layers and input modes (game controller, macropad, mouse, remote)

//This should be encoder matrix, which doesn't exist in QMK and I will have to write my own.
/*#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
};*/


// All below needs to be moved into a file called joykey.c, as its custom utility functions and not usr


//joystick
//if in mouse mode return mouse movements, otherwise return joystick values
// Need to write that code
/*joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(GP26, 900, 575, 285),
    JOYSTICK_AXIS_VIRTUAL
};*/

//Gyro sensor data, used for mouse, or game controller only


//wireless stuff??

/*#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    
    return false;
}
#endif*/
