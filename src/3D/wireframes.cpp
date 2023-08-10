#include "wireframes.h"



Point2D Wireframes::doProjection(const Vector3D &point, const double d) {
    Point2D point2D;

    double tempz = point.z * -1;
    point2D.x = d * point.x / tempz;
    point2D.y = d * point.y / tempz;
    point2D.z = point.z;

    return point2D;
}

Lines2D Wireframes::doProjection(const Figure &figure, double d) {
    Lines2D lines;
    Points2D points;

    // Project Points
    for (auto &point : figure.points)
    {
        points.push_back(doProjection(point, d));
    }

    // Create lines
    for (auto &face : figure.faces)
    {
        Points2D temppoints;
        for (auto index : face.point_indexes){
            temppoints.push_back(Utilities::pointAt(index, points));
        }
        for (int i = 0; i < temppoints.size() ; i++){
            Point2D p1 = Utilities::pointAt(i, temppoints);
            Point2D p2;

            if(i + 1 == temppoints.size()){
                p2 = Utilities::pointAt(0, temppoints);}
            else{
                p2 = Utilities::pointAt(i + 1, temppoints);}

            lines.emplace_back(p1, p2, figure.color);
        }
    }
    return lines;
}



Lines2D Wireframes::createLineDrawing(Vector3D &eye, Figure &figure, double d) {
// Apply transformations
    Transformations::applyTransformations(figure, Transformations::translate(figure.center));
    Transformations::applyTransformations(figure, Transformations::scaleFigure(figure.scale));
    Transformations::applyTransformations(figure, Transformations::rotateX(figure.rotation.x));
    Transformations::applyTransformations(figure, Transformations::rotateY(figure.rotation.y));
    Transformations::applyTransformations(figure, Transformations::rotateZ(figure.rotation.z));

// Eye point transform
    Matrix V = Transformations::eyePointTrans(eye);
    Transformations::applyTransformations(figure, V);

    // Perspective projection
    Lines2D lines = doProjection(figure, d);

    return lines;
}

Lines2D Wireframes::createLineDrawing(Vector3D &eye, Figures &figures, double d) {
    Lines2D lines;

    for (auto &figure : figures) {
        Lines2D new_lines = createLineDrawing(eye, figure, d);
        lines.insert(lines.end(), new_lines.begin(), new_lines.end());
    }

    return lines;
}



