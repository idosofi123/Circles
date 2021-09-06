#include "Segment.h"

Point Point::operator +(Point other) {
	return Point{ x + other.x, y + other.y };
}

Point Point::operator *(float t) {
	return Point{ x * t, y * t };
}

Segment::Segment(Point startingPoint) : startingPoint(startingPoint) { }
