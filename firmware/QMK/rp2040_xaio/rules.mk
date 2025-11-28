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
       utils/gui_elements.c \
       utils/ff16/ffsystem.c \
       utils/ff16/ffunicode.c \
       utils/ff16/diskio.c \
       media/fonts/thintel15.qff.c \
       media/github-mark-white.qgf.c \
       media/github-mark.qgf.c \
       media/ignore.qgf.c

# --- Mass Storage & Filesystem Configuration ---

# 1. Custom Glue Code
SRC += utils/msc_disk.c

# 2. ChibiOS Drivers (USB Mass Storage)
# USE RELATIVE PATHS (No $(QMK_TOP))
SRC += lib/chibios-contrib/os/hal/src/hal_usb_msd.c
SRC += lib/chibios-contrib/os/various/lib_scsi.c

# 3. FatFS Core (Local Vendor)
SRC += utils/ff16/ff.c

# 4. Include Directories (Headers)
# Add system paths for the MSD driver (Relative to QMK Root)
EXTRAINCDIRS += lib/chibios-contrib/os/hal/include
EXTRAINCDIRS += lib/chibios-contrib/os/various

# Add LOCAL path for msc_disk.h
EXTRAINCDIRS += $(KEYBOARD_PATH)/utils

# Add LOCAL path for ff.h
EXTRAINCDIRS += $(KEYBOARD_PATH)/utils/ff16

# 5. Required Flags
OPT_DEFS += -DHAL_USE_USB_MSD=TRUE
OPT_DEFS += -DHAL_USE_COMMUNITY=TRUE
OPT_DEFS += -DCH_CFG_USE_WAITEXIT=TRUE

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

QUANTUM_PAINTER_NUM_IMAGES = 12

# Bootloader selection
BOOTLOADER = rp2040

USB_WAIT_FOR_ENUMERATION = yes

USB_SUSPEND_WAKEUP_DELAY = 200

NO_USB_STARTUP_CHECK = yes