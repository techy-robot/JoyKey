#ifndef KEYNAME_MAP_H
#define KEYNAME_MAP_H

#include "color.h"

// --- Configuration Macros ---
// Adjust these values based on your firmware's needs.
#define KEYNAME_MAP_MAX_LAYERS 4
#define KEYNAME_MAP_MAX_KEYS_PER_LAYER 16
#define KEYNAME_MAP_NAME_LENGTH 16 // Max length for names (including null terminator)

// --- Data Structures ---

/**
 * @brief Holds the data for a single key.
 * Names are fixed-size char arrays to avoid dynamic allocation.
 */
typedef struct {
    char name[KEYNAME_MAP_NAME_LENGTH];
    char imageName[KEYNAME_MAP_NAME_LENGTH];
    hsv_t color;
} KeyData_t;

/**
 * @brief Holds the data for a single layer.
 * Contains the layer's name and a fixed-size array of its keys.
 */
typedef struct {
    char name[KEYNAME_MAP_NAME_LENGTH];
    KeyData_t keys[KEYNAME_MAP_MAX_KEYS_PER_LAYER];
} LayerData_t;


// --- Public API Functions ---

/**
 * @brief Initializes the entire keyname map, clearing all data to zero.
 * This should be called once at startup.
 */
void keyname_map_init(void);

/**
 * @brief Sets the name for a given layer.
 * Truncates the name if it's too long.
 * @param layerIndex The index of the layer.
 * @param layerName The name to assign.
 */
void keyname_map_set_layer_name(int layerIndex, const char* layerName);

/**
 * @brief Sets the data for a specific key on a layer.
 * Truncates names if they are too long.
 * @param layerIndex The index of the layer.
 * @param keyIndex The index of the key.
 * @param keyName The name of the key (e.g., "Enter").
 * @param imageName The name of the key's image asset.
 */
void keyname_map_set_key_data(int layerIndex, int keyIndex, const char* keyName, const char* imageName);

/**
 * @brief Gets the name of a specific layer.
 * @param layerIndex The index of the layer.
 * @return A constant pointer to the layer's name, or NULL if the index is invalid.
 */
const char* keyname_map_get_layer_name(int layerIndex);

/**
 * @brief Gets a pointer to the data for a specific key.
 * @param layerIndex The index of the layer.
 * @param keyIndex The index of the key.
 * @return A constant pointer to the KeyData_t struct, or NULL if indices are invalid.
 */
const KeyData_t* keyname_map_get_key_data(int layerIndex, int keyIndex);

/**
 * @brief Checks if a key has been defined.
 * A key is considered to exist if its name is not empty.
 * @param layerIndex The index of the layer.
 * @param keyIndex The index of the key.
 * @return 1 (true) if the key exists, 0 (false) otherwise.
 */
int keyname_map_key_exists(int layerIndex, int keyIndex);

#endif // KEYNAME_MAP_H
