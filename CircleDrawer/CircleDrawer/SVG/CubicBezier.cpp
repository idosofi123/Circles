#include "CubicBezier.h"
#include "QuadBezier.h"

CubicBezier::CubicBezier(Point startingPoint, Point controlPoint1, Point controlPoint2, Point endingPoint) : Bezier(startingPoint),
                                                                                                             controlPoint1(controlPoint1),
                                                                                                             controlPoint2(controlPoint2),
                                                                                                             endingPoint(endingPoint) { }

Point CubicBezier::Interpolate(float t) {
    QuadBezier subBezierA{ startingPoint, controlPoint1, controlPoint2 };
    QuadBezier subBezierB{ controlPoint1, controlPoint2, endingPoint };
    return subBezierA.Interpolate(t) * (1 - t) + subBezierA.Interpolate(t) * t;
}
