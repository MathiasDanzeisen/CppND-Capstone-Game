#ifndef LOGIC_H
#define LOGIC_H

#include "SDL.h"
#include "object2d.h"
#include <vector>
#include <string>
#include <memory>
#include <vector>


// base class for logic
class Logic {
    public:
        Logic();
        bool keyInUp{false};
        bool keyInDown{false};
        bool keyInRight{false};
        bool keyInLeft{false};
        bool keyInAction1{false}; 

        static constexpr int POINTS_MIN{0};
        static constexpr int POINTS_MAX{2000};  //virtual resolution

        //TODO: make private
        std::unique_ptr<Object2d> _player1;
        std::vector<std::unique_ptr<Object2d>> _bullets;
        std::vector<std::unique_ptr<Object2d>> _enemies;
    private:
};

#endif