#include "world3D.h"

World3D::World3D(const ini::Configuration &configuration) {
    type = configuration["General"]["type"].as_string_or_die();

    if (type == "Wireframe"){zbufType = 0;}
    else if (type == "ZBufferedWireframe"){zbufType = 1;}
    else if (type == "ZBuffering"){zbufType = 2;}
    else {throw std::runtime_error("Unknown type");}


    size = configuration["General"]["size"].as_int_or_default(1000);
    d = 1.0;


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

        else if(figure.type == "Cube"){
            figure.createCube();
        }
        else if(figure.type == "Tetrahedron"){
            figure.createTetrahedron();
        }
        else if(figure.type == "Octahedron"){
            figure.createOctahedron();
        }
        else if(figure.type == "Icosahedron"){
            figure.createIcosahedron();
        }
        else if(figure.type == "Dodecahedron"){
            figure.createDodecahedron();
        }
        else if(figure.type == "Cone"){
            figure.n = config["n"].as_int_or_die();
            figure.h = config["height"].as_double_or_die();

            figure.createCone();
        }
        else if(figure.type == "Sphere"){
            figure.n = config["n"].as_int_or_die();

            figure.createSphere();
        }
        else if(figure.type == "Cylinder"){
            figure.n = config["n"].as_int_or_die();
            figure.h = config["height"].as_double_or_die();

            figure.createCylinder();
        }
        else if(figure.type == "Torus"){
            figure.m = config["m"].as_int_or_default(10);
            figure.n = config["n"].as_int_or_default(10);
            figure.r = config["r"].as_double_or_default(1);
            figure.R = config["R"].as_double_or_default(2);

            figure.createTorus();
        }
        else if(figure.type == "3DLSystem"){
            figure.filename = config["inputfile"].as_string_or_die();

            figure.create3DLSystem();
        }
        else {
            throw std::runtime_error("Unknown figure type:" + figure.type);
        }

        figures.push_back(figure);
    }
}

img::EasyImage World3D::drawWorld() {
    img::EasyImage image;

    if (type == "Wireframe" || type == "ZBufferedWireframe"){
        Lines2D lines = Wireframes::createLineDrawing(eye, figures, d);

        if(!lines.empty()){
            image = draw2DLines(lines, size, background_color, zbufType);
        }
    }

    else if (type == "ZBuffering"){
        image = drawZBuffered();
    }

    else {
        throw std::runtime_error("Unknown type: " + type);
    }

    return image;
}

img::EasyImage World3D::drawZBuffered() {
    // Triangulate all faces
    for (auto &figure: figures){
        Faces newfaces;
        for (const auto& face: figure.faces){
            Faces faces = triangulate(face);
            newfaces.reserve(newfaces.size());
            newfaces.insert(newfaces.end(), faces.begin(), faces.end());
        }

        figure.faces = newfaces;
    }

    for (auto &figure: figures){
        // Apply transformations
        Transformations::applyTransformations(figure, Transformations::scaleFigure(figure.scale));
        Transformations::applyTransformations(figure, Transformations::rotateX(figure.rotation.x));
        Transformations::applyTransformations(figure, Transformations::rotateY(figure.rotation.y));
        Transformations::applyTransformations(figure, Transformations::rotateZ(figure.rotation.z));
        Transformations::applyTransformations(figure, Transformations::translate(figure.center));

    // Eye point transform
        Matrix V = Transformations::eyePointTrans(eye);
        Transformations::applyTransformations(figure, V);
    }


    // Project all points

    Points2D projectedPoints;

    for (auto figure :figures){
        for (auto point : figure.points){
            projectedPoints.push_back(Wireframes::doProjection(point, d));
        }
    }

    // Calculate d
    double xMax = -std::numeric_limits<double>::infinity();
    double yMax = -std::numeric_limits<double>::infinity();

    for (auto point : projectedPoints){
        if (point.x > xMax){
            xMax = point.x;
        }
        if (point.y > yMax){
            yMax = point.y;
        }
    }

    double xMin = std::numeric_limits<double>::infinity();
    double yMin = std::numeric_limits<double>::infinity();

    for (auto point : projectedPoints){
        if (point.x < xMin){
            xMin = point.x;
        }
        if (point.y < yMin){
            yMin = point.y;
        }
    }

    double xRange = xMax - xMin;
    double yRange = yMax - yMin;

    double imageX = size * (xRange/std::max(xRange, yRange));
    double imageY = size * (yRange/std::max(xRange, yRange));

    d = 0.95 * (imageX/xRange);

    double dcX = d * (xMax + xMin)/2;
    double dcY = d * (yMax + yMin)/2;

    dx = (imageX / 2) - dcX;
    dy = (imageY / 2) - dcY;

    // Create image
    img::EasyImage image(imageX, imageY, background_color);

    // Create zBuffer
    ZBuffer zBuffer(imageX, imageY);

    // Draw all faces
    for(auto figure : figures){
        for(auto face : figure.faces){
            if (face.point_indexes.size() != 3){
                throw std::runtime_error("Face is not a triangle");
            }
            Vector3D A = figure.points[face.point_indexes[0]];
            Vector3D B = figure.points[face.point_indexes[1]];
            Vector3D C = figure.points[face.point_indexes[2]];

            img::Color color = figure.color;

            draw_zbuf_triag(zBuffer, image, A, B, C, color);
        }
    }

    return image;
}



void World3D::draw_zbuf_triag(ZBuffer &zBuffer,
                              img::EasyImage& image,
                              const Vector3D &A,
                              const Vector3D &B,
                              const Vector3D &C,
                              const img::Color &color) const {
    // Project points
    Point2D a, b, c;

    a.x = (d*A.x)/-A.z + dx;
    a.y = (d*A.y)/-A.z + dy;
    a.z = A.z;

    b.x = (d*B.x)/-B.z + dx;
    b.y = (d*B.y)/-B.z + dy;
    b.z = B.z;

    c.x = (d*C.x)/-C.z + dx;
    c.y = (d*C.y)/-C.z + dy;
    c.z = C.z;

    int yMin = std::min(a.y, std::min(b.y, c.y));
    int yMax = std::max(a.y, std::max(b.y, c.y));

    // G bepalen
    Vector3D G;
    G.x = (a.x + b.x + c.x) / 3.0;
    G.y = (a.y + b.y + c.y) / 3.0;
    G.z = (a.z + b.z + c.z) / 3.0;

    // inv_zG bepalen
    double inv_zG = 1.0 / G.z;

    // u en v bepalen
    Vector3D u, v;

    u = B - A;
    v = C - A;

    // w bepalen
    Vector3D w;

    w.x = u.y * v.z - u.z * v.y;
    w.y = u.z * v.x - u.x * v.z;
    w.z = u.x * v.y - u.y * v.x;

    // k berekenen
    double k;
    k = w.x * A.x + w.y * A.y + w.z * A.z;

    // dzdx en dzdy bepalen
    double dzdx, dzdy;
    dzdx = w.x / (-d * k);
    dzdy = w.y / (-d * k);

    for (int y = Utilities::roundToInt(yMin); y <= Utilities::roundToInt(yMax) ; y++){
        double xL_AB= std::numeric_limits<double>::infinity(), xL_AC= std::numeric_limits<double>::infinity(), xL_BC = std::numeric_limits<double>::infinity();
        double xR_AB= -std::numeric_limits<double>::infinity(), xR_AC= -std::numeric_limits<double>::infinity(), xR_BC = -std::numeric_limits<double>::infinity();
        double xi;

        // Line AB
        if ((y - a.y)*(y - b.y) <= 0 && a.y != b.y){
            xi = a.x + (b.x - a.x) * ((double)y - a.y) / (b.y - a.y);
            xL_AB = xi;
            xR_AB = xi;
        }

        // Line BC
        if ((y - b.y)*(y - c.y) <= 0 && b.y != c.y){
            xi = b.x + (c.x - b.x) * ((double)y - b.y) / (c.y - b.y);
            xL_BC = xi;
            xR_BC = xi;
        }

        // Line AC
        if ((y - a.y)*(y - c.y) <= 0 && a.y != c.y){
            xi = a.x + (c.x - a.x) * ((double)y - a.y) / (c.y - a.y);
            xL_AC = xi;
            xR_AC = xi;
        }

        // Set xL and xR
        int xL = Utilities::roundToInt(std::min(xL_AB, std::min(xL_AC, xL_BC)));
        int xR = Utilities::roundToInt(std::max(xR_AB, std::max(xR_AC, xR_BC)));

        for (int x = xL; x < xR; x++){
            double inv_z = 1.0001 * inv_zG + (x - G.x) * dzdx + (y - G.y) * dzdy;

            if (zBuffer[x][y] > inv_z) {
                zBuffer[x][y] = inv_z;
                image(x, y) = color;
            }
        }
    }
}
