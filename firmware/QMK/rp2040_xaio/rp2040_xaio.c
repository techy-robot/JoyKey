// Copyright 2025 asher Edwards
// Licensed under the GNU GPL v3

/*
 * Keyboard specific file for Joykey, contianing all utility functions
*/

#include QMK_KEYBOARD_H
#include "rp2040_xaio.h"

painter_device_t oled;
painter_font_handle_t default_font;

extern row_col_t encoder_index_to_row_col[ENCODER_COUNT*2];

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
  // Key Matrix to LED Index. [1][0] had to be swapped for faulty, so there is one less LED
  {   5   ,  0,  6 ,    NO_LED },
  {   0   ,  3,  1,     NO_LED },
  { NO_LED,  4,  2,     NO_LED }
}, {
  // LED Index to Physical Position. For accurate animations it is scaled  to { 0..224, 0..64 }
  { 112,  32 }, { 168,  32 }, { 224,  64 }, { 168,  64 }, { 112,  64 }, { 56,  0 }, { 224,  0 }
}, {
  // LED Index to Flag (bitmask). See https://docs.qmk.fm/features/rgb_matrix#flags
  255, 255, 255, 255, 255, 255, 255
} };
#endif

void keyboard_post_init_kb(void) {

    generate_encoder_index_to_row_col(encoder_index_to_row_col);
    //disable the multicolor LED that always turns on at boot
    gpio_set_pin_input_high(INDICATOR_RED);
    gpio_set_pin_input_high(INDICATOR_GREEN);
    gpio_set_pin_input_high(INDICATOR_BLUE);

    default_font = qp_load_font_mem(font_thintel15);

    oled = qp_sh1106_make_i2c_device(QP_WIDTH, QP_HEIGHT, 0x3c);//width, height, i2c address
    qp_init(oled, QP_ROTATION_180);

    // Display offset
    qp_set_viewport_offsets(oled, QP_OFFSET_X, QP_OFFSET_Y);

    // Power on display
    qp_power(oled, 1);

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

//joystick
//if in mouse mode return mouse movements, otherwise return joystick values
// Need to write that code
/*joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(GP26, 900, 575, 285),
    JOYSTICK_AXIS_VIRTUAL
};*/

//Gyro sensor data, used for mouse, or game controller only
