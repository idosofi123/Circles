#include "Simulation.h"
#include <cmath>

Simulation::Simulation(int n, std::shared_ptr<Path> path) : n(n), path(path) {
	this->CalculateConstants();
}

Point Simulation::GetVector(float t, int circleIndex) {
	return constants[circleIndex + n].AddAngle(2 * PI * t * circleIndex);
}

void Simulation::CalculateConstants() {

	for (int i = 0, circleIndex; i < 2 * n + 1; i++) {

		circleIndex = i - n;

		Point averagePoint{0, 0};

		for (float t = AVG_CALCULATION_DELTA; t <= 1; t += AVG_CALCULATION_DELTA) {
			averagePoint += (path->Interpolate(t) * AVG_CALCULATION_DELTA).AddAngle(-circleIndex * 2 * PI * t);
		}

		constants.push_back(averagePoint);
	}
}
