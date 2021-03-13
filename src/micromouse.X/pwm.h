#ifndef PWM_H
#define PWM_H

// PWM1 Pair 1 -> Left Motor (M1) (only if hardware fix)
// PWM1H1 -> M1_IN1/RB14
// PWM1L1 -> M1_IN2/RB15

// PWM1 Pair 3 -> Right Motor (M2)
// PWM1H3 -> M2_IN1
// PWM1L3 -> M2_IN2

void initPWM1();

int setPWM1Pair1DutyCycle(float dc);
int setPWM1Pair3DutyCycle(float dc);

void overridePWM1H1_HIGH();
void overridePWM1H1_LOW();
void disableOverridePWM1H1();
void overridePWM1L1_HIGH();
void overridePWM1L1_LOW();
void disableOverridePWM1L1();

void overridePWM1H3_HIGH();
void overridePWM1H3_LOW();
void disableOverridePWM1H3();
void overridePWM1L3_HIGH();
void overridePWM1L3_LOW();
void disableOverridePWM1L3();

#endif