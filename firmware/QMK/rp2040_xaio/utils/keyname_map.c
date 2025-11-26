#include "keyname_map.h"
#include <string.h> // For strncpy and memset

LayerData_t keyname_map[KEYNAME_MAP_MAX_LAYERS];

void keyname_map_init(void) {
    // Zero out the entire data structure to ensure all names start as empty strings.
    memset(keyname_map, 0, sizeof(keyname_map));
}

void keyname_map_set_layer_name(int layerIndex, const char* layerName) {
    // Bounds check to prevent memory corruption.
    if (layerIndex < 0 || layerIndex >= KEYNAME_MAP_MAX_LAYERS) {
        return;
    }
    // Safely copy the string, ensuring null termination.
    strncpy(keyname_map[layerIndex].name, layerName, KEYNAME_MAP_NAME_LENGTH - 1);
    keyname_map[layerIndex].name[KEYNAME_MAP_NAME_LENGTH - 1] = '\0';
}

void keyname_map_set_key_data(int layerIndex, int keyIndex, const char* keyName, const char* imageName) {
    // Bounds check for both layer and key indices.
    if (layerIndex < 0 || layerIndex >= KEYNAME_MAP_MAX_LAYERS ||
        keyIndex < 0 || keyIndex >= KEYNAME_MAP_MAX_KEYS_PER_LAYER) {
        return;
    }

    KeyData_t* key = &keyname_map[layerIndex].keys[keyIndex];

    // Safely copy the key name.
    strncpy(key->name, keyName, KEYNAME_MAP_NAME_LENGTH - 1);
    key->name[KEYNAME_MAP_NAME_LENGTH - 1] = '\0';

    // Safely copy the image name.
    strncpy(key->imageName, imageName, KEYNAME_MAP_NAME_LENGTH - 1);
    key->imageName[KEYNAME_MAP_NAME_LENGTH - 1] = '\0';
}

const char* keyname_map_get_layer_name(int layerIndex) {
    if (layerIndex < 0 || layerIndex >= KEYNAME_MAP_MAX_LAYERS) {
        return NULL; // Return NULL for invalid index.
    }
    return keyname_map[layerIndex].name;
}

const KeyData_t* keyname_map_get_key_data(int layerIndex, int keyIndex) {
    if (layerIndex < 0 || layerIndex >= KEYNAME_MAP_MAX_LAYERS ||
        keyIndex < 0 || keyIndex >= KEYNAME_MAP_MAX_KEYS_PER_LAYER) {
        return NULL; // Return NULL for invalid index.
    }
    return &keyname_map[layerIndex].keys[keyIndex];
}

int keyname_map_key_exists(int layerIndex, int keyIndex) {
    const KeyData_t* key = keyname_map_get_key_data(layerIndex, keyIndex);
    // A key "exists" if we can get a valid pointer to it and its name is not empty.
    // The check for the first character being non-null is a fast way to check for an empty string.
    if (key && key->name[0] != '\0') {
        return 1; // true
    }
    return 0; // false
}
