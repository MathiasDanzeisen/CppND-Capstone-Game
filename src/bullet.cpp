#include "bullet.h"
#include "config.h"


Bullet::Bullet()  {
    this->_type = objectBullet;
    _objWidPoints = config::BULLET_GRAPIC_SIZE;
    _objHeiPoints = config::BULLET_GRAPIC_SIZE;
}