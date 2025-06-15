#include "lib.h"

int prepareIndex (int size, int index) {
    if (index < 0) {
        // For negative based indexing
        index = size + index;

        if (index < 0) { 
            // Out of bounds
            DEBUG_PRINT("INVALID INDEX\n");
            return -1;
        }
    }

    if (index > size) { 
        // Out of bounds
        DEBUG_PRINT("INVALID INDEX\n");
        return -1;
    }

    return index;
} 