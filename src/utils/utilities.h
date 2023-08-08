#ifndef ENGINE_UTILITIES_H
#define ENGINE_UTILITIES_H

#include <vector>
#include <cmath>
#include "easy_image.h"
#include "ini_configuration.h"
#include "vector3d.h"

class Utilities {
public:
    int round(double d){
        return static_cast<int>(round(d));
    }

    static double to_rad(double angle){
        angle *= M_PI;
        angle /= 180;
        return angle;
    }

    void trianglePoints(Vector3D &A, Vector3D &B, Vector3D &C, Vector3D &D, Vector3D &E, Vector3D &F){
        D = (A + B)/2;
        E = (A + C)/2;
        F = (B + C)/2;
    }
};



#endif //ENGINE_UTILITIES_H
