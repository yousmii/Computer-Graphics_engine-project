#ifndef ENGINE_WIREFRAMES_H
#define ENGINE_WIREFRAMES_H

#include "transformations.h"
#include "../utils/utilities.h"


class Wireframes {

    static Point2D doProjection(const Vector3D &point, double d);
    static Lines2D doProjection(const Figure &figure, double d);

public:
    static Lines2D createLineDrawing(Vector3D& eye, Figure &figure, double d);
    static Lines2D createLineDrawing(Vector3D& eye, Figures &figures, double d);
};


#endif //ENGINE_WIREFRAMES_H
