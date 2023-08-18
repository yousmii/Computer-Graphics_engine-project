#ifndef ENGINE_TRANSFORMATIONS_H
#define ENGINE_TRANSFORMATIONS_H

#include <vector>
#include "figure.h"

class Transformations{
    static void toPolar(const Vector3D &point, double &theta, double &phi, double &r);

public:
    static Matrix scaleFigure(double scale);

    static Matrix rotateX(double angle);
    static Matrix rotateY(double angle);
    static Matrix rotateZ(double angle);

    static Matrix translate(const Vector3D& vector);

    static Matrix eyePointTrans(const Vector3D &eye);

    static void applyTransformations(Figure &figure, const Matrix &transformation);
};


#endif //ENGINE_TRANSFORMATIONS_H
