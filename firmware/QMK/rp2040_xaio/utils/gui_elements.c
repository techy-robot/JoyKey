#include "gui_elements.h"
#include <string.h>
#include <stdio.h>

// --- Configuration ---
// For Monochrome OLED: 0 = Black (Off), 1 = White (On)
#define QP_COLOR_BG  0
#define QP_COLOR_FG  1


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
// Offsets: X+6, Y+2 to center on screen.
const screen_key_pos_t PROGMEM SCREEN_LAYOUT[] = {
    // {X, Y, Width, Height}
    // Note: W/H are slightly smaller than the grid step (22px) to create a 2px gap.
    
    {0, 0,   6,  2, 20, 20}, // Index 0:  Left Trigger (1u)
    {0, 1,  50, 24, 20, 20}, // Index 1:  Key 2        (1u)
    {0, 2,  94,  2, 20, 20}, // Index 2:  Right Trigger(1u)
    {0, 3, 110, 29,  9,  9}, // Index 3:  EncA         (0.5u)
    {1, 0,  28, 24, 20, 20}, // Index 4:  Key 1        (1u)
    {1, 1,  50, 46, 20, 20}, // Index 5:  Key 5        (1u)
    {1, 2,  72, 24, 20, 20}, // Index 6:  Key 3        (1u)
    {1, 3, 110, 51,  9,  9}, // Index 7:  EncB         (0.5u)
    {2, 0,  11, 40,  9,  9}, // Index 8:  JoystickBtn  (0.5u)
    {2, 1,  28, 46, 20, 20}, // Index 9:  Key 4        (1u)
    {2, 2,  72, 46, 20, 20}, // Index 10: Key 6        (1u)
    {2, 3,  99, 40,  9,  9}  // Index 11: EncBtn       (0.5u)
};

#define SCREEN_LAYOUT_SIZE (sizeof(SCREEN_LAYOUT) / sizeof(screen_key_pos_t))

// --- Helper Functions ---

/** 
 * Helper to calculate text width to center it.
 * Requires a loaded font.
 */

static int get_centered_text_pos(int container_pos, int container_size, int text_size) {
    return container_pos + (container_size - text_size) / 2;
}


void gui_elements_init(painter_device_t oled, painter_font_handle_t font) {
    display_device = oled;
    gui_font = font;
    
    // Initialize the screen background
    if (display_device) {

        // Clear screen.
        qp_clear(display_device);
    }
}

void draw_key(bool pressed, int x, int y, int w, int h, const char* name, const char* imageName) {
    if (!display_device) return;

    // Default corner radius
    //int corner_radius = 3;

    // Determine colors based on state
    //int border_color = QP_COLOR_FG;
    //int fill_color   = pressed ? QP_COLOR_FG : QP_COLOR_BG;
    //int text_color   = pressed ? QP_COLOR_BG : QP_COLOR_FG;

    // Draw Key Outline/Body
    // Note: QMK QP coordinates are typically left/top/right/bottom for shapes, not w/h.
    qp_rect(display_device, x, y, x + w, y + h, 255, 255, 255, false);

    // If pressed, fill the rectangle
    if (pressed) {
        qp_rect(display_device, x + 1, y + 1, x + w - 1, y + h - 1, 255, 255, 255, true);
    }

    // We ignore imageName for now, but could use qp_drawimage with a lookup table if needed.
    
    // Draw Text (Only if fits and font exists)
    // We skip drawing text on small encoder/joystick buttons (w < 10)
    if (name && gui_font && w > 10) { 
        int text_w = qp_textwidth(gui_font, name);
        int text_h = gui_font->line_height; // qp_lineheight(gui_font) does not exist
        int text_x = get_centered_text_pos(x, w, text_w);
        int text_y = get_centered_text_pos(y, h, text_h);
        
        qp_drawtext(display_device, text_x, text_y, gui_font, name);
    }
}

void draw_layer(int layerIndex) {
    if (!display_device) return;

    // Clear
    qp_clear(display_device);

    // Header
    char layerName[16];
    snprintf(layerName, sizeof(layerName), "LAYER %d", layerIndex);
    draw_layer_name(layerName);

    // Iterate Layout
    for (int i = 0; i < SCREEN_LAYOUT_SIZE; i++) {
        screen_key_pos_t item = SCREEN_LAYOUT[i];

        // Get Physical State
        bool is_pressed = matrix_is_on(item.matrix_row, item.matrix_col);
        const char* label = "test";

        // Draw using standard X/Y coordinates
        draw_key(is_pressed, item.x, item.y, item.w, item.h, label, NULL);
    }
}

void draw_layer_name(const char* name) {
    if (!display_device || !gui_font) return;

    int text_w = qp_textwidth(gui_font, name);
    // Center strictly based on screen width, 2px padding from top
    int text_x = (QP_WIDTH - text_w) / 2; 
    
    qp_drawtext(display_device, text_x, 2, gui_font, name);
}

void draw_menu_item(const char* text, int x, int y, bool highlighted, bool selected) {
    if (!display_device) return;

    int item_height = 12; // Approx line height
    int item_width = 100; // Fixed width menu or calculate based on screen

    //int bg_color = highlighted ? QP_COLOR_FG : QP_COLOR_BG;
    //int text_color = highlighted ? QP_COLOR_BG : QP_COLOR_FG;

    // Draw background strip for the item
    qp_rect(display_device, x, y, x + item_width, y + item_height, 255, 255, 0, true);//bg color

    // If selected (e.g., confirmed/active option), maybe draw a marker or border
    if (selected) {
        qp_rect(display_device, x, y, x + 2, y + item_height, 255, 255, 255, true); // Side bar marker, color foreground
    }

    if (gui_font) {
        // Padding of 4px on the left
        qp_drawtext(display_device, x + 4, y + 1, gui_font, text);
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