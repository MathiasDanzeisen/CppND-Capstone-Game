#ifndef LOGIC_H
#define LOGIC_H

#include "SDL.h"
#include "object2d.h"
#include <vector>
#include <string>
#include <memory>

// base class for logic
class Logic {
    public:
        Logic();

        //TODO: make private
        std::unique_ptr<Object2d> _player1;
    private:
};

#endif