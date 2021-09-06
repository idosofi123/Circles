#include "Path.h"
#include "HorizontalLine.h"
#include "VerticalLine.h"
#include "Line.h"
#include "QuadBezier.h"
#include "CubicBezier.h"

#include <algorithm>
#include <sstream>

inline Point Path::CutPoint(std::stringstream &path) {
	float a, b;
	path >> a;
	path.ignore();
	path >> b;
	return Point{ a, b };
}

inline float Path::CutLength(std::stringstream &path) {
	float value;
	path >> value;
	return value;
}

Path::Path(std::string path) {

	totalLength = 0;

	std::transform(path.begin(), path.end(), path.begin(), std::toupper);

	std::stringstream pathStream{ path };

	// Handle the 'M' command seperately, to enable uniform handling of the segment-generating commands.
	pathStream.ignore();
	Point startingPoint = CutPoint(pathStream), currentPoint = startingPoint;

	char command;
	std::unique_ptr<Segment> segment;

	while (pathStream >> command) {

		switch (static_cast<SegmentType>(command)) {

			case SegmentType::HorizontalLine:

				segment = std::make_unique<HorizontalLine>(currentPoint, CutLength(pathStream));
				break;

			case SegmentType::VerticalLine:

				segment = std::make_unique<VerticalLine>(currentPoint, CutLength(pathStream));
				break;

			case SegmentType::Line:

				segment = std::make_unique<Line>(currentPoint, CutPoint(pathStream));
				break;

			case SegmentType::QuadBezier:

				segment = std::make_unique<QuadBezier>(currentPoint, CutPoint(pathStream), CutPoint(pathStream));
				break;

			case SegmentType::CubicBezier:

				segment = std::make_unique<CubicBezier>(currentPoint, CutPoint(pathStream), CutPoint(pathStream), CutPoint(pathStream));
				break;

			case SegmentType::ConnectToStart:

				segment = std::make_unique<Line>(currentPoint, startingPoint);
				break;
		}

		currentPoint = segment->Interpolate(1);
		segments[segment->GetLength()] = std::move(segment);
	}
}

Point Path::Interpolate(float t) {

	// Find the segment that holds our requested point.
	std::map<float, std::unique_ptr<Segment>>::iterator relevantSegmnet = segments.lower_bound(t * totalLength);

	// Given the specific segement calculate the relative interpolation rate to it.
	float floorLength = relevantSegmnet == segments.begin() ? 0 : (--relevantSegmnet)->first;
	float relativeT = (totalLength * t - floorLength) / (relevantSegmnet->first - floorLength);

	return relevantSegmnet->second->Interpolate(relativeT);
}
