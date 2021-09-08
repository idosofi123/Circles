#pragma once

#include "SVG/Path.h"
#include <vector>
#include <memory>

const float AVG_CALCULATION_DELTA = 1.0f / 1000.0f;

class Simulation {

	private:
		int n;
		std::shared_ptr<Path> path;
		std::vector<Point> constants;
		void CalculateConstants();

	public:
		Simulation(int n, std::shared_ptr<Path> path);
		Point GetVector(float t, int circleIndex);
};

