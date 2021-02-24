#ifndef HALAPI_H
#define	HALAPI_H

/**
 * Initializes the HAL. To be called from main before using
 * any other HAL API.
 */
void initHAL();

/**
 * Returns the distance in millimeters from the left wall or 
 * ERR_WALL_DISTANCE_NO_AVAIL if if not available (either too close or too far).
 */
float getDistanceLeft_mm();

/**
 * Returns the distance in millimeters from the right wall or 
 * ERR_WALL_DISTANCE_NO_AVAIL if if not available (either too close or too far).
 */
float getDistanceRight_mm();

/**
 * Returns the distance in millimeters from the front wall or 
 * ERR_WALL_DISTANCE_NO_AVAIL if if not available (either too close or too far).
 */
float getDistanceFront_mm();

/**
 * The left motor moves forward modulated by `intensity`.
 * @param intensity Between 0 (motor does not drive) and 1 (motor drives at full speed)
 * @return ERR_OK if the operation was successful, an error code otherwise
 */
int setMotorLeftForward(float intensity);

/**
 * The left motor moves backward modulated by `intensity`.
 * @param intensity Between 0 (motor does not drive) and 1 (motor drives at full speed)
 * @return ERR_OK if the operation was successful, an error code otherwise
 */
int setMotorLeftBackward(float intensity);

/**
 * Makes the left motor coast (left free to spin). Overrides any other previous
 * motor setting.
 */
void motorLeftCoast();

/**
 * Makes the left motor brake (activeley braking). Overrides any other previous
 * motor setting.
 */
void motorLeftBrake();

#endif

