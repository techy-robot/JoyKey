# OLED_ENABLE = yes
# OLED_TRANSPORT = i2c
# OLED_DRIVER = ssd1306

# RGBLIGHT_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = vendor # This driver is RP2040 specific, use pwm for other


# ENCODER_ENABLE = yes
# ENCODER_MAP_ENABLE = yes
# required for rp2040
LTO_ENABLE = yes

JOYSTICK_ENABLE = yes

# POINTING_DEVICE_DRIVER = analog_joystick

# Bootloader selection
BOOTLOADER = rp2040