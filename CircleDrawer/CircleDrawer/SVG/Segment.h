#pragma once
#include <cmath>

const float PI = atan(1) * 4;

struct Point {

	float x{ 0 };
	float y{ 0 };

	Point operator +(Point other);
	Point operator -(Point other);
	Point& operator +=(Point other);
	Point operator *(float t);
	Point AddAngle(float angle);
};

enum class SegmentType : char {

	HorizontalLine = 'H',
	VerticalLine   = 'V',
	Line		   = 'L',
	QuadBezier	   = 'Q',
	CubicBezier    = 'C',
	ConnectToStart = 'Z'

};

const float BEZIER_LENGTH_DELTA = 0.01f;

class Segment {

	protected:
		Point startingPoint;

	public:
		Segment(Point startingPoint);
		virtual float GetLength() = 0;
		virtual Point Interpolate(float t) = 0;
};

