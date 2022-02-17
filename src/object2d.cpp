#include "object2d.h"
#include "config.h"
#include "logic.h"
#include <algorithm>
#include <cmath>
#include <iostream>

// constructor
Object2d::Object2d() {}

// destructor
Object2d::~Object2d() {}

// move constructor
Object2d::Object2d(Object2d &&other) {
  this->_posX = other._posX;
  this->_posY = other._posY;
  this->_veloX = other._veloX;
  this->_veloY = other._veloY;
  this->_objWidPoints = other._objWidPoints;
  this->_objHeiPoints = other._objHeiPoints;
  this->_type = other._type;
}

// move assignment
Object2d &Object2d::operator=(Object2d &&other) {
  this->_posX = other._posX;
  this->_posY = other._posY;
  this->_veloX = other._veloX;
  this->_veloY = other._veloY;
  this->_objWidPoints = other._objWidPoints;
  this->_objHeiPoints = other._objHeiPoints;
  this->_type = other._type;

  return *this;
}

void Object2d::init() {}

bool Object2d::checkCollision(IObject2d &otherObj) const {
  // check if x and y axis overlap
  return std::max(this->getPosX(), otherObj.getPosX()) <
             std::min(this->getPosX() + this->getObjWPoints(),
                      otherObj.getPosX() + otherObj.getObjWPoints()) &&
         std::max(this->getPosY(), otherObj.getPosY()) <
             std::min(this->getPosY() + this->getObjHPoints(),
                      otherObj.getPosY() + otherObj.getObjHPoints());
}

bool Object2d::isObjOnScreen(void) const {

  auto xPoints = this->getPosX();
  auto yPoints = this->getPosY();

  return this->isObjOnScreen(xPoints, yPoints);
}

bool Object2d::isObjOnScreen(int xPoints, int yPoints) const {

  return (xPoints >= config::VRES_POINTS_MIN &&
          (xPoints + this->getObjWPoints()) <= config::VRES_POINTS_MAX &&
          yPoints >= config::VRES_POINTS_MIN &&
          (yPoints + this->getObjHPoints()) <= config::VRES_POINTS_MAX);
}