#include "HorizontalLine.h"

HorizontalLine::HorizontalLine(Point startingPoint, float length) : Segment(startingPoint), length(length) { }

float HorizontalLine::GetLength() {
    return this->length;
}

Point HorizontalLine::Interpolate(float t) {
    return startingPoint + Point{ length, 0 } * t;
}
