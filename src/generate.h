#ifndef ENGINE_GENERATE_H
#define ENGINE_GENERATE_H

#include "l_systems.h"
#include "3D/world3D.h"

class Generator{
public:
    static img::EasyImage generate_image(const ini::Configuration &configuration);
};



#endif //ENGINE_GENERATE_H
