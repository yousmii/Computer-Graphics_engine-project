#include <cmath>
#include "transformations.h"
#define _USE_MATH_DEFINES

void Transformations::toPolar(const Vector3D &point, double &theta, double &phi, double &r) {
    r       =     sqrt(pow(point.x,2) + pow(point.y,2) + pow(point.z, 2));
    theta   =     atan2(point.y, point.x);
    phi     =     acos(point.z/r);
}

Matrix Transformations::scaleFigure(const double scale) {
    Matrix scalematrix;
    for(int i = 1; i < 4; i++){scalematrix(i, i) = scale;}
    return scalematrix;
}

Matrix Transformations::rotateX(double angle) {
    Matrix rotX;
    double cosa = cos(angle);
    double sina = sin(angle);

    //Build Rotation matrix
    rotX(2,2) = cosa;
    rotX(2,3) = sina;
    rotX(3,2) = sina * -1;
    rotX(3,3) = cosa;

    return rotX;
}

Matrix Transformations::rotateY(double angle) {
    Matrix rotY;
    double cosa = cos(angle);
    double sina = sin(angle);

    //Build rotation matrix
    rotY(1,1) = cosa;
    rotY(1,3) = sina * -1;
    rotY(3,1) = sina;
    rotY(3,3) = cosa;

    return rotY;
}

Matrix Transformations::rotateZ(double angle) {
    Matrix rotZ;

    double cosa = cos(angle);
    double sina = sin(angle);

    //Build Rotation matrix
    rotZ(1,1) = cosa;
    rotZ(1,2) = sina;
    rotZ(2,1) = sina * -1;
    rotZ(2,2) = cosa;

    return rotZ;
}

Matrix Transformations::translate(const Vector3D& vector) {
    Matrix translate;

    translate(4,1) = vector.x;
    translate(4,2) = vector.y;
    translate(4,3) = vector.z;

    return translate;
}

Matrix Transformations::eyePointTrans(const Vector3D &eye) {
    // Variables
    double theta;
    double phi;
    double r;

    // Calculate theta, phi and r
    toPolar(eye, theta, phi, r);

    Vector3D r_point = Vector3D::point (0, 0, -r);

    // Build Transformation matrix
    Matrix V;

    V(1,1) = -1 * sin(theta);
    V(1,2) = -1 * cos(theta) * cos(phi);
    V(1,3) = cos(theta) * sin(phi);

    V(2,1) = cos(theta);
    V(2,2) = -1 * sin(theta) * cos(phi);
    V(2,3) = sin(theta) * sin(phi);

    V(3,2) = sin(phi);
    V(3,3) = cos(phi);

    V(4,3) = -1 * r;

    return V;
}

void Transformations::applyTransformations(Figure &figure, const Matrix &transformation) {
    for (auto &point : figure.points) {
        point *= transformation;
    }
}




