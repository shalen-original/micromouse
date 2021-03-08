#include "utils.h"

float lerp(float t, float min, float max) {
    __conditional_software_breakpoint(t > 0 && t < 1);
    return min + t * (max - min);
}
