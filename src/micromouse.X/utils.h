// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UTILS_H
#define	UTILS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "direction.h"
#include "position.h"

// This is just a dummy / temporary file

/**
 * Linearly interpolates between `min` and `max`.
 * @param t The parameter of the interpolation
 * @param min Value returned when t == 0
 * @param max Value returned when t == 1
 */
float lerp(float t, float min, float max) {
    __conditional_software_breakpoint(t > 0 && t < 1);
    return min + t * (max - min);
}


#endif	/* UTILS_H */

