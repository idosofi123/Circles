#pragma once
#include "Segment.h"
class Bezier : public Segment {

	using Segment::Segment;

	public:
		float GetLength() override;
};

