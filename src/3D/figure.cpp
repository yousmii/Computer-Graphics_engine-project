#include <valarray>
#include <fstream>
#include <stack>
#include "figure.h"
#include "../utils/l_parser.h"

void Figure::createCube() {
    // clear points and faces
    points.clear();
    faces.clear();

    //Create points
    points.push_back(Vector3D::point(1, -1, -1));
    points.push_back(Vector3D::point(-1, 1, -1));
    points.push_back(Vector3D::point(1, 1, 1));
    points.push_back(Vector3D::point(-1, -1, 1));
    points.push_back(Vector3D::point(1, 1, -1));
    points.push_back(Vector3D::point(-1, -1, -1));
    points.push_back(Vector3D::point(1, -1, 1));
    points.push_back(Vector3D::point(-1, 1, 1));

    //Create faces
    Face face;

    face.point_indexes = {0, 4, 2, 6};  faces.push_back(face);
    face.point_indexes = {4, 1, 7, 2};  faces.push_back(face);
    face.point_indexes = {1, 5, 3, 7};  faces.push_back(face);
    face.point_indexes = {5, 0, 6, 3};  faces.push_back(face);
    face.point_indexes = {6, 2, 7, 3};  faces.push_back(face);
    face.point_indexes = {0, 5, 1, 4};  faces.push_back(face);
}

void Figure::createTetrahedron() {
    // clear points and faces
    points.clear();
    faces.clear();

    // Setting up the points
    points.push_back(Vector3D::point(1, -1, -1)); // 0
    points.push_back(Vector3D::point(-1, 1, -1)); // 1
    points.push_back(Vector3D::point(1, 1, 1));   // 2
    points.push_back(Vector3D::point(-1, -1, 1)); // 3


    //Create faces
    Face face;
    faces.clear();

    face.point_indexes = {0, 1, 2};                     faces.push_back(face);
    face.point_indexes = {1, 3, 2};                     faces.push_back(face);
    face.point_indexes = {0, 3, 1};                     faces.push_back(face);
    face.point_indexes = {0, 2, 3};                     faces.push_back(face);
}

void Figure::createOctahedron() {
    // clear points and faces
    points.clear();

    points.push_back(Vector3D::point(1, 0, 0));   // 0
    points.push_back(Vector3D::point(0, 1, 0));   // 1
    points.push_back(Vector3D::point(-1, 0, 0));  // 2
    points.push_back(Vector3D::point(0, -1, 0));  // 3
    points.push_back(Vector3D::point(0, 0, -1));  // 4
    points.push_back(Vector3D::point(0, 0, 1));   // 5

    //Create faces
    Face face;
    faces.clear();

    face.point_indexes = {0, 1, 5};                     faces.push_back(face);
    face.point_indexes = {1, 2, 5};                     faces.push_back(face);
    face.point_indexes = {2, 3, 5};                     faces.push_back(face);
    face.point_indexes = {3, 0, 5};                     faces.push_back(face);
    face.point_indexes = {1, 0, 4};                     faces.push_back(face);
    face.point_indexes = {2, 1, 4};                     faces.push_back(face);
    face.point_indexes = {3, 2, 4};                     faces.push_back(face);
    face.point_indexes = {0, 3, 4};                     faces.push_back(face);
}

void Figure::createIcosahedron() {
    points.clear();

    for(int i = 1 ; i <= 12 ; i++){
        if(i == 1){
            points.push_back(Vector3D::point(
                    0,
                    0,
                    sqrt(5)/2));}

        else if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6 ){
            double temp = i - 2;
            temp *= 2;
            temp *= M_PI;
            temp /= 5;

            points.push_back(
                    Vector3D::point(
                            cos(temp),
                            sin(temp),
                            0.5)
            );}

        else if(i == 7 || i == 8 || i == 9 || i == 10 || i == 11 ){
            double temp1 = M_PI/5;
            double temp2 = i-7;
            temp2 *= 2;
            temp2 *= M_PI;
            temp2 /= 5;
            double temp = temp1 + temp2;

            points.push_back(
                    Vector3D::point(
                            cos(temp),
                            sin(temp),
                            -1 * 0.5)
            );}

        else if(i == 12){
            double temp = sqrt(5);
            temp *= -1;
            temp /= 2;
            points.push_back(
                    Vector3D::point(
                            0,
                            0,
                            temp)
            );}
    }

    //Create faces
    Face face;
    faces.clear();

    face.point_indexes =    {0,     1,      2};         faces.push_back(face);
    face.point_indexes =    {0,     2,      3};         faces.push_back(face);
    face.point_indexes =    {0,     3,      4};         faces.push_back(face);
    face.point_indexes =    {0,     4,      5};         faces.push_back(face);
    face.point_indexes =    {0,     5,      1};         faces.push_back(face);
    face.point_indexes =    {1,     6,      2};         faces.push_back(face);
    face.point_indexes =    {2,     6,      7};         faces.push_back(face);
    face.point_indexes =    {2,     7,      3};         faces.push_back(face);
    face.point_indexes =    {3,     7,      8};         faces.push_back(face);
    face.point_indexes =    {3,     8,      4};         faces.push_back(face);
    face.point_indexes =    {4,     8,      9};         faces.push_back(face);
    face.point_indexes =    {4,     9,      5};         faces.push_back(face);
    face.point_indexes =    {5,     9,      10};        faces.push_back(face);
    face.point_indexes =    {5,     10,     1};         faces.push_back(face);
    face.point_indexes =    {1,     10,     6};         faces.push_back(face);
    face.point_indexes =    {11,    7,      6};         faces.push_back(face);
    face.point_indexes =    {11,    8,      7};         faces.push_back(face);
    face.point_indexes =    {11,    9,      8};         faces.push_back(face);
    face.point_indexes =    {11,    10,     9};         faces.push_back(face);
    face.point_indexes =    {11,    6,      10};        faces.push_back(face);
}

void Figure::createDodecahedron() {
    // clear points and faces
    points.clear();
    faces.clear();

    // Icosahedron maken
    Figure icosa;
    icosa.createIcosahedron();

    //Points
    for(const auto& icoface : icosa.faces){
        double tempX = 0, tempY = 0, tempZ = 0;
        for(auto index : icoface.point_indexes) {
            Vector3D temppoint = Utilities::pointAt(index, icosa.points);
            tempX += temppoint.x;
            tempY += temppoint.y;
            tempZ += temppoint.z;
        }
        points.push_back(Vector3D::point(tempX / 3.0 , tempY / 3.0, tempZ / 3.0));
    }

    // Faces
    Face face;
    faces.clear();

    face.point_indexes =    {0, 1, 2, 3, 4};       faces.push_back(face);
    face.point_indexes =    {0, 5, 6, 7, 1};       faces.push_back(face);
    face.point_indexes =    {1, 7, 8, 9, 2};       faces.push_back(face);
    face.point_indexes =    {2, 9, 10, 11, 3};     faces.push_back(face);
    face.point_indexes =    {3, 11, 12, 13, 4};    faces.push_back(face);
    face.point_indexes =    {4, 13, 14, 5, 0};     faces.push_back(face);
    face.point_indexes =    {19, 18, 17, 16, 15};  faces.push_back(face);
    face.point_indexes =    {19, 14, 13, 12, 18};  faces.push_back(face);
    face.point_indexes =    {18, 12, 11, 10, 17};  faces.push_back(face);
    face.point_indexes =    {17, 10, 9, 8, 16};    faces.push_back(face);
    face.point_indexes =    {16, 8, 7, 6, 15};     faces.push_back(face);
    face.point_indexes =    {15, 6, 5, 14, 19};    faces.push_back(face);

}

void Figure::createCone() {
    // clear points and faces
    points.clear();
    faces.clear();

    /// Check if variables are okay
    if (n < 2){
        std::cerr << "The variable n for the Cone is not big enough!" << std::endl;
        exit(42);
    }
    if (h == 0){
        std::cerr << "Your cone will be flat :(" << std::endl;
    }

    /// Create the points
    for (int i = 0 ; i < n ; i++){
        double x = cos((2 * i * M_PI)/n);
        double y = sin((2 * i * M_PI)/n);
        points.push_back(Vector3D::point(x, y, 0.0));
    }
    points.push_back(Vector3D::point(0.0, 0.0, h));

    /// Create faces
    Face face;
    for (int i = 0 ; i < n ; i++){
        face.point_indexes = { i, (i+1)%n , n };
        faces.push_back(face);
    }
    /// Polygon on bottom
    for (int i = n-1 ; i >= 0 ; i--){
        face.point_indexes.push_back(i);
    }
    faces.push_back(face);
}

void Figure::createSphere() {
    if(n == 0){
        createIcosahedron();
        return;
    }

    // Icosahedron maken
    Figure icosa;
    icosa.createIcosahedron();
    points = icosa.points;
    faces = icosa.faces;

    /// Divide all triangles n times
    Faces tempfaces;
    for(int i = 1 ; i <= n ; i++){
        for(Face face : faces){
            if (face.point_indexes.size() < 3){
                std::cerr << "Face has less than 3 points!" << std::endl;
                exit(42);
            }
            Vector3D A = points[face.point_indexes[0]];           int indexA = face.point_indexes[0];
            Vector3D B = points[face.point_indexes[1]];           int indexB = face.point_indexes[1];
            Vector3D C = points[face.point_indexes[2]];           int indexC = face.point_indexes[2];

            Vector3D D;  Vector3D E;  Vector3D F;
            Utilities::trianglePoints(A, B, C, D, E, F);

            int indexD = points.size();       points.push_back(D);
            int indexE = points.size();       points.push_back(E);
            int indexF = points.size();       points.push_back(F);

            Face newFace;
            newFace.point_indexes = {indexA, indexD, indexE};               tempfaces.push_back(newFace);
            newFace.point_indexes = {indexB, indexF, indexD};               tempfaces.push_back(newFace);
            newFace.point_indexes = {indexC, indexE, indexF};               tempfaces.push_back(newFace);
            newFace.point_indexes = {indexD, indexF, indexE};               tempfaces.push_back(newFace);
        }
        faces = tempfaces;
        tempfaces.clear();
    }

    /// Normalize all points
    for(auto& point : points){
        point.normalise();
    }
}

void Figure::createCylinder() {
    // clear points and faces
    points.clear();
    faces.clear();

    /// Check if variables are okay
    if (n < 2){
        std::cerr << "The variable n for the cylinder is not big enough!" << std::endl;
        exit(42);
    }
    if (h == 0){
        std::cerr << "Your cylinder will be flat :(" << std::endl;
    }

    // Create points
    //First half of list is bottom, second half is top
    double height = 0.0;

    for(int e = 0 ; e < 2 ; e++){
        for(int i = 0 ; i < n ; i++){
            double x = cos((2 * i * M_PI)/n);
            double y = sin((2 * i * M_PI)/n);
            points.push_back(Vector3D::point(x, y, height));
        }
        height = h;
    }

    //-------------- Create faces
    Face face;
    for (int i = 0 ; i < n ; i++){
        face.point_indexes = { i+n, i, (i+1)%n , (i+1)%n + n };
        faces.push_back(face);
    }

    face.point_indexes.clear();
    // Polygon on bottom
    for (int i = n-1 ; i >= 0 ; i--){
        face.point_indexes.push_back(i);
    }
    faces.push_back(face);

    face.point_indexes.clear();
    // Polygon on top
    for (int i = 2*n-1 ; i >= n ; i--){
        face.point_indexes.push_back(i);
    }
    faces.push_back(face);
}

void Figure::createTorus() {
    // clear points and faces
    points.clear();
    faces.clear();


    /// Create points
    int indexMatrix[n][m]; // houdt de indexen van de punten in de pointsvector bij

    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < m ; j++){
            double u = 2 * i * M_PI/n;
            double v = 2 * j * M_PI/n;

            double x = (R + r * cos(v)) * cos(u);
            double y = (R + r * cos(v)) * sin(u);
            double z = r * sin(v);

            indexMatrix[i][j] = points.size();

            points.push_back(Vector3D::point(x, y, z));
        }
    }

    /// Create Surfaces
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < m ; j++){
            int point1 = indexMatrix[i][j];
            int point2 = indexMatrix[(i+1)%n][j];
            int point3 = indexMatrix[(i+1)%n][(j+1)%m];
            int point4 = indexMatrix[i][(j+1)%m];

            Face face;
            face.point_indexes = { point1, point2, point3, point4 };
            faces.push_back(face);
        }
    }
}

void Figure::create3DLSystem() {
    LParser::LSystem3D l_system;

    std::ifstream input_stream(filename);
    input_stream >> l_system;
    input_stream.close();

    // Clear points and faces in case it is still filled
    this->points.clear();
    this->faces.clear();

    // Initiate essential variables
    double delta = l_system.get_angle() * M_PI / 180;

    int nr_its = l_system.get_nr_iterations();
    std::string str = l_system.get_initiator();
    std::string tempstring;

    Vector3D turtlepos = Vector3D::point(0.0, 0.0, 0.0);
    Vector3D nextpos = Vector3D::point(0.0, 0.0, 0.0);

    int turtleindex = 0;
    points.push_back(turtlepos);

    Vector3D h; h.x = 1.0; h.y = 0.0; h.z = 0.0;
    Vector3D l; l.x = 0.0; l.y = 1.0; l.z = 0.0;
    Vector3D u; u.x = 0.0; u.y = 0.0; u.z = 1.0;

    // Iterate through string and replace
    for(int i = nr_its ; i > 0 ; i-- ) {
        tempstring = "";
        for(char c : str){
            if(l_system.get_alphabet().find(c) != l_system.get_alphabet().end()){
                tempstring += l_system.get_replacement(c);
            }
            else if(c == '(' || c == '+' || c == '-' || c == ')' || c == '^' || c == '&' || c == '\\' || c == '/' || c == '|'){
                tempstring += c;
            }
            else{std::cerr << "Unsupported character found!" << std::endl; exit(69);}
        }
        str = tempstring;
    }

    // For brackets
    std::stack<std::pair < int, std::vector<Vector3D>> > stack;
    //de positie van de turtle en de 3 vectors voor het assenstelsel

    // Loop through string and create a line if needed
    for (char c : str) {
        // char is a symbol of the alphabet
        if (l_system.get_alphabet().find(c) != l_system.get_alphabet().end()) {
            // Determine next position
            int nextposindex    = this->points.size();

            nextpos = turtlepos + h;
            this->points.push_back(nextpos);

            // Create a line
            if (l_system.draw(c)) {
                Face face;
                face.point_indexes = {turtleindex, nextposindex};
                this->faces.push_back(face);
            }
            turtlepos = nextpos;
            turtleindex = nextposindex;
        }

            // Edit the vectors
        else {
            switch (c) {
                case '+': {
                    Vector3D h_new = h * cos(delta) + l * sin(delta);
                    Vector3D l_new = -1 * h * sin(delta) + l * cos(delta);

                    h = h_new;
                    l = l_new;
                    break;
                }
                case '-': {
                    Vector3D h_new = h * cos(-1 * delta) + l * sin(-1 * delta);
                    Vector3D l_new = -1 * h * sin(-1 * delta) + l * cos(-1 * delta);

                    h = h_new;
                    l = l_new;
                    break;
                }

                case '^': {
                    Vector3D h_new = h * cos(delta) + u * sin(delta);
                    Vector3D u_new = -1 * h * sin(delta) + u * cos(delta);

                    h = h_new;
                    u = u_new;
                    break;
                }

                case '&': {
                    Vector3D h_new = h * cos(-1 * delta) + u * sin(-1 * delta);
                    Vector3D u_new = -1 * h * sin(-1 * delta) + u * cos(-1 * delta);

                    h = h_new;
                    u = u_new;
                    break;
                }
                case '\\': {
                    Vector3D l_new = l * cos(delta) - u * sin(delta);
                    Vector3D u_new = l * sin(delta) + u * cos(delta);

                    l = l_new;
                    u = u_new;
                    break;
                }
                case '/': {
                    Vector3D l_new = l * cos(-1 * delta) - u * sin(-1 * delta);
                    Vector3D u_new = l * sin(-1 * delta) + u * cos(-1 * delta);

                    l = l_new;
                    u = u_new;
                    break;
                }
                case '|': {
                    h *= -1;
                    l *= -1;
                    break;
                }
                case '(': {
                    stack.push({turtleindex,{turtlepos, h, l, u}});
                    break;
                }
                case ')': {
                    auto tempvector = stack.top();

                    turtleindex = tempvector.first;
                    turtlepos = tempvector.second[0];
                    h = tempvector.second[1];
                    l = tempvector.second[2];
                    u = tempvector.second[3];

                    stack.pop();
                    break;
                }
                default: {
                    std::cerr << "Unsupported character " << c << " found!" << std::endl;
                    exit(1);
                }
            }
        }
    }
}




