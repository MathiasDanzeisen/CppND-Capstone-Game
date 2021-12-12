#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <vector>
#include <string>
#include "SDL.h"

// base class for 2d objects
class Object2d {
    public:
        Object2d(const std::string image_path);

    private:
        const std::string _image_path;
};

#endif