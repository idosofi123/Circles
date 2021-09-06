#include "Line.h"
#include <cmath>

Line::Line(Point startingPoint, Point endingPoint) : Segment(startingPoint), endingPoint(endingPoint) { }

float Line::GetLength() {
    return sqrt(pow(startingPoint.x - endingPoint.x, 2) + pow(startingPoint.y - endingPoint.y, 2));
}

Point Line::Interpolate(float completionRate) {
    return Point{ startingPoint.x + endingPoint.x * completionRate, startingPoint.y + endingPoint.y * completionRate };
}
