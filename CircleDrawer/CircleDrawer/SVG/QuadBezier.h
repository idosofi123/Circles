#pragma once
#include "Bezier.h"

class QuadBezier : public Bezier {

	private:
		Point controlPoint;
		Point endingPoint;

	public:
		QuadBezier(Point startingPoint, Point controlPoint, Point endingPoint);
		Point Interpolate(float completionRate) override;
};