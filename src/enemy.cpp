#include "enemy.h"
#include "config.h"


Enemy::Enemy()  {
    this->_type = objectEnemy;
    _objWidPoints = config::ENEMY_GRAPIC_SIZE;
    _objHeiPoints = config::ENEMY_GRAPIC_SIZE;
}