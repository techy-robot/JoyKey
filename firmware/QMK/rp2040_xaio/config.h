/*
Copyright 2025 Asher Edwards

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//#pragma once

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { GP28, GP29, GP0 }
#define MATRIX_COL_PINS { GP4, GP1, GP2, GP27 } // GP27 is hyjacked joystick y pin.

/* COL2ROW for me, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

//#define ENCODER_MAP_KEY_DELAY 10

#define WS2812_DI_PIN GP3
#define RGBLIGHT_LED_COUNT 6 //6 for basic, 10 for radio one
#define RGB_MATRIX_CENTER { 2, 1 } //Key 2. For accurate animations I need it in center of { 0..224, 0..64 }



//#define I2C_DRIVER I2CD1
//#define I2C1_SDA_PIN GP6
//#define I2C1_SCL_PIN GP7

// Min 0, max 32
//#define JOYSTICK_BUTTON_COUNT 1
// Min 0, max 6: X, Y, Z, Rx, Ry, Rz
//#define JOYSTICK_AXIS_COUNT 2
// Min 8, max 16
//#define JOYSTICK_AXIS_RESOLUTION 10

//#define ANALOG_JOYSTICK_X_AXIS_PIN GP26
//#define ANALOG_JOYSTICK_Y_AXIS_PIN GP27

//Left trigger
#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 0

//DFU only, RP2040 has UF2
//#define QMK_LED GP3
