#pragma once
#include "Segment.h"

class VerticalLine : public Segment {

	private:
		float length;

	public:
		VerticalLine(Point startingPoint, float length);
		float GetLength() override;
		Point Interpolate(float completionRate) override;
};