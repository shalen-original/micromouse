#ifndef PWM_H
#define PWM_H

void initPWM1();

int setPWM1Pair1DutyCycle(float dc);
int setPWM1Pair2DutyCycle(float dc);

void overridePWM1H1_HIGH();
void overridePWM1H1_LOW();
void disableOverridePWM1H1();
void overridePWM1L1_HIGH();
void overridePWM1L1_LOW();
void disableOverridePWM1L1();

void overridePWM1H2_HIGH();
void overridePWM1H2_LOW();
void disableOverridePWM1H2();
void overridePWM1L2_HIGH();
void overridePWM1L2_LOW();
void disableOverridePWM1L2();

#endif