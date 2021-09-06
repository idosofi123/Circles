#include "Bezier.h"
#include "Line.h"

float Bezier::GetLength() {
    float result = 0;
    for (float i = 0; i < 1; i += BEZIER_LENGTH_DELTA) {
        result += Line{ this->Interpolate(i), this->Interpolate(i + BEZIER_LENGTH_DELTA) }.GetLength();
    }
    return result;
}
