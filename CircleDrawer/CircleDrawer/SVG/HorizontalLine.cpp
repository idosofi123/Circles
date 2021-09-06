#include "HorizontalLine.h"

HorizontalLine::HorizontalLine(Point startingPoint, float length) : Segment(startingPoint), length(length) { }

float HorizontalLine::GetLength() {
    return this->length;
}

Point HorizontalLine::Interpolate(float completionRate) {
    return Point{ this->startingPoint.x + length * completionRate, this->startingPoint.y };
}
