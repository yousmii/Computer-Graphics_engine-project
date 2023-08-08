#ifndef ENGINE_WIREFRAMES_H
#define ENGINE_WIREFRAMES_H

#include "transformations.h"
#include "../2D/points_n_lines.h"


class Wireframes {
    static Point2D pointAt(int index, Points2D points2D);
    static Vector3D pointAt(int index, Points points3D);

    static Point2D doProjection(const Vector3D &point, double d);
    static Lines2D doProjection(const Figure &figure, double d);

public:
    static Lines2D createLineDrawing(Vector3D& eye, Figure &figure, double d);
    static Lines2D createLineDrawing(Vector3D& eye, Figures &figures, double d);
};


#endif //ENGINE_WIREFRAMES_H
