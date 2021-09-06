#pragma once
#include "Segment.h"

class HorizontalLine : public Segment {

	private:
		float length;

	public:
		HorizontalLine(Point startingPoint, float length);
		float GetLength() override;
		Point Interpolate(float t) override;
};