#ifndef ENGINE_UTILITIES_H
#define ENGINE_UTILITIES_H

#include <vector>
#include <cmath>
#include "easy_image.h"
#include "ini_configuration.h"
#include "vector3d.h"
#include "../2D/points_n_lines.h"
#include "../3D/figure.h"

class Utilities {
public:
    static int roundToInt(double d){
        return static_cast<int>(round(d));
    }

    static double to_rad(double angle){
        angle *= M_PI;
        angle /= 180;
        return angle;
    }

    static void trianglePoints(Vector3D A, Vector3D B, Vector3D C, Vector3D &D, Vector3D &E, Vector3D &F){
        D = (A + B)/2;
        E = (A + C)/2;
        F = (B + C)/2;
    }

    static Point2D pointAt(int index, Points2D points2D){
        auto it = points2D.begin();
        for(int i = 0; i < index ; i++){it++;}
        return *it;
    }

    static Vector3D pointAt(int index, std::vector<Vector3D> points3D){
        auto it = points3D.begin();
        for(int i = 0; i < index ; i ++){it++;}
        return *it;
    }
};



#endif //ENGINE_UTILITIES_H
