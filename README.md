---
modified: 2025-02-20T21:09:22-07:00
---
# JoyKey
This is a small macropad that simultaneously acts as game controller and an entertainment device. 

![](media/Real%20Life%20Photo.jpg)

The name is inspired by the Nintendo JoyCon portmanteau (Joystick Controller) except I have replaced the 2nd word with "Keypad" (Joystick Keypad). See [name ideas](name%20ideas.md) for other things I came up with.

My main repo were development will continue: https://github.com/techy-robot/JoyKey

# Features
- Customizable macro pad using QMK firmware
- Game controller mimicking a joy-con
- Offline games that can be played on the display with no connections
- Small handheld size
- Linear keys

# Approoved Parts BOM
- 8 Cherry mx Red keys with clear shell variant
- 8 Black keycaps
- 128x64 px SSD1306-based monochrome display near the top
- SEEED Xiao RP2040 (can be replaced later w/ SEEED xiao MG24 or nRF52840 Sense for BLE and other goodies)
- 12 Sk6812 Mini-E reverse mount RGB leds
- 3 M3x16 screws and M3 heatsets

# Extra Parts BOM
- 1 Analog PS2 Joystick (I already have)
- 1 Alps SRBE110301. (flat volume dial on the side). LCSC #C160861
- AP2112K-3.3 Linear Regulator. LCSC #C51118
- MCP73831T-2ACI/OT Lipo Battery Charger. LCSC #C424093
- 4 10uf 0805 capacitors. LCSC #C15850
- DMG3415 Sot23-3 PMOS. LCSC #C7202986
- 3 10k 0805 resistors. LCSC #C17414
- 1 2k 0805 resistor. LCSC #C17604
- 1 0603 LED. LCSC #C2286
- 1 LSM6DS3 LCSC #C967633
- JST PH S2B smd LCSC #C295747
- 12 1N4148W diodes LCSC #C2128
- 1 MBR0540 schotkey LCSC #C78545

# Pictures

## Case
![](media/Case%20Bottom.png)

![](media/Case%20Front.png)

![](media/Case%20Inside.png)

![](media/Case%20Top.png)

![](media/Final%20View.png)

## PCB
Bottom
![](media/Board%20Bottom.png)
Top
![](media/Board%20Top.png)

## Schematic
![](media/Schem%201.png)

![](media/Schem%202.png)

![](media/Schem%203.png)

![](media/Schem%204.png)

![](media/Schem%205.png)

# Sprite Credit

All icons that are converted using qmk's command line tool were originally from Nikoichu's 1-bit Pixel Icons set, which is licensed CC0 1.0