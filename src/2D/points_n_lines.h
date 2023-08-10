#ifndef ENGINE_POINTS_N_LINES_H
#define ENGINE_POINTS_N_LINES_H

#include "../utils/easy_image.h"

class Point2D{
public:
    Point2D(double x, double y);

    Point2D();

    double x;
    double y;
    double z;
};

class Line2D{
public:
    Line2D(Point2D p1, Point2D p2, img::Color color);

    Line2D();

    Point2D p1;
    Point2D p2;
    img::Color color;
};

using Points2D = std::vector<Point2D>;
using Lines2D = std::vector<Line2D>;

img::EasyImage draw2DLines(Lines2D &lines, int size, img::Color bgcolor, int zbufType);

#endif