#ifndef LOGIC_H
#define LOGIC_H

#include "SDL.h"
#include "object2d.h"
#include <list>
#include <string>
#include <memory>


// base class for logic
class Logic {
    public:
        Logic();
        bool keyInUp{false};
        bool keyInDown{false};
        bool keyInRight{false};
        bool keyInLeft{false};
        bool keyInAction1{false}; 

        //TODO: make private
        std::unique_ptr<Object2d> _player1;
        std::list<std::unique_ptr<Object2d>> _bullets;
        std::list<std::unique_ptr<Object2d>> _enemies;

    private:
};

#endif