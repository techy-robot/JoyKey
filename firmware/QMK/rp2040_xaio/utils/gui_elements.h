#pragma once
#include <qp.h> // QMK quantum painter library
#include <string.h>
#include <stdio.h>
#include "keyname_map.h"

// Media to include
#include "media/fonts/thintel15.qff.h"
#include "media/github-mark-white.qgf.h"
#include "media/github-mark.qgf.h"

//Stores pointers for all currently loaded images
extern painter_image_handle_t image_cache[10];

void bulk_unload(void);

int image_index_from_name(char image[KEYNAME_MAP_NAME_LENGTH]);

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
 * @param imageName The name of the key's image asset.
 */
void draw_key(bool pressed, int x, int y, int w, int h, const char* name, const char* imageName);

/**
 * @brief Draws a full key layer on the screen.
 * 
 * This function is responsible for drawing a single layer on the screen, rendering all keys in that layer.
 *
 * @param layerIndex The index of the layer to draw.
 * @param layerName The name of the layer (e.g., "Layer 1").
 */
void draw_layer(int layerIndex, char* layerName);
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
void draw_menu_item(const char* text, int x, int y, bool highlighted, bool selected);

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
void draw_menu(const char* items[], int size, int selected);

