
#include "utils/encoder_handler.h"
#include "print.h"

#include "qp.h"
#include "qp_comms.h"
#include "qp_sh1106_opcodes.h"

#include "color.h"
#include "config.h"

#include "media/fonts/thintel15.qff.h"

extern painter_device_t oled;
extern painter_font_handle_t default_font;

void keyboard_post_init_kb(void);

bool process_record_kb(uint16_t keycode, keyrecord_t *record);

