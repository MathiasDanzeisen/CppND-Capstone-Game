#include "enemy.h"
#include "config.h"


Enemy::Enemy()  {
    this->_type = objectEnemy;
    _objSizePoints.sizeW = config::ENEMY_GRAPIC_SIZE;
    _objSizePoints.sizeH = config::ENEMY_GRAPIC_SIZE;
}