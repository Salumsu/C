#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

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

IndexPath* createIndexPath() {
    IndexPath* indexPath = malloc(sizeof(IndexPath));
    indexPath->steps = 0;
    return indexPath;
}


IndexPath* getPathInfo(int size, int index) {
    IndexPath* indexPath = createIndexPath();
    if (indexPath == NULL) return NULL;
    int fromHeadIndex = prepareIndex(size, index);
    // Index out of bounds
    if (fromHeadIndex < 0) return NULL;
    if (fromHeadIndex > size / 2) {
        indexPath->fromHead = false;
        if (index > 0) {
            indexPath->steps = abs(index - size);
        } else if (index < 0) {
            indexPath->steps = abs(index);
        }
    } else {
        indexPath->fromHead = true;
        indexPath->steps = fromHeadIndex;
    }

    return indexPath;
}