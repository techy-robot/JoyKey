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

#pragma once

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { GP28, GP29, GP0 }
#define MATRIX_COL_PINS { GP4, GP1, GP2, GP27 } // GP27 is hyjacked joystick y pin.

#define DYNAMIC_KEYMAP_LAYER_COUNT 16

/* COL2ROW for me, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

//#define ENCODER_MAP_KEY_DELAY 10

#define ENCODER_COUNT 1
#define ENCODER_RESOLUTION 2
#define ENCODER_DIRECTION_FLIP
#define TAP_CODE_DELAY 10

/* LED matrix*/
#define WS2812_DI_PIN GP3
//6 for basic, 10 for radio one
#define RGB_MATRIX_LED_COUNT 7
//Key 2. For accurate animations I need it in center of { 0..224, 0..64 }
#define RGB_MATRIX_CENTER { 2, 1 }

#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL	Enables
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_STARLIGHT	Enables
#define ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH
#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
#define ENABLE_RGB_MATRIX_RIVERFLOW

#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN

// These require additional memory
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

// disable backlight when USB suspended (sleep/hibernate/shutdown)
#define RGB_MATRIX_SLEEP

// 5 minute timeout in milliseconds
#define RGB_MATRIX_TIMEOUT 300000

/* Single Neopixel, 2 LED lines not supported in QMK*/

/* Single RGB (IDK why Xaio RP2040 has both)*/
#define INDICATOR_RED GP17
#define INDICATOR_GREEN GP16
#define INDICATOR_BLUE GP25

#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

#define OLED_BRIGHTNESS 128
#define OLED_DISPLAY_128X64

#define QP_OFFSET_X 0
#define QP_OFFSET_Y 0
#define QP_WIDTH 128
#define QP_HEIGHT 64


// The size of the "fake" EEPROM exposed to your code
#define WEAR_LEVELING_LOGICAL_SIZE 8192
#define WEAR_LEVELING_BACKING_SIZE 16384

// Timeout configuration, default 30000 (30 seconds). 0 = No timeout.
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 30000

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

//#undef NO_PRINT
//#undef NO_DEBUG

//DFU only, RP2040 has UF2
//#define QMK_LED GP3
