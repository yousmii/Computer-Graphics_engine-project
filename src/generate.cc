#include "generate.h"
#include "l_systems.h"

img::EasyImage Generator::generate_image(const ini::Configuration &configuration) {
    std::string type = configuration["General"]["type"];

    if(type == "2DLSystem"){
        return LSystem::generate2DLsystem(
                configuration["2DLSystem"]["inputfile"].as_string_or_die(),
                configuration["General"]["size"].as_int_or_die(),
                configuration["General"]["backgroundcolor"],
                configuration["2DLSystem"]["color"]);
    }
    else if(type == "Wireframe" || type == "ZBufferedWireframe" || type == "ZBuffering"){
        World3D world(configuration);
        return world.drawWorld();
    }
    else{
        throw std::runtime_error("Unsupported type");
    }
}