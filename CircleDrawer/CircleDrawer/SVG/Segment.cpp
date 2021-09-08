#include "Segment.h"
#include <cmath>

Point Point::operator +(Point other) {
	return Point{ x + other.x, y + other.y };
}

Point Point::operator -(Point other) {
	return Point{ x - other.x, y - other.y };
}

Point Point::operator *(float t) {
	return Point{ x * t, y * t };
}

Point Point::AddAngle(float angle) {

	float computedAngle{ };
	if (x == 0) {
		computedAngle = (y >= 0) ? PI / 2 : PI * 3 / 2;
	} else {
		computedAngle = atan(y / x);
		if (x < 0) {
			computedAngle += PI;
		}
	}

	float radius = sqrt(pow(x, 2) + pow(y, 2));

	return Point{ radius * cos(computedAngle + angle), radius * sin(computedAngle + angle) };
}

Point &Point::operator+=(Point other) {
	x += other.x;
	y += other.y;
	return *this;
}

Segment::Segment(Point startingPoint) : startingPoint(startingPoint) { }
