#ifndef HALAPI_H
#define	HALAPI_H

#include <xc.h>

#define LED_1 LATBbits.LATB2
#define LED_2 LATBbits.LATB3
#define LED_3 LATCbits.LATC0
#define LED_4 LATCbits.LATC1

#define LED_ON 0
#define LED_OFF 1

#define TIMER1_PERIOD 10 /* ms */
#define TIMER2_PERIOD 100 /* ms */

#define TIMER1_FREQUENCY 1000/TIMER1_PERIOD /* Hz */
#define TIMER2_FREQUENCY 1000/TIMER2_PERIOD /* Hz */

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
 * Makes the left motor brake (actively braking). Overrides any other previous
 * motor setting.
 */
void motorLeftBrake();

/**
 * The right motor moves forward modulated by `intensity`.
 * @param intensity Between 0 (motor does not drive) and 1 (motor drives at full speed)
 * @return ERR_OK if the operation was successful, an error code otherwise
 */
int setMotorRightForward(float intensity);

/**
 * The right motor moves backward modulated by `intensity`.
 * @param intensity Between 0 (motor does not drive) and 1 (motor drives at full speed)
 * @return ERR_OK if the operation was successful, an error code otherwise
 */
int setMotorRightBackward(float intensity);

/**
 * Makes the right motor coast (left free to spin). Overrides any other previous
 * motor setting.
 */
void motorRightCoast();

/**
 * Makes the right motor brake (actively braking). Overrides any other previous
 * motor setting.
 */
void motorRightBrake();

/**
 * Returns the position of the left motor in encoder ticks. A positive value
 * means forward motion, a negative value means backward motion.
 */
long getMotorLeftPosition_ticks();

/**
 * Returns the position of the right motor in encoder ticks. A positive value
 * means forward motion, a negative value means backward motion.
 */
long getMotorRightPosition_ticks();

#endif

