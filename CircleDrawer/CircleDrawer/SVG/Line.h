#pragma once
#include "Segment.h"

class Line : public Segment {

	private:
		Point endingPoint;

	public:
		Line(Point startingPoint, Point endingPoint);
		float GetLength() override;
		Point Interpolate(float t) override;
};

