// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UTILS_H
#define	UTILS_H

#include <xc.h> // include processor files - each processor file is guarded.  

// This is just a dummy / temporary file
typedef enum // for booleans
{
    FALSE=0,
    TRUE
} BOOL;

typedef struct { // general 2D maze cell position
    int x;
    int y;
} position;

typedef enum // cardinal direction enum (binary, 4 bits required)
{
    NORTH = 0b0001,
    EAST = 0b0010,
    SOUTH = 0b0100,
    WEST = 0b1000
} dir;


#endif	/* UTILS_H_H */

