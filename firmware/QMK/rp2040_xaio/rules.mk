# OLED_ENABLE = yes
# OLED_TRANSPORT = i2c
# OLED_DRIVER = ssd1306

# RGBLIGHT_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = vendor # This driver is RP2040 specific, use pwm for other

ENCODER_ENABLE = yes
SRC += utils/encoder_handler.c

# required for rp2040
LTO_ENABLE = yes

JOYSTICK_ENABLE = yes

# POINTING_DEVICE_DRIVER = analog_joystick

OLED_ENABLE = yes
OLED_DRIVER = ssd1306

OLED_TRANSPORT = i2c

# Bootloader selection
BOOTLOADER = rp2040

USB_WAIT_FOR_ENUMERATION = yes

USB_SUSPEND_WAKEUP_DELAY = 200

NO_USB_STARTUP_CHECK = yes