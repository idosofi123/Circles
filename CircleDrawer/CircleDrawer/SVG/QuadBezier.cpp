#include "QuadBezier.h"
#include "Line.h"

QuadBezier::QuadBezier(Point startingPoint, Point controlPoint, Point endingPoint) : Bezier(startingPoint),
                                                                                     controlPoint(controlPoint),
                                                                                     endingPoint(endingPoint) { }

Point QuadBezier::Interpolate(float t) {
    return Point {
        startingPoint.x + (controlPoint.x - startingPoint.x) * t + (endingPoint.x - controlPoint.x) * t,
        startingPoint.y + (controlPoint.y - startingPoint.y) * t + (endingPoint.y - controlPoint.y) * t
    };
}
