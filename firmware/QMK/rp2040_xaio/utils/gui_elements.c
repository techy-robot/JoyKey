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

// --- Layout Structure ---
typedef struct {
    uint8_t matrix_row;
    uint8_t matrix_col;
    int x; // Top-left X
    int y; // Top-left Y
    int w;
    int h;
} screen_key_pos_t;

// --- Layout Definition ---
// Scaled for 128x64: ~22px per 1u. 
// Offsets: X+6 to center on screen.
const screen_key_pos_t PROGMEM SCREEN_LAYOUT[] = {
    
    // Note: W/H are slightly smaller than the grid step (22px) to create a 2px gap.
// {Row, Col, X, Y, W,  H}
    {0, 0,   6,  0, 20, 20}, // Index 0:  Left Trigger (1u)
    {0, 1,  50, 20, 20, 20}, // Index 1:  Key 2        (1u)
    {0, 2,  94,  0, 20, 20}, // Index 2:  Right Trigger(1u)
    {0, 3, 99, 22,  20, 20}, // Index 3:  EncA         (0.5u)
    {1, 0,  28, 20, 20, 20}, // Index 4:  Key 1        (1u)
    {1, 1,  50, 42, 20, 20}, // Index 5:  Key 5        (1u)
    {1, 2,  72, 20, 20, 20}, // Index 6:  Key 3        (1u)
    {1, 3, 99, 42,  20, 20}, // Index 7:  EncB         (0.5u)
    //{2, 0,  11, 38,  20, 20}, // Index 8:  JoystickBtn. Does not exist in case yet
    {2, 1,  28, 42, 20, 20}, // Index 9:  Key 4        (1u)
    {2, 2,  72, 42, 20, 20}, // Index 10: Key 6        (1u)
    //{2, 3,  99, 38,  20, 20}  // Index 11: EncBtn. Held hostage by layer change code, we don't need key press
};

#define SCREEN_LAYOUT_SIZE (sizeof(SCREEN_LAYOUT) / sizeof(screen_key_pos_t))

// --- Helper Functions ---

/** 
 * Helper to calculate text width to center it.
 * Requires a loaded font.
 */

static int get_centered_start(int container_pos, int container_size, int text_size) {
    return container_pos + (container_size - text_size) / 2;
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

/**
 * @brief Fits text into a box by truncating or wrapping.
 * * @param str The string to draw.
 * @param x Top-left X of the box.
 * @param y Top-left Y of the box.
 * @param w Width of the box.
 * @param h Height of the box.
 * @param fg_hsv Hue/Sat/Val for foreground text.
 * @param bg_hsv Hue/Sat/Val for background (antialiasing).
 */
void draw_text_confined(const char* str, int x, int y, int w, int h, 
                        uint8_t h_fg, uint8_t s_fg, uint8_t v_fg,
                        uint8_t h_bg, uint8_t s_bg, uint8_t v_bg) {
    
    if (!gui_font || !str) return;

    // Local buffer to modify string without touching source
    char buffer[16]; 
    strncpy(buffer, str, 15);
    buffer[15] = '\0'; // Ensure null term

    int line_height = gui_font->line_height;
    int padding = 2; // Pixel padding on sides
    int max_w = w - (padding * 2);

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
    int len = strlen(buffer);
    while (len > 0) {
        int text_w = qp_textwidth(gui_font, buffer);
        
        if (text_w <= max_w) {
            // It fits! Draw it centered.
            int text_x = get_centered_start(x, w, text_w);
            int text_y = get_centered_start(y, h, line_height);
            qp_drawtext_recolor(display_device, text_x, text_y, gui_font, buffer, h_fg, s_fg, v_fg, h_bg, s_bg, v_bg);
            return;
        }

        // It doesn't fit. Shorten by 1 char.
        len--;
        buffer[len] = '\0';
    }
}

void draw_key(bool pressed, int x, int y, int w, int h, const char* name, const char* imageName) {
    if (!display_device) return;

    //If pressed move the key down and to the side. Yes, it will join with another key, but its more animated
    if (pressed) {
        x = x + 2;
        y = y + 2;
    }
    // Draw The Box

    // White Outline, Black Interior
    qp_rect(display_device, x, y, x + w, y + h, HSV_WHITE, false);

    //ignoring image display for now.

    // We skip drawing text on small encoder/joystick buttons (w < 10)
    if (name && gui_font && w > 10) { 
        
        // White Text on Black BG
        draw_text_confined(name, x, y, w, h, HSV_WHITE, HSV_BLACK);
    }
}

void draw_layer(int layerIndex, char* layerName) {
    if (!display_device) return;

    // Clear
    qp_clear(display_device);

    // Header
    draw_layer_name(layerName);

    // Iterate Layout
    for (int i = 0; i < SCREEN_LAYOUT_SIZE; i++) {
        screen_key_pos_t item = SCREEN_LAYOUT[i];

        // Get Physical State
        bool is_pressed = matrix_is_on(item.matrix_row, item.matrix_col);
        const char* label = keyname_map_get_key_data(layerIndex, i)->name;

        // Draw using standard X/Y coordinates
        draw_key(is_pressed, item.x, item.y, item.w, item.h, label, NULL);
    }
}

void draw_layer_name(const char* name) {
    if (!display_device || !gui_font) return;

    int text_w = qp_textwidth(gui_font, name);
    // Center strictly based on screen width, 2px padding from top
    int text_x = (QP_WIDTH - text_w) / 2; 
    
    //draw white text
    qp_drawtext_recolor(display_device, text_x, 2, gui_font, name, HSV_WHITE, HSV_BLACK);
}

void draw_menu_item(const char* text, int x, int y, bool highlighted, bool selected) {
    if (!display_device) return;

    int item_height = 12; 
    int item_width = 100; 

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

void draw_menu(const char* items[], int size, int selected) {
    if (!display_device) return;

    // --- Menu Configuration ---
    const int MAX_VISIBLE_ITEMS = 4;
    const int ITEM_HEIGHT = 14;
    const int MENU_START_X = 10;
    const int MENU_START_Y = 10;

    // --- Scrolling Logic ---
    int start_index = 0;
    if (selected >= MAX_VISIBLE_ITEMS) {
        start_index = selected - MAX_VISIBLE_ITEMS + 1;
    }
    // Clamp start index so we don't scroll past the end if list is short
    if (size > MAX_VISIBLE_ITEMS && start_index > size - MAX_VISIBLE_ITEMS) {
        start_index = size - MAX_VISIBLE_ITEMS;
    }

    int end_index = start_index + MAX_VISIBLE_ITEMS;
    if (end_index > size) end_index = size;

    // Clear menu area (optional, depends on update rate)
    // qp_clear(display_device);

    // --- Render Loop ---
    for (int i = start_index; i < end_index; ++i) {
        int display_row = i - start_index;
        int current_y = MENU_START_Y + (display_row * ITEM_HEIGHT);
        
        bool is_highlighted = (i == selected);
        bool is_selected = false; // Can be passed in if tracking "Active" vs "Hovered"

        draw_menu_item(items[i], MENU_START_X, current_y, is_highlighted, is_selected);
    }
}