#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include <limits>
#include <vector>


class ZBuffer : public std::vector<std::vector<double>>{
public:
    ZBuffer(const int width, const int height)
    {
        for (int i = 0; i < width; i++){
            std::vector<double> temp_vector;
            for (int j = 0; j < height; j++){ temp_vector.push_back(std::numeric_limits<double>::infinity());}
            this->push_back(temp_vector);
        }
    }
};


#endif //ENGINE_ZBUFFER_H
