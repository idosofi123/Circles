#include "Path.h"
#include "HorizontalLine.h"
#include "VerticalLine.h"
#include "Line.h"
#include "QuadBezier.h"
#include "CubicBezier.h"

#include <algorithm>
#include <sstream>

inline Point Path::CutPoint(std::stringstream &path, const Point &currentPoint = { 0, 0 }, bool isRelative = false) {

	float a, b;

	if (path.peek() == ',') path.ignore();

	path >> a;
	path.ignore();
	path >> b;

	Point res{ a, b };

	if (isRelative) {
		res += currentPoint;
	}

	return res;
}

inline float Path::CutLength(std::stringstream &path) {
	float value;
	path >> value;
	return value;
}

Path::Path(std::string path) {

	const float LENGTH_LOWER_LIMIT = 0.01f;

	totalLength = 0;

	std::stringstream pathStream{ path };

	// Handle the 'M' command seperately, to enable uniform handling of the segment-generating commands.
	pathStream.ignore();
	Point startingPoint = CutPoint(pathStream), currentPoint = startingPoint, controlPointA, controlPointB, endingPoint;

	char command;
	bool isRelative;
	std::unique_ptr<Segment> segment;

	while (pathStream >> command) {

		isRelative = islower(command);

		switch (static_cast<SegmentType>(toupper(command))) {

			case SegmentType::HorizontalLine:

				segment = std::make_unique<HorizontalLine>(currentPoint, CutLength(pathStream));
				break;

			case SegmentType::VerticalLine:

				segment = std::make_unique<VerticalLine>(currentPoint, CutLength(pathStream));
				break;

			case SegmentType::Line:

				segment = std::make_unique<Line>(currentPoint, CutPoint(pathStream, currentPoint, isRelative));
				break;

			case SegmentType::QuadBezier:

				controlPointA = CutPoint(pathStream, currentPoint, isRelative);
				endingPoint = CutPoint(pathStream, currentPoint, isRelative);
				segment = std::make_unique<QuadBezier>(currentPoint, controlPointA, endingPoint);
				break;

			case SegmentType::CubicBezier:

				controlPointA = CutPoint(pathStream, currentPoint, isRelative);
				controlPointB = CutPoint(pathStream, currentPoint, isRelative);
				endingPoint = CutPoint(pathStream, currentPoint, isRelative);
				segment = std::make_unique<CubicBezier>(currentPoint, controlPointA, controlPointB, endingPoint);
				break;

			case SegmentType::ConnectToStart:

				segment = std::make_unique<Line>(currentPoint, startingPoint);
				break;
		}

		float segmentLength = segment->GetLength();

		if (segmentLength >= LENGTH_LOWER_LIMIT) {

			currentPoint = segment->Interpolate(1);
			totalLength += segmentLength;
			segments[totalLength] = std::move(segment);
		}

	}
}

Point Path::Interpolate(float t) {

	// Find the segment that holds our requested point.
	std::map<float, std::unique_ptr<Segment>>::iterator relevantSegmnet = segments.lower_bound(t * totalLength);

	// Given the specific segement calculate the relative interpolation rate to it.
	float floorLength = relevantSegmnet == segments.begin() ? 0 : std::prev(relevantSegmnet)->first;
	float relativeT = (totalLength * t - floorLength) / (relevantSegmnet->first - floorLength);

	return relevantSegmnet->second->Interpolate(relativeT);
}
