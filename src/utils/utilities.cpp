#include "utilities.h"

Faces Utilities::triangulate(Face face) {
    Faces faces;

    for(int i = 1; i < face.point_indexes.size() - 1; i++){
        Face newface;
        newface.point_indexes.push_back(face.point_indexes[0]);
        newface.point_indexes.push_back(face.point_indexes[i]);
        newface.point_indexes.push_back(face.point_indexes[i + 1]);
        faces.push_back(newface);
    }

    return faces;
}
