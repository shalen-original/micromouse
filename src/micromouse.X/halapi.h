#ifndef HALAPI_H
#define	HALAPI_H

/**
 * Initializes the HAL. To be called from main before using
 * any other HAL API.
 */
void initHAL();

/**
 * Returns the distance in millimeters from the left wall or `-1` if
 * if not available (either too close or too far).
 */
float getDistanceLeft_mm();

/**
 * Returns the distance in millimeters from the right wall or `-1` if
 * if not available (either too close or too far).
 */
float getDistanceRight_mm();

/**
 * Returns the distance in millimeters from the fron wall or `-1` if
 * if not available (either too close or too far).
 */
float getDistanceFront_mm();

#endif

