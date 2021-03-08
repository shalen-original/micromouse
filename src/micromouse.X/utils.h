#ifndef UTILS_H
#define	UTILS_H

#include <xc.h>
#include <assert.h>

#include "direction.h"
#include "position.h"

/**
 * Linearly interpolates between `min` and `max`.
 * @param t The parameter of the interpolation
 * @param min Value returned when t == 0
 * @param max Value returned when t == 1
 */
float lerp(float t, float min, float max);


#endif

