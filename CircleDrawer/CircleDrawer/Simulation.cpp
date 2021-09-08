#include "Simulation.h"
#include <cmath>

Simulation::Simulation(int n, std::shared_ptr<Path> path) : n(n), path(path) {
	this->CalculateConstants();
}

Point Simulation::GetVector(float t, int circleIndex) {
	return constants[circleIndex + n].AddAngle(2 * PI * t * circleIndex);
}

void Simulation::CalculateConstants() {

	for (int i = -n; i <= n; i++) {

		Point averagePoint{ 0, 0 }, curr;

		for (float t = 0; t < 1; t += AVG_CALCULATION_DELTA) {
			curr = path->Interpolate(t);
			curr = curr.AddAngle(-i * 2 * PI * t);
			curr = curr * AVG_CALCULATION_DELTA;
			averagePoint += curr;
		}
		 
		constants.push_back(averagePoint);
	}
}
