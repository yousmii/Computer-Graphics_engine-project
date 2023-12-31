#ifndef ENGINE_L_SYSTEMS_H
#define ENGINE_L_SYSTEMS_H

#define _USE_MATH_DEFINES
#include "utils/l_parser.h"
#include "2D/points_n_lines.h"
#include "utils/ini_configuration.h"
#include <stack>
#include <cmath>

class LSystem{
    public:
static Lines2D draw2DLSystem(const LParser::LSystem2D &l_system, img::Color color);

static img::EasyImage generate2DLsystem(std::string filename, const int size, const ini::DoubleTuple& backgroundcolor, ini::DoubleTuple color);

};


#endif //ENGINE_L_SYSTEMS_H
