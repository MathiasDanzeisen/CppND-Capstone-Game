#include "bullet.h"
#include "config.h"


Bullet::Bullet()  {
    this->_type = objectBullet;
    _objSizePoints.sizeW = config::BULLET_GRAPIC_SIZE;
    _objSizePoints.sizeH = config::BULLET_GRAPIC_SIZE;
}