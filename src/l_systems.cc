#include <fstream>
#include "l_systems.h"
#define _USE_MATH_DEFINES

Lines2D draw2DLSystem(const LParser::LSystem2D &l_system, img::Color color){
    // Initiate lineslist
    Lines2D lineslist;

    // Initiate essential variables
    double current_angle = l_system.get_starting_angle();
    int nr_its_left = l_system.get_nr_iterations();
    std::string str = l_system.get_initiator();
    std::string tempstring;

    Point2D turtlepos;
    Point2D nextpos;

    // Iterate through string
    while(nr_its_left != 0) {
        tempstring = "";
        for(char c : str){
            if(l_system.get_alphabet().find(c) != l_system.get_alphabet().end()){tempstring += l_system.get_replacement(c);}
            else if(c == '(' || c == '+' || c == '-' || c == ')'){tempstring += c;}
            else{std::cerr << "Unsupported character found!" << std::endl; exit(69);}
        }
        str = tempstring;
        nr_its_left --;
    }

    // To save the current angle and position when we encouter brackets
    std::stack<std::pair<double, std::pair<double, double>>> stack;

    // Loop through string and create a line if needed

    for (char c : str) {
        // char is a symbol of the alphabet
        if (l_system.get_alphabet().find(c) != l_system.get_alphabet().end()) {

            // Determine next position
            nextpos.x = turtlepos.x + cos(current_angle * M_PI / 180);
            nextpos.y = turtlepos.y + sin(current_angle * M_PI / 180);

            // Create a line
            if (l_system.draw(c)) {
                if (nextpos.x < turtlepos.x) {
                    Line2D newline(nextpos, turtlepos, color);
                    lineslist.push_back(newline);
                }
                else {
                    Line2D newline(turtlepos, nextpos, color);
                    lineslist.push_back(newline);
                }
            }
            turtlepos = nextpos;
        }
        else if (c == '+') {
            current_angle += l_system.get_angle();
        } else if (c == '-') {
            current_angle -= l_system.get_angle();
        }
        else if(c == '('){
            stack.push({current_angle, {turtlepos.x, turtlepos.y}});
        } else if(c == ')'){
            std::pair<double, std::pair<double, double>> temppair = stack.top();
            current_angle = temppair.first;
            turtlepos.x = temppair.second.first;
            turtlepos.y = temppair.second.second;
            stack.pop();
        }
        else {
            std::cerr << "Unsupported character found!" << std::endl;
            exit(69);
        }
    }
    return lineslist;
}

img::EasyImage generate2DLsystem(std::string filename, const int size, const ini::DoubleTuple& backgroundcolor, ini::DoubleTuple color){
    LParser::LSystem2D l_system;
    img::EasyImage image;

//    filename = "L2D files/" + filename;

    std::ifstream input_stream(filename);

    if(!input_stream.is_open()){
        std::cerr << "File not found!" << std::endl;
        exit(69);
    }

    input_stream >> l_system;
    input_stream.close();

    img::Color linecolor(255 * color[0], 255 * color[1], 255 * color[2]);
    img::Color bgcolor(255 * backgroundcolor[0], 255 * backgroundcolor[1], 255 * backgroundcolor[2]);

    Lines2D lines = draw2DLSystem(l_system, linecolor);

    image = draw2DLines(lines, size, bgcolor);

    return image;
}