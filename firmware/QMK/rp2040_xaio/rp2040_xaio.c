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

void keyboard_post_init_kb(void) {

    generate_encoder_index_to_row_col(encoder_index_to_row_col);
    //disable the multicolor LED that always turns on at boot
    gpio_set_pin_input_high(INDICATOR_RED);
    gpio_set_pin_input_high(INDICATOR_GREEN);
    gpio_set_pin_input_high(INDICATOR_BLUE);

    //Display timeout for initialization
    wait_ms(QP_WAIT_TIME);

    default_font = qp_load_font_mem(font_thintel15);

    oled = qp_sh1106_make_i2c_device(QP_WIDTH, QP_HEIGHT, 0x3c);//width, height, i2c address
    qp_init(oled, QP_ROTATION_180);

    // Display offset
    qp_set_viewport_offsets(oled, QP_OFFSET_X, QP_OFFSET_Y);

    // Power on display
    qp_power(oled, 1);

    if (default_font != NULL) {
        static const char *text = "Hello QMK!";
        int16_t width = qp_textwidth(default_font, text);
        qp_drawtext(oled, (QP_WIDTH - width), (QP_HEIGHT - default_font->line_height), default_font, text);
    }

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
