#include "world3D.h"

World3D::World3D(const ini::Configuration &configuration) {
    type = configuration["General"]["type"].as_string_or_die();
    size = configuration["General"]["size"].as_int_or_default(1000);
    d = configuration["General"]["d"].as_double_or_default(1.0);


    ini::DoubleTuple bgtuple = configuration["General"]["backgroundcolor"].as_double_tuple_or_default({0,0,0});
    background_color = img::Color(bgtuple[0]*255, bgtuple[1]*255, bgtuple[2]*255);

    nr_figures = configuration["General"]["nrFigures"].as_int_or_die();

    eye = Vector3D::point(configuration["General"]["eye"].as_double_tuple_or_die()[0],
                                   configuration["General"]["eye"].as_double_tuple_or_die()[1],
                                   configuration["General"]["eye"].as_double_tuple_or_die()[2]);

    for(int n = 0; n < nr_figures; n++){
        std::string figName = "Figure" + std::to_string(n);

        Figure figure;
        auto config = configuration[figName];

        figure.type = config["type"].as_string_or_die();

        figure.rotation.x = Utilities::to_rad(config["rotateX"].as_double_or_default(0));
        figure.rotation.y = Utilities::to_rad(config["rotateY"].as_double_or_default(0));
        figure.rotation.z = Utilities::to_rad(config["rotateZ"].as_double_or_default(0));

        figure.scale = config["scale"].as_double_or_default(1.0);
        ini::DoubleTuple center = config["center"].as_double_tuple_or_default({0,0,0});
        figure.center = Vector3D::point(center[0], center[1], center[2]);

        ini::DoubleTuple colortuple = configuration[figName]["color"].as_double_tuple_or_default({0.0, 1.0, 0.0});
        figure.color = img::Color(colortuple[0]*255, colortuple[1]*255, colortuple[2]*255);


        // Parse points and faces
        if(figure.type == "LineDrawing") {
            int npoints = config["nrPoints"].as_int_or_die();
            for (int p = 0; p < npoints; p++) {
                std::string pname = "point" + std::to_string(p);
                ini::DoubleTuple pointcoords = config[pname].as_double_tuple_or_die();

                Vector3D point = Vector3D::point(pointcoords[0], pointcoords[1], pointcoords[2]);
                figure.points.push_back(point);
            }
            int nlines = config["nrLines"];
            for(int l = 0 ; l < nlines ; l++){
                std::string lname = "line" + std::to_string(l);

                Face face;
                face.point_indexes = config[lname];
                figure.faces.push_back(face);
            }
        }

        figures.push_back(figure);
    }
}

img::EasyImage World3D::drawWorld() {
    img::EasyImage image;

    if (type == "Wireframe"){
        Lines2D lines = Wireframes::createLineDrawing(eye, figures, d);

        if(!lines.empty()){
            image = draw2DLines(lines, size, background_color);
        }
    }
    else {
        throw std::runtime_error("Unknown type:" + type);
    }


    return image;
}