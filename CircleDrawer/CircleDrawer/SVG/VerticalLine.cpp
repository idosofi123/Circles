#include "VerticalLine.h"

VerticalLine::VerticalLine(Point startingPoint, float length) : Segment(startingPoint), length(length) { }

float VerticalLine::GetLength() {
    return this->length;
}

Point VerticalLine::Interpolate(float completionRate) {
    return Point{ this->startingPoint.x, this->startingPoint.y + length * completionRate };
}
