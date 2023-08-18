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
    double d;
    double dx;
    double dy;

    img::Color background_color;
    Figures figures;

    explicit World3D(const ini::Configuration &configuration);
    img::EasyImage drawWorld();

    void draw_zbuf_triag(ZBuffer &zBuffer, img::EasyImage& image,
                         const Vector3D &A,
                         const Vector3D &B,
                         const Vector3D &C,
                         const img::Color &color) const;

    img::EasyImage drawZBuffered();

};


#endif //ENGINE_WORLD3D_H
