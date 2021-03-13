#include <xc.h>

#include "oc.h"
#include "utils.h"
#include "errors.h"

void initOC() {
    OC1CONbits.OCM = 0b110; // PWM mode without fault
    OC1CONbits.OCTSEL = 0b1; // Clock source is timer 3 
    
    setOC1DutyCycle(0);
    setOC2DutyCycle(0);
}

int _computeOcPwmDutyCycle(float dc) {
    dc = lerp(dc, 0, PWM_MAX_SAFE_DUTY_CYCLE);
    if (dc < 0 || dc > PWM_MAX_SAFE_DUTY_CYCLE) {
        return ERR_DUTY_CYCLE_INVALID;
    }
    
    return (int)(PR3 * dc);
}

int setOC1DutyCycle(float dc) {
    int ans = _computeOcPwmDutyCycle(dc);
    
    if (ans >= 0) {
        OC1R = ans;
        return ERR_OK;
    }
    
    return ans;
}

int setOC2DutyCycle(float dc) {
    int ans = _computeOcPwmDutyCycle(dc);
    
    if (ans >= 0) {
        OC2R = ans;
        return ERR_OK;
    }
    
    return ans;
}
