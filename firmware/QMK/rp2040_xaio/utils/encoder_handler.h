#include QMK_KEYBOARD_H
#include "matrix.h"

#define NO_ENC 255
#define ENC_PAD_A 0
#define ENC_PAD_B 1

// Define a structure to hold a row and column pair
#ifndef ENCODER_HANDLER_H
#define ENCODER_HANDLER_H

typedef struct row_col_t { uint8_t row; uint8_t col; } row_col_t;

#endif // ENCODER_HANDLER_H

uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b);
void generate_encoder_index_to_row_col(row_col_t encoder_index_to_row_col[ENCODER_COUNT*2]);
void encoder_quadrature_init(void);
bool encoder_update_kb(uint8_t index, bool clockwise);
