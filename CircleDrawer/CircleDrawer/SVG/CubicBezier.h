#pragma once
#include "Bezier.h"

class CubicBezier : public Bezier {

	private:
		Point controlPoint1;
		Point controlPoint2;
		Point endingPoint;

	public:
		CubicBezier(Point startingPoint, Point controlPoint1, Point controlPoint2, Point endingPoint);
		Point Interpolate(float t) override;
};

