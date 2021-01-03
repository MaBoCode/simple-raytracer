#include "utils.h"

float shuffle(const float a, const float b, const float shuff) {
    return b * shuff + a * (1 - shuff);
}

float min(const float a, const float b) {
    return a < b ? a : b;
}

float max(const float a, const float b) {
    return a > b ? a : b;
}