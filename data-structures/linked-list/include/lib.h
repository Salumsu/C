#include <stdio.h>
#include <stdbool.h>

#ifndef LIB_H
#define LIB_H

#ifdef DEBUG
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...) ((void)0)
#endif

/*
 * Converts a possibly negative index into a valid positive index, if within bounds.
 *
 * - If the index is negative, it is treated as an offset from the end (like Python).
 * - If the resulting index is still out of bounds (negative or greater than size), returns -1.
 * - Otherwise, returns the adjusted index.
 */
int prepareIndex (int size, int index);

typedef struct IndexPath {
    bool fromHead;
    int steps;
} IndexPath;

/**
 * @brief Computes the shortest path to reach a given index in a linear structure.
 *
 * This function determines whether it's more efficient to traverse from the head
 * or the tail of a data structure (like a linked list) to reach the specified `index`.
 * It calculates the direction and the number of steps required to get there.
 *
 * Negative indices are supported and interpreted as offsets from the tail 
 * (e.g., -1 means the last element).
 *
 * @param size  The total number of elements in the structure.
 * @param index The target index to access. Can be negative.
 *
 * @return A pointer to an IndexPath struct containing:
 *         - `fromHead`: true if traversal should start from the head,
 *                        false if from the tail.
 *         - `steps`: the number of steps from the chosen end to reach the index.
 * 
 * @note Caller is responsible for freeing the returned IndexPath pointer.
 */
IndexPath* getPathInfo(int size, int index);

#endif