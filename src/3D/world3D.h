#ifndef ENGINE_WORLD3D_H
#define ENGINE_WORLD3D_H

#include "../utils/utilities.h"
#include "wireframes.h"



class World3D {
public:
    std::string type;
    int zbufType;

    int size;
    int nr_figures; // amount of figures in the world

    Vector3D eye;
    int d;
    img::Color background_color;
    Figures figures;

    explicit World3D(const ini::Configuration &configuration);
    img::EasyImage drawWorld();
};


#endif //ENGINE_WORLD3D_H
