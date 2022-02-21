#include "logic.h" 

Logic::Logic() : _bullets(),_enemies() {
    _player1 = std::make_unique<Player>();

}