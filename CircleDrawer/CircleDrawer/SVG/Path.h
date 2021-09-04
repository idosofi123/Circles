#pragma once
#include "Segment.h"
#include <string>
#include <map>

class Path {

	private:
		std::map<float, Segment> segments;

	public:
		Path(std::string path);

};
