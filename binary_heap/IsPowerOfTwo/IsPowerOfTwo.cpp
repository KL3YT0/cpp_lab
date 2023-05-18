#include <math.h>
#include "IsPowerOfTwo.h"

bool isPowerOfTwo(int value) {
    if (value == 0) return true;

    double log2Value = log2(value);

    if (log2Value == int(log2Value)) {
        return true;
    }

    return false;
}