#include "points_n_lines.h"
#define _USE_MATH_DEFINES

Point2D::Point2D(double x, double y) {
    this->x = x;
    this->y = y;
}

Point2D::Point2D() {
    this->x = 0;
    this->y = 0;
}

Line2D::Line2D() {
    this->p1 = Point2D();
    this->p2 = Point2D();
    this->color = img::Color(0,0,0);
}

Line2D::Line2D(Point2D p1, Point2D p2, img::Color color) {
    this->p1 = p1;
    this->p2 = p2;
    this->color = color;
}

img::EasyImage draw2DLines(Lines2D &lines, const int size, img::Color bgcolor){
    // xmax, xmin, ymax en ymin bepalen
    double xMax = lines.begin()->p1.x;
    double xMin = lines.begin()->p1.x;

    double yMax = lines.begin()->p1.y;
    double yMin = lines.begin()->p1.y;

    // Goes over the list of lines to find the smallest and biggest values
    for(const Line2D& line : lines){
        Point2D beginpt = line.p1;
        Point2D endpt = line.p2;

        if(beginpt.x > xMax)        {xMax = beginpt.x;}
        else if(beginpt.x < xMin)   {xMin = beginpt.x;}

        if(endpt.x > xMax)          {xMax = endpt.x;}
        else if(endpt.x < xMin)     {xMin = endpt.x;}

        if(beginpt.y > yMax)        {yMax = beginpt.y;}
        else if(beginpt.y < yMin)   {yMin = beginpt.y;}

        if(endpt.y > yMax)          {yMax = endpt.y;}
        else if(endpt.y < yMin)     {yMin = endpt.y;}
    }

    // Error checks because this happened before
    if(xMin > xMax){
        std::cerr << "For some stupid reason is xMax smaller than xMin.." << std::endl;
        exit(420);
    }
    if(yMin > yMax){
        std::cerr << "For some stupid reason is yMax smaller than yMin.." << std::endl;
        exit(420);
    }

    // ImageX en ImageY bepalen (size of the image)
    double xRange = xMax - xMin;
    double yRange = yMax - yMin;

    double biggestRange;
    if(xRange >= yRange){biggestRange = xRange;}
    else{biggestRange = yRange;}

    double ImageX = xRange / biggestRange;
    ImageX *= size;
    double ImageY = yRange / biggestRange;
    ImageY *= size;

    // Initialize the img file
    img::EasyImage image(ImageX, ImageY);
    image.clear(bgcolor);

    // Scalefactor for the lines
    double d = ImageX / xRange;
    d *= 0.95;

    // Apply the scalefactor
    for(auto& line : lines){
        line.p1.x *= d;
        line.p1.y *= d;

        line.p2.x *= d;
        line.p2.y *= d;
    }

    // Put the drawing on the correct position
    double DCx = xMin + xMax;
    DCx /= 2;
    DCx *= d;

    double DCy = yMin + yMax;
    DCy /= 2;
    DCy *= d;

    double dx = ImageX / 2;
    dx -= DCx;
    double dy = ImageY / 2;
    dy -= DCy;

    // dx en dy optellen bij elk punt
    for(auto& line : lines){
        line.p1.x += dx;
        line.p1.y += dy;
        line.p2.x += dx;
        line.p2.y += dy;
    }

    for (const Line2D& line : lines) {
        image.draw_line(line.p1.x, line.p1.y, line.p2.x, line.p2.y, line.color);
    }

    return image;
}
