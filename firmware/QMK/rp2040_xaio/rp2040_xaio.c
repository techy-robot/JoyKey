// Copyright 2025 asher Edwards
// Licensed under the GNU GPL v3

/*
 * Keyboard specific file for Joykey, contianing all utility functions
*/

#include QMK_KEYBOARD_H
#include "rp2040_xaio.h"

extern row_col_t encoder_index_to_row_col[ENCODER_COUNT*2];

void keyboard_post_init_kb(void) {
    //layer_on(1);//change layers

    debug_enable=true;

    generate_encoder_index_to_row_col(encoder_index_to_row_col);
    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    keypos_t keypos = record->event.key;

    // ignore the encoder keys, because we will process the keycodes assigned in the encoder section
    if ((keypos.row == 0 || keypos.row == 1) && keypos.col == 3) {
        return false;
    }

    if (!process_record_user(keycode, record)) {
      return false; /* Don't process further events if user function exists and returns false */
    }

    return true;
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
