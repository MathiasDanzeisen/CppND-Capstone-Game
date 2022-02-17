#include "player.h"
#include "config.h"



Player::Player()  {
    this->_type = objectPlayer;
    _objWidPoints = config::PLAYER1_GRAPIC_SIZE;
    _objHeiPoints = config::PLAYER1_GRAPIC_SIZE;
}