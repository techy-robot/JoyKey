#include QMK_KEYBOARD_H

#include "gui_elements.h"

// --- Configuration ---

// HSV Values
#define HSV_WHITE 0, 0, 255
#define HSV_BLACK 0, 0, 0

// Global reference to the loaded font
static painter_font_handle_t gui_font = NULL;

// Global reference to the display device
static painter_device_t display_device = NULL;

//Stores pointers for all currently loaded images
painter_image_handle_t image_cache[KEYNAME_MAP_MAX_KEYS_PER_LAYER];

//This is for software control with textbox through the web panel
char* all_image_names[ALL_IMAGES] = {
    "github",
    "ignore",
    "up",
    "down",
    "left",
    "right",
    "u_point",
    "d_point",
    "l_point",
    "r_point",
    "left_trig",
    "right_trig",
    "keyboard",
    "image"
};

// Stores image IDs for all currently loaded images
// This basically says "Oh, what names are currently loaded right now?"
// The index is the same as the image_cache index, so you can find the image_cache index by looking at the image_id_to_cache_id
static uint8_t image_id_to_cache_id[KEYNAME_MAP_MAX_KEYS_PER_LAYER];
static uint8_t current_cache_id = 0;// current incrementing cache id, increased by image, loading reset when dumped

// --- Layout Structure ---
typedef struct {
    uint8_t matrix_row;
    uint8_t matrix_col;
    uint8_t x; // Top-left X
    uint8_t y; // Top-left Y
    uint8_t w;
    uint8_t h;
    bool show;
} screen_key_pos_t;

// --- Layout Definition ---
// Scaled for 128x64: ~22px per 1u. 
// Offsets: X+6 to center on screen.
const screen_key_pos_t PROGMEM SCREEN_LAYOUT[] = {

    // The do not show elements are simply to map display keys to the matrix properly
    
    // Note: W/H are slightly smaller than the grid step (22px) to create a 2px gap.
// {Row, Col, X, Y, W,  H}
    {0, 0,   6,  0, 20, 20, true}, // Index 0:  Left Trigger (1u)
    {0, 1,  50, 20, 20, 20, true}, // Index 1:  Key 2        (1u)
    {0, 2,  94,  0, 20, 20, true}, // Index 2:  Right Trigger(1u)
    {0, 3, 99, 22,  20, 20, true}, // Index 3:  EncA         (0.5u)
    {1, 0,  28, 20, 20, 20, true}, // Index 4:  Key 1        (1u)
    {1, 1,  50, 42, 20, 20, true}, // Index 5:  Key 5        (1u)
    {1, 2,  72, 20, 20, 20, true}, // Index 6:  Key 3        (1u)
    {1, 3, 99, 42,  20, 20, true}, // Index 7:  EncB         (0.5u)
    {2, 0,  11, 38,  20, 20, false}, // Index 8:  JoystickBtn. Does not exist in case yet, placeholder.
    {2, 1,  28, 42, 20, 20, true}, // Index 9:  Key 4        (1u)
    {2, 2,  72, 42, 20, 20, true}, // Index 10: Key 6        (1u)
    {2, 3,  99, 38,  20, 20, false}  // Index 11: EncBtn. Held hostage by layer change code, we don't need key press
};

#define SCREEN_LAYOUT_SIZE (sizeof(SCREEN_LAYOUT) / sizeof(screen_key_pos_t))

// --- Helper Functions ---

/** 
 * Helper to calculate location of an item to center it, with coordinates at upper left corner.
 */
static uint8_t get_centered_start(uint8_t container_pos, uint8_t container_size, uint8_t item_size) {
    return container_pos + (container_size - item_size) / 2;
}


void gui_elements_init() {
    display_device = oled;
    gui_font = default_font;
    
    // Initialize the screen background
    if (display_device) {

        // Clear screen.
        qp_clear(display_device);
    }
}

void bulk_unload() {
    for (uint8_t i = 0; i < 10; i++) {
        qp_close_image(image_cache[i]);
    }
    current_cache_id = 0;
}

uint8_t image_index_from_name(const char image[KEYNAME_MAP_NAME_LENGTH]) {
    if (!image) return 255; // Safety check for null pointer

    for (uint8_t i = 0; i < ALL_IMAGES; i++) {
        // use strncmp to only compare up to the max length of your key names
        // This protects against strings that are missing a null terminator
        if (strncmp(image, all_image_names[i], KEYNAME_MAP_NAME_LENGTH) == 0) {
            return i;
        }
    }
    return 255;
}

painter_image_handle_t load_image(uint8_t image_id) {
    // Map the current cache slot to this image ID
    image_id_to_cache_id[current_cache_id] = image_id;

    painter_image_handle_t handle = NULL;

    switch (image_id) {
        case 0:
            handle = qp_load_image_mem(gfx_github_mark);
            break;
        case 1:
            handle = qp_load_image_mem(gfx_ignore);
            break;
        case 2:
            handle = qp_load_image_mem(gfx_Arrows_Pointer_Up_North);
            break;
        case 3:
            handle = qp_load_image_mem(gfx_Arrows_Pointer_Down_South);
            break;
        case 4:
            handle = qp_load_image_mem(gfx_Arrows_Pointer_Left_West);
            break;
        case 5:
            handle = qp_load_image_mem(gfx_Arrows_Pointer_Right_East);
            break;
        case 6:
            handle = qp_load_image_mem(gfx_Arrows_Up_North);
            break;
        case 7:
            handle = qp_load_image_mem(gfx_Arrows_Down_South);
            break;
        case 8:
            handle = qp_load_image_mem(gfx_Arrows_Left_West);
            break;
        case 9:
            handle = qp_load_image_mem(gfx_Arrows_Right_East);
            break;
        case 10:
            handle = qp_load_image_mem(gfx_Controller_Buttons_Left_Trigger_LT);
            break;
        case 11:
            handle = qp_load_image_mem(gfx_Controller_Buttons_Right_Trigger_RT);
            break;
        case 12:
            handle = qp_load_image_mem(gfx_Software_Hardware_Keyboard_Keys_Text_Input);
            break;
        case 13:
            handle = qp_load_image_mem(gfx_Software_Image_File_Picture_Framed_Painting_Landscape_Photo_Decoration);
            break;

        default:
            // Fallback: mark this slot as invalid (255)
            image_id_to_cache_id[current_cache_id] = 255;
            handle = qp_load_image_mem(gfx_Software_Image_File_Picture_Framed_Painting_Landscape_Photo_Decoration);
            break;
    }

    current_cache_id++;
    return handle;
}

void bulk_load(char names[10][KEYNAME_MAP_NAME_LENGTH]) {
    for (uint8_t i = 0; i < 10; i++) {
        image_cache[i] = load_image(image_index_from_name(names[i]));
    }
}

uint8_t get_image_cache_id(uint8_t image_id) {
    for (uint8_t i = 0; i < current_cache_id; i++) {
        if (image_id == image_id_to_cache_id[i]) {
            return i;
        }
    }
    return 255;
}

/**
 * @brief Fits text into a box by truncating or wrapping.
 * @param str The string to draw.
 * @param x Top-left X of the box.
 * @param y Top-left Y of the box.
 * @param w Width of the box.
 * @param h Height of the box.
 * @param fg_hsv Hue/Sat/Val for foreground text.
 * @param bg_hsv Hue/Sat/Val for background (antialiasing).
 */
void draw_text_confined(const char* str, uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
                        uint8_t h_fg, uint8_t s_fg, uint8_t v_fg,
                        uint8_t h_bg, uint8_t s_bg, uint8_t v_bg) {
    
    if (!gui_font || !str) return;

    // Local buffer to modify string without touching source
    char buffer[16]; 
    strncpy(buffer, str, 15);
    buffer[15] = '\0'; // Ensure null term

    uint8_t line_height = gui_font->line_height;
    //uint8_t padding = 0; // Pixel padding
    uint8_t max_w = w;

    // --- STRATEGY 1: Check for Line Wrap (Space split) ---
    // Only if the box is tall enough for 2 lines
    char* space_ptr = strchr(buffer, ' ');
    if (space_ptr != NULL && h >= (line_height * 2)) {
        // Split into two strings
        *space_ptr = '\0'; // Terminate first word
        char* second_line = space_ptr + 1;

        // Recursive call for top half
        // We give it the top half of the box
        draw_text_confined(buffer, x, y, w, h/2, h_fg, s_fg, v_fg, h_bg, s_bg, v_bg);
        
        // Recursive call for bottom half
        draw_text_confined(second_line, x, y + (h/2), w, h/2, h_fg, s_fg, v_fg, h_bg, s_bg, v_bg);
        return;
    }

    // --- STRATEGY 2: Single Line Truncation ---
    // If we are here, it's one line (or the split line from above).
    // Loop until it fits the width.
    uint8_t len = strlen(buffer);
    while (len > 0) {
        uint8_t text_w = qp_textwidth(gui_font, buffer);
        
        if (text_w <= max_w) {
            // It fits! Draw it centered.
            uint8_t text_x = get_centered_start(x, w, 16);
            uint8_t text_y = get_centered_start(y, h, 16);
            qp_drawtext_recolor(display_device, text_x, text_y, gui_font, buffer, h_fg, s_fg, v_fg, h_bg, s_bg, v_bg);
            return;
        }

        // It doesn't fit. Shorten by 1 char.
        len--;
        buffer[len] = '\0';
    }
}

void draw_key(bool pressed, uint8_t x, uint8_t y, uint8_t w, uint8_t h, const char* name, uint8_t image_cache_id) {
    if (!display_device) return;

    //If pressed move the key down and to the side. Yes, it will join with another key, but its more animated
    if (pressed) {
        x = x + 2;
        y = y + 2;
    }
    // Draw The Box

    // White Outline, Black Interior
    qp_rect(display_device, x, y, x + w, y + h, HSV_WHITE, false);

    // Draw image if it exists, else draw the name
    if (image_cache_id < 255) {
        //image is gauranteed to be 16x16 pixels, so we can center it
        x = get_centered_start(x, w, 16);
        y = get_centered_start(y, h, 16);
        //recolor image and invert colors so outlines that were black are white and transparency & white in conversions show dark.
        //Most images will look fine with this, as white is used for filling and black is used for outlines
        qp_drawimage_recolor(display_device, x, y, image_cache[image_cache_id], HSV_WHITE, HSV_BLACK);
    }
    else {
        // We skip drawing text on small encoder/joystick buttons (w < 10)
        if (name && gui_font && w > 10) { 
            
            // White Text on Black BG
            draw_text_confined(name, x, y, w, h, HSV_WHITE, HSV_BLACK);
        }
    }
}

void draw_layer(uint8_t layerIndex, char* layerName) {
    if (!display_device) return;

    // Clear
    qp_clear(display_device);

    // Header
    draw_layer_name(layerName);

    // Iterate Layout
    for (uint8_t i = 0; i < SCREEN_LAYOUT_SIZE; i++) {
        screen_key_pos_t item = SCREEN_LAYOUT[i];
        if (item.show == false) continue;

        // Get Physical State
        bool is_pressed = matrix_is_on(item.matrix_row, item.matrix_col);

        // Get pointers to data
        const KeyData_t* keyData = keyname_map_get_key_data(layerIndex, i);
        const char* label = keyData->name;

        // Standardize variable names and remove debugging statements
        uint8_t image_cache_id = 255;
        const char *imageName = keyData->imageName;

        // Validate image name and get image cache ID
        if (imageName && imageName[0]) {
            image_cache_id = get_image_cache_id(image_index_from_name(imageName));
        }

        // Draw using standard X/Y coordinates
        draw_key(is_pressed, item.x, item.y, item.w, item.h, label, image_cache_id);
    }
}

void draw_layer_name(const char* name) {
    if (!display_device || !gui_font) return;

    uint8_t text_w = qp_textwidth(gui_font, name);
    // Center strictly based on screen width, 2px padding from top
    uint8_t text_x = (QP_WIDTH - text_w) / 2; 
    
    //draw white text
    qp_drawtext_recolor(display_device, text_x, 2, gui_font, name, HSV_WHITE, HSV_BLACK);
}

void draw_menu_item(const char* text, uint8_t x, uint8_t y, bool highlighted, bool selected) {
    if (!display_device) return;

    uint8_t item_height = 12; 
    uint8_t item_width = 100; 

    // 1. Draw Background
    if (highlighted) {
        // Highlighted: Filled White Bar
        qp_rect(display_device, x, y, x + item_width, y + item_height, HSV_WHITE, true);
    } else {
        // Normal: Clear/Black Background
        qp_rect(display_device, x, y, x + item_width, y + item_height, HSV_BLACK, true);
    }

    // 2. Draw Selection Marker (if active)
    if (selected) {
        // If highlighted, marker needs to be contrasting (Black), otherwise White
        uint8_t h, s, v;
        if (highlighted) { h=0; s=0; v=0; } // Black
        else             { h=0; s=0; v=255; } // White
        
        qp_rect(display_device, x, y, x + 2, y + item_height, h, s, v, true); 
    }

    // 3. Draw Text
    if (gui_font) {
        if (highlighted) {
            // Highlighted: Black Text on White BG
            qp_drawtext_recolor(display_device, x + 4, y + 1, gui_font, text, HSV_BLACK, HSV_WHITE);
        } else {
            // Normal: White Text on Black BG
            qp_drawtext_recolor(display_device, x + 4, y + 1, gui_font, text, HSV_WHITE, HSV_BLACK);
        }
    }
}

void draw_menu(const char* items[], uint8_t size, uint8_t selected) {
    if (!display_device) return;

    // --- Menu Configuration ---
    const uint8_t MAX_VISIBLE_ITEMS = 4;
    const uint8_t ITEM_HEIGHT = 14;
    const uint8_t MENU_START_X = 10;
    const uint8_t MENU_START_Y = 10;

    // --- Scrolling Logic ---
    uint8_t start_index = 0;
    if (selected >= MAX_VISIBLE_ITEMS) {
        start_index = selected - MAX_VISIBLE_ITEMS + 1;
    }
    // Clamp start index so we don't scroll past the end if list is short
    if (size > MAX_VISIBLE_ITEMS && start_index > size - MAX_VISIBLE_ITEMS) {
        start_index = size - MAX_VISIBLE_ITEMS;
    }

    uint8_t end_index = start_index + MAX_VISIBLE_ITEMS;
    if (end_index > size) end_index = size;

    // Clear menu area (optional, depends on update rate)
    // qp_clear(display_device);

    // --- Render Loop ---
    for (uint8_t i = start_index; i < end_index; ++i) {
        uint8_t display_row = i - start_index;
        uint8_t current_y = MENU_START_Y + (display_row * ITEM_HEIGHT);
        
        bool is_highlighted = (i == selected);
        bool is_selected = false; // Can be passed in if tracking "Active" vs "Hovered"

        draw_menu_item(items[i], MENU_START_X, current_y, is_highlighted, is_selected);
    }
}