#include QMK_KEYBOARD_H
#include "utils/gui_elements.h"
#include <qp.h>

// Prototypes
void display_task(void);
void gui_init(void);
void gui_refresh(bool layer_change_toggle);

extern bool update_oled;
bool update_oled = false;//external variable

bool layer_change = false;
static uint8_t last_layer = 255;

void gui_init() {

    // Initialize the GUI elements
    gui_elements_init();

};

void image_handler(uint8_t layer) {

    //if layer change unload and load correct images
    if (layer != last_layer) {
        bulk_unload();

        for (uint8_t i = 0; i < KEYNAME_MAP_MAX_KEYS_PER_LAYER; i++) {
            image_cache[i] = load_image(image_index_from_name(keyname_map[layer].keys[i].imageName));
        }

        last_layer = layer;
    }

    //refresh loaded icons if the settings have changed for the current layer
    if (layer_dirty[layer] == true) {
        bulk_unload();

        for (uint8_t i = 0; i < KEYNAME_MAP_MAX_KEYS_PER_LAYER; i++) {
            image_cache[i] = load_image(image_index_from_name(keyname_map[layer].keys[i].imageName));
        }
    }
}


/**
 * This is the main menu system, which deals with updating the menu on the screen and all logic
 * for menu navigation, display stats, scrolling, etc...
 */
void display_task() {
    qp_clear(oled);//clean slate, it may be a little slower but I don't want to do selective overwrite.
    //Note that clear prevents the display from sleeping

    uint8_t current_layer = get_highest_layer(layer_state);

    image_handler(current_layer);

    if (layer_change) {
        //Swizzling to pull out all the layer names
        // Change menu_items to an array of pointers (char*)

        // [ROWS][LENGTH] -> 16 layers * 16 chars per name = 256 bytes of stack
        char menu_storage[KEYNAME_MAP_MAX_LAYERS][16];

        // names
        const char *menu_items[KEYNAME_MAP_MAX_LAYERS];

        for(int i = 0; i < KEYNAME_MAP_MAX_LAYERS; i++) {
            //  Write directly into the specific storage slot for this layer
            snprintf(menu_storage[i], 16, "#%d %s", i, keyname_map[i].name);
        
            // Point the menu item to that storage slot
            menu_items[i] = menu_storage[i];
        }
        draw_menu(menu_items, MAX_LAYER, current_layer);
    }
    else {
        char layerName[16];
        snprintf(layerName, 16, "#%d %s", current_layer, keyname_map[current_layer].name);
        draw_layer(current_layer, layerName);
    }
    qp_flush(oled);
}

/**
 * Refreshes the GUI by calling display_task() if the display hasn't been updated in the last 33 milliseconds.
 * This prevents unnecessary refreshes.
 */
void gui_refresh(bool layer_change_toggle) {
    layer_change = layer_change_toggle;

    static uint32_t last_draw = 0;

    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();

        //variable refresh rate, only refresh if something has changed. Cuts down on i2c usage
        if (update_oled) {
            display_task();
            update_oled = false;
        }
    }
}