# OLED_ENABLE = yes
# OLED_TRANSPORT = i2c
# OLED_DRIVER = ssd1306

# RGBLIGHT_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = vendor # This driver is RP2040 specific, use pwm for other

ENCODER_ENABLE = yes
SRC += utils/encoder_handler.c \
       utils/keyname_map.c \
       utils/settings.c \
       utils/via_handler.c \
       utils/gui_elements.c \
       utils/menu_display.c \
       media/fonts/thintel15.qff.c

# required for rp2040
LTO_ENABLE = yes

JOYSTICK_ENABLE = yes

# POINTING_DEVICE_DRIVER = analog_joystick

# testing for QP instead
OLED_ENABLE = no
OLED_DRIVER = ssd1306

OLED_TRANSPORT = i2c

# advanced graphics
QUANTUM_PAINTER_ENABLE = yes
# For I2C, very much same as ssd1306
QUANTUM_PAINTER_DRIVERS += sh1106_i2c

# Bootloader selection
BOOTLOADER = rp2040

USB_WAIT_FOR_ENUMERATION = yes

USB_SUSPEND_WAKEUP_DELAY = 200

NO_USB_STARTUP_CHECK = yes