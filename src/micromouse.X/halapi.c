#include "halapi.h"

#include "errors.h"
#include "utils.h"
#include "dma.h"
#include "adc.h"
#include "pwm.h"
#include "qei.h"
#include "timers.h"
#include "buttons.h"
#include "ioconfig.h"

#include <assert.h>

void initHAL() {
    initIO();
    
    initTimer1(10 /* ms */);
    initTimer2(100 /* ms */);
    
    initButtons();
    
    initDMAChannel4();
    initADC1();
    initPWM1();
    initQEI();
    
    startTimer1();
    startTimer2();
    startADC1();
    
    LED_1 = LED_OFF;
    LED_2 = LED_OFF;
    LED_3 = LED_OFF;
    LED_4 = LED_OFF;
    
    int i;
    for (i = 0; i < 3000; i++); // short dirty delay for changes to take effect
}

typedef struct {
    float voltage_v;
    float distance_mm;
} SensorCurvePoint;

// MUST be sorted by voltage ASCENDING (distance descending)
#define N_POINTS_2TO15 4
SensorCurvePoint conversionCurve_2to15[] = {
    { 0.39, 150 },
    { 0.59, 100 },
    { 1.02, 50 },
    { 2.10, 20 },
};

// MUST be sorted by voltage ASCENDING (distance descending)
#define N_POINTS_4TO30 11
SensorCurvePoint conversionCurve_4to30[] = {
    { 0.45, 300 },
    { 0.55, 250 },
    { 0.65, 200 },
    { 0.75, 180 },
    { 0.80, 160 },
    { 0.95, 140 },
    { 1.05, 120 },
    { 1.25, 100 },
    { 1.55, 80 },
    { 2.00, 60 },
    { 2.75, 40 },
};

float _interpolateCurve(const SensorCurvePoint *curve, int length, float value) {
    float minVoltage = curve[0].voltage_v;
    float maxVoltage = curve[length - 1].voltage_v;
    
    if (value < minVoltage || value > maxVoltage)
        return ERR_WALL_DISTANCE_NO_AVAIL;
              
    int pointIndex, i;
    for (i = 0; i < length - 2; i++) {
        if (curve[i].voltage_v <= value && curve[i + 1].voltage_v > value){
            pointIndex = i;
            break;
        }
    }
    
    SensorCurvePoint a = curve[pointIndex];
    SensorCurvePoint b = curve[pointIndex + 1];
    
    float t = (value - a.voltage_v) / (b.voltage_v - a.voltage_v);
    return lerp(t, a.distance_mm, b.distance_mm);
}

float getDistanceLeft_mm() {
    return _interpolateCurve(
            conversionCurve_2to15, N_POINTS_2TO15, 
            RAW_SENSOR_LEFT
    );
}

float getDistanceRight_mm() {
    return _interpolateCurve(
            conversionCurve_2to15, N_POINTS_2TO15, 
            RAW_SENSOR_RIGHT
    ); 
}

float getDistanceFront_mm() {
    return _interpolateCurve(
            conversionCurve_4to30, N_POINTS_4TO30, 
            RAW_SENSOR_FRONT
    ); 
}

int setMotorLeftForward(float intensity) {
    int ans = setPWM1Pair1DutyCycle(intensity);
    if (ans != ERR_OK) {
        return ERR_CANNOT_SET_MOTOR_SPEED;
    }
    
    disableOverridePWM1H1();
    overridePWM1L1_LOW();
    return ERR_OK;
}

int setMotorLeftBackward(float intensity) {
    int ans = setPWM1Pair1DutyCycle(intensity);
    if (ans != ERR_OK) {
        return ERR_CANNOT_SET_MOTOR_SPEED;
    }
    
    disableOverridePWM1L1();
    overridePWM1H1_LOW();
    return ERR_OK;
}

void motorLeftCoast() {
    overridePWM1H1_LOW();
    overridePWM1L1_LOW();
}

void motorLeftBrake() {
    overridePWM1H1_HIGH();
    overridePWM1L1_HIGH();
}

int setMotorRightForward(float intensity) {
    int ans = setPWM1Pair2DutyCycle(intensity);
    if (ans != ERR_OK) {
        return ERR_CANNOT_SET_MOTOR_SPEED;
    }
    
    disableOverridePWM1H2();
    overridePWM1L2_LOW();
    return ERR_OK;
}

int setMotorRightBackward(float intensity) {
    int ans = setPWM1Pair2DutyCycle(intensity);
    if (ans != ERR_OK) {
        return ERR_CANNOT_SET_MOTOR_SPEED;
    }
    
    disableOverridePWM1L2();
    overridePWM1H2_LOW();
    return ERR_OK;
}

void motorRightCoast() {
    overridePWM1H2_LOW();
    overridePWM1L2_LOW();
}

void motorRightBrake() {
    overridePWM1H2_HIGH();
    overridePWM1L2_HIGH();
}

long getMotorLeftPosition_ticks() {
    return getQEI1Position();
}

long getMotorRightPosition_ticks() {
    return getQEI2Position();
}