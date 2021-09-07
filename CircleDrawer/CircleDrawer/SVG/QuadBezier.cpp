#include "QuadBezier.h"
#include "Line.h"

QuadBezier::QuadBezier(Point startingPoint, Point controlPoint, Point endingPoint) : Bezier(startingPoint),
                                                                                     controlPoint(controlPoint),
                                                                                     endingPoint(endingPoint) { }

Point QuadBezier::Interpolate(float t) {
    Point a = (startingPoint + (controlPoint - startingPoint) * t) * (1 - t) + (controlPoint + (endingPoint - controlPoint) * t) * t;
    return (startingPoint + (controlPoint - startingPoint) * t) * (1 - t) + (controlPoint + (endingPoint - controlPoint) * t) * t;
}
