#pragma once
#include <qp.h> // QMK quantum painter library
#include <string.h>
#include <stdio.h>
#include "keyname_map.h"

// Media to include
#include "media/fonts/thintel15.qff.h"
#include "media/github-mark.qgf.h"
#include "media/ignore.qgf.h"
#include "media/Arrows_Up_North.qgf.h"
#include "media/Arrows_Down_South.qgf.h"
#include "media/Arrows_Left_West.qgf.h"
#include "media/Arrows_Right_East.qgf.h"
#include "media/Arrows_Pointer_Up_North.qgf.h"
#include "media/Arrows_Pointer_Down_South.qgf.h"
#include "media/Arrows_Pointer_Left_West.qgf.h"
#include "media/Arrows_Pointer_Right_East.qgf.h"
#include "media/Controller_Buttons_Left_Trigger_LT.qgf.h"
#include "media/Controller_Buttons_Right_Trigger_RT.qgf.h"
#include "media/Software_Hardware_Keyboard_Keys_Text_Input.qgf.h"
#include "media/Software_Image_File_Picture_Framed_Painting_Landscape_Photo_Decoration.qgf.h"

//Stores pointers for all currently loaded images
extern painter_image_handle_t image_cache[KEYNAME_MAP_MAX_KEYS_PER_LAYER];

#define ALL_IMAGES 14

extern char* all_image_names[ALL_IMAGES];

//This is for more efficient hard coding the images you want
enum all_image_name_ids {
    image_github = 0,
    image_ignore = 1,
    image_up = 2,
    image_down = 3,
    image_left = 4,
    image_right = 5,
    image_u_point = 6,
    image_d_point = 7,
    image_l_point = 8,
    image_r_point = 9,
    image_left_trig = 10,
    image_right_trig = 11,
    image_keyboard = 12,
    image_image = 13
};

void bulk_unload(void);

uint8_t image_index_from_name(const char image[KEYNAME_MAP_NAME_LENGTH]);

painter_image_handle_t load_image(uint8_t image_id);

void bulk_load(char names[10][KEYNAME_MAP_NAME_LENGTH]);

/**
 * @brief Initializes the GUI elements.
 * 
 * This function is responsible for capturing the quantum painer display object to be used by the other functions,
 * and clearing the screen on init.
 * 
 */
void gui_elements_init(void);

/**
 * @brief Draws a key on the screen.
 * 
 * This function is responsible for drawing a single key on the screen in any location.
 *
 * @param pressed Whether the key is currently pressed and should render that way.
 * @param x The x-coordinate of the top-left corner of the key.
 * @param y The y-coordinate of the top-left corner of the key.
 * @param w The width of the key.
 * @param h The height of the key.
 * @param name The name of the key (e.g., "Enter").
 * @param image_cache_id The ID of the image to use for the key.
 */
void draw_key(bool pressed, uint8_t x, uint8_t y, uint8_t w, uint8_t h, const char* name, uint8_t image_cache_id);

/**
 * @brief Draws a full key layer on the screen.
 * 
 * This function is responsible for drawing a single layer on the screen, rendering all keys in that layer.
 *
 * @param layerIndex The index of the layer to draw.
 * @param layerName The name of the layer (e.g., "Layer 1").
 */
void draw_layer(uint8_t layerIndex, char* layerName);
/** 
 * @brief Draws the name of a layer on the screen.
 * 
 * This function is responsible for drawing the name of a layer on the screen.
 *
 * @param name The name of the layer (e.g., "Layer 1").
 */


void draw_layer_name(const char* name);

/**
 * @brief Draws a menu item on the screen.
 * 
 * This function is responsible for drawing a single menu item on the screen.
 *
 * @param text The text to display on the menu item.
 * @param x The x-coordinate of the top-left corner of the menu item.
 * @param y The y-coordinate of the top-left corner of the menu item.
 * @param highlighted Whether the menu item is currently highlighted (invert background color of the text box)
 * @param selected Whether the menu item is currently selected (renders pressed down similar to a key)
 */
void draw_menu_item(const char* text, uint8_t x, uint8_t y, bool highlighted, bool selected);

/**
 * @brief Draws the menu on the screen.
 * 
 * This function is responsible for drawing a menu on the screen, rendering all menu items.
 * It deals with scrolling text (no animation) and rendering more than can fit on screen. No logic
 * for menu navigation.
 *
 * @param items The array of menu items.
 * @param size The number of menu items in the array.
 * @param selected The index of the currently selected menu item.
 */
void draw_menu(const char* items[], uint8_t size, uint8_t selected);

