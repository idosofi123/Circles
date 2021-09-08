#pragma once
#include "Segment.h"
#include <sstream>
#include <map>
#include <memory>

class Path {

	private:
		std::map<float, std::unique_ptr<Segment>> segments;
		float totalLength;
		
		inline static Point CutPoint(std::stringstream &path, const Point &currentPoint, bool isRelative);
		inline static float CutLength(std::stringstream &path);

	public:
		Path(std::string path);
		Point Interpolate(float t);
};
