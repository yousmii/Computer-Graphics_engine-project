#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <vector>
#include <map>
#include "../utils/utilities.h"


class Face{
public:
    std::vector<int> point_indexes;
};

typedef std::vector<Face> Faces;
typedef std::vector<Vector3D> Points;

static Faces triangulate (Face face){
    Faces faces;

    if (face.point_indexes.size() == 3){
        return {face};
    }

    for(int i = 1; i < face.point_indexes.size() - 1; i++){
        Face newface;

        newface.point_indexes.push_back(face.point_indexes[0]);
        newface.point_indexes.push_back(face.point_indexes[i]);
        newface.point_indexes.push_back(face.point_indexes[i + 1]);

        faces.push_back(newface);
    }

    return faces;
}

class Figure{
public:
    std::string type;

    Vector3D rotation;

    double scale;
    Vector3D center;
    img::Color color;

    Points points;
    Faces faces;

    //For cone, sphere, cylinder
    int n;
    double h;

    //For Torus
    int m;
    double r;
    double R;

    // For 3D lsystem
    std::string filename;

    void createCube();
    void createTetrahedron();
    void createOctahedron();
    void createIcosahedron();
    void createDodecahedron();
    void createCone();
    void createSphere();
    void createCylinder();
    void createTorus();
    void create3DLSystem();
};

typedef std::vector<Figure> Figures;


#endif //ENGINE_FIGURE_H
