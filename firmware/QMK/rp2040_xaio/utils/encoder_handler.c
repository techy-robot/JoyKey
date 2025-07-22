// Copyright 2025 asher Edwards
// Licensed under the GNU GPL v3

#include "encoder_handler.h"

extern matrix_row_t matrix[MATRIX_ROWS];

// We'll need a way to go from row/col to the index in that above array - fortunately we have a pretty convenient macro.
// key matrix to encoder index
// encoder index is split into two indeces, one for each pad. therefore the original index is multiplied by 2
uint8_t encoder_positions[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(
    NO_ENC, NO_ENC, NO_ENC, 0*2 + ENC_PAD_A,
    NO_ENC, NO_ENC, NO_ENC, 0*2 + ENC_PAD_B,
    NO_ENC, NO_ENC, NO_ENC,     NO_ENC
);

// This is a new array that maps an encoder index directly to its row/col.
row_col_t encoder_index_to_row_col[ENCODER_COUNT*2];

void generate_encoder_index_to_row_col(row_col_t encoder_index_to_row_col[ENCODER_COUNT*2]) {
    for (uint8_t r = 0; r < MATRIX_ROWS; ++r) {
        for (uint8_t c = 0; c < MATRIX_COLS; ++c) {
            if (encoder_positions[r][c] != NO_ENC) {
                encoder_index_to_row_col[encoder_positions[r][c]] = (row_col_t){.row = r, .col = c};
            }
        }
    }
}

// Whenever an encoder is turned, we need to calculate if it rotated clockwise or counter clockwise
// based on the keycodes pressed
uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b) {

    row_col_t rowCol = encoder_index_to_row_col[index + (pad_b ? ENC_PAD_B : ENC_PAD_A)];
    uint8_t rowIndex = rowCol.row;
    uint8_t colIndex = rowCol.col;

    uint8_t returnVal = (uint8_t)!!(matrix[rowIndex] & (0x1 << colIndex));
    return returnVal;
}

// custom function to handle encoder events
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
      return false; /* Don't process further events if user function exists and returns false */
    }

    return true;
}