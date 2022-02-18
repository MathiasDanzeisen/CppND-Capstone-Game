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
  this->_pos = other._pos;
  this->_veloX = other._veloX;
  this->_veloY = other._veloY;
  this->_objSizePoints = other._objSizePoints;
  this->_type = other._type;
}

// move assignment
Object2d &Object2d::operator=(Object2d &&other) {
  this->_pos = other._pos;
  this->_veloX = other._veloX;
  this->_veloY = other._veloY;
  this->_objSizePoints = other._objSizePoints;
  this->_type = other._type;

  return *this;
}

void Object2d::init() {}

bool Object2d::checkCollision(IObject2d &otherObj) const {
  // check if x and y axis overlap
  return std::max(this->getCurrPosX(), otherObj.getCurrPosX()) <
             std::min(this->getCurrPosX() + this->getObjWPoints(),
                      otherObj.getCurrPosX() + otherObj.getObjWPoints()) &&
         std::max(this->getCurrPosY(), otherObj.getCurrPosY()) <
             std::min(this->getCurrPosY() + this->getObjHPoints(),
                      otherObj.getCurrPosY() + otherObj.getObjHPoints());
}

bool Object2d::isObjOnScreen(void) const {
  return this->isObjOnScreen(this->getCurrPos());
}

bool Object2d::isObjOnScreen(objPosition_t pos) const {

  return (pos.posX >= config::VRES_POINTS_MIN &&
          (pos.posX + this->getObjWPoints()) <= config::VRES_POINTS_MAX &&
          pos.posY >= config::VRES_POINTS_MIN &&
          (pos.posY + this->getObjHPoints()) <= config::VRES_POINTS_MAX);
}

objPosition_t Object2d::getNextPos() const {
  int xPosNew = this->getCurrPosX() + this->getVeloX();
  int yPosNew = this->getCurrPosY() + this->getVeloY();
  return objPosition_t{xPosNew, yPosNew};
}

void Object2d::update(){
  this->setCurrPos(this->getNextPos());
}