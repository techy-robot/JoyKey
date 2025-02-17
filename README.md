---
modified: 2025-02-11T08:44:54-07:00
---
# JoyKey
This is a small macropad that simultaneously acts as game controller and an entertainment device. 

The name is inspired by the Nintendo JoyCon portmanteau (Joystick Controller) except I have replaced the 2nd word with "Keypad" (Joystick Keypad). See [name ideas](name%20ideas.md) for other things I came up with.

# Features
- Customizable macro pad using KMK firmware
- Game controller mimicking a joy-con
- Offline games that can be played on the display with no connections
- Small handheld size
- Linear keys


# BOM
- 8 Cherry mx Red keys with clear shell varient
- 8 Black keycaps
- 1 Analog PS2 Joystick (I already have)
- 1 EC11 encoder (flat volume dial on the side)
- 128x64 px SSD1306-based monochrome display near the top
- SEEED Xiao RP2040 (can be replaced w/ SEEED xiao MG24 or nRF52840 Sense for BLE, IMU, and battery charging)
- 10 Sk6812 Mini-E reverse mount RGB leds
- 3 M3x16 screws and M3 heatsets

# A Note on Project Management
This project is managed transparently in this very repo. I am using Obsidian.md as my notetaking, documentation, and project management tool. A lot of the markdown files you will see in this repo might look a bit weird; that is due to the Wiki-links instead of markdown links and the YAML file front-matter that Obsidian supports. My system works well for one person, but I'm not sure how future proof this system is. You can find my sample vault here, which explains more: [GitHub - techy-robot/Project-Management-Obsidian-Sample-Vault](https://github.com/techy-robot/Project-Management-Obsidian-Sample-Vault). 
