# OLED_ENABLE = yes
# OLED_TRANSPORT = i2c
# OLED_DRIVER = ssd1306

# RGBLIGHT_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = vendor # This driver is RP2040 specific, use pwm for other

ENCODER_ENABLE = yes
# Code Files # Media Files
SRC += utils/encoder_handler.c \
       utils/keyname_map.c \
       utils/settings.c \
       utils/via_handler.c \
       utils/gui_elements.c

# Media Files
SRC +=   media/fonts/thintel15.qff.c \
         media/github-mark-white.qgf.c \
         media/github-mark.qgf.c \
         media/ignore.qgf.c \
         media/Arrows_Left_West.qgf.c \
         media/Arrows_Right_East.qgf.c \
         media/Arrows_Down_South.qgf.c \
         media/Arrows_Up_North.qgf.c \
         media/Arrows_Pointer_Left_West.qgf.c \
         media/Arrows_Pointer_Right_East.qgf.c \
         media/Arrows_Pointer_Down_South.qgf.c \
         media/Arrows_Pointer_Up_North.qgf.c \
         media/Controller_Buttons_Left_Trigger_LT.qgf.c \
         media/Controller_Buttons_Right_Trigger_RT.qgf.c \
         media/Software_Hardware_Keyboard_Keys_Text_Input.qgf.c \
         media/Software_Image_File_Picture_Framed_Painting_Landscape_Photo_Decoration.qgf.c

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