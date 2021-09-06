#pragma once

struct Point {
	float x;
	float y;

	Point operator +(Point other) {
		return Point{ x + other.x, y + other.y };
	}

	Point operator *(float t) {
		return Point{ x + x * t, y + y * t };
	}
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

