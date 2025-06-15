#include <stdio.h>
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

#endif