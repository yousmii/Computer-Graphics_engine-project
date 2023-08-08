#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <vector>
#include <map>
#include "../utils/vector3d.h"
#include "../utils/easy_image.h"


class Face{
public:
    std::vector<int> point_indexes;
};

typedef std::vector<Face> Faces;
typedef std::vector<Vector3D> Points;

class Figure{
public:
    std::string type;

    Vector3D rotation;

    double scale;
    Vector3D center;
    img::Color color;

    Points points;
    Faces faces;
};

typedef std::vector<Figure> Figures;


#endif //ENGINE_FIGURE_H
