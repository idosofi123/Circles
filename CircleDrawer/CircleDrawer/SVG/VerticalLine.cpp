#include "VerticalLine.h"

VerticalLine::VerticalLine(Point startingPoint, float length) : Segment(startingPoint), length(length) { }

float VerticalLine::GetLength() {
    return this->length;
}

Point VerticalLine::Interpolate(float t) {
    return startingPoint + Point{ 0, length } * t;
}
