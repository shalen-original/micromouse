#ifndef UTILS_H
#define	UTILS_H

#include <xc.h>
#include <assert.h>

#include "direction.h"
#include "position.h"

/**
 * The hash values of the UART commands
 * Commands are sent with upper-case letters (and are always equal to the part after CMD_
 */
#define CMD_LED 12452 //"LED" 0b11000 01010 0100
#define CMD_CLRS 111187 //"CLRS"
#define CMD_CLRH 111176 //"CLRH"
#define CMD_GO 239 //"GO"
#define CMD_STOP 643568 //"STOP"
#define CMD_PAUSE 16832101 //"PAUSE"
#define CMD_SPIN 639278 //"SPIN"
#define CMD_MAP 13360 //"MAP"

/**
 * The duration in nanoseconds of one cycle of the microcontroller
 */
#define MC_PERIOD_NS 37.5
#define MC_PERIOD_US (MC_PERIOD_NS / 1000)
#define MC_PERIOD_MS (MC_PERIOD_NS / 1000000)

/**
 * The maximum allowed duty cycle on a PWM pin.
 * This in an implementation detail of the HAL and should
 * not be used outside it. It is here because it is
 * required in multiple files in the HAL.
 */
#define PWM_MAX_SAFE_DUTY_CYCLE 0.66

/**
 * Linearly interpolates between `min` and `max`.
 * @param t The parameter of the interpolation
 * @param min Value returned when t == 0
 * @param max Value returned when t == 1
 */
float lerp(float t, float min, float max);


#endif

