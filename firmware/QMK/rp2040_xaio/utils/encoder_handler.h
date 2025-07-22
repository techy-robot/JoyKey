#include QMK_KEYBOARD_H
#include "matrix.h"
#include "print.h"

#define NO_ENC 255
#define ENC_PAD_A 0
#define ENC_PAD_B 1

// Define a structure to hold a row and column pair
#ifndef ENCODER_HANDLER_H
#define ENCODER_HANDLER_H

typedef struct row_col_t { uint8_t row; uint8_t col; } row_col_t;

#endif // ENCODER_HANDLER_H

/// @brief Generates the encoder_index_to_row_col array, from encoder_positions, a 2D LAYOUT array
// Its size is determined by the maximum encoder index * 2 because we have two encoder pads
/*#define GENERATE_ENCODER_INDEX_TO_ROW_COL() \
    row_col_t encoder_index_to_row_col[ENCODER_COUNT*2]; \
    static const bool __attribute__((unused)) __generate_encoder_index_map = ( \
        { \
            for (uint8_t r = 0; r < MATRIX_ROWS; ++r) { \
                for (uint8_t c = 0; c < MATRIX_COLS; ++c) { \
                    if (encoder_positions[r][c] != NO_ENC) { \
                        encoder_index_to_row_col[encoder_positions[r][c]] = (row_col_t){.row = r, .col = c}; \
                    } \
                } \
            } \
            true; \
        } \
    );*/

uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b);
void generate_encoder_index_to_row_col(row_col_t encoder_index_to_row_col[ENCODER_COUNT*2]);
void encoder_quadrature_init(void);
bool encoder_update_kb(uint8_t index, bool clockwise);
