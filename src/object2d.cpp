#include "object2d.h"
#include "logic.h"
#include "config.h"
#include <algorithm>
#include <cmath>
#include <iostream>

// constructor
Object2d::Object2d() : _texture(nullptr) {}

// destructor
Object2d::~Object2d() {
  if (_texture != nullptr) {
    SDL_DestroyTexture(_texture);
  }
}

// move constructor
Object2d::Object2d(Object2d &&other) {
  this->_posX = other._posX;
  this->_posY = other._posY;
  this->_veloX = other._veloX;
  this->_veloY = other._veloY;

  this->_texture = other.getTexture();

  other.setTexture(nullptr);
}

// move assignment
Object2d &Object2d::operator=(Object2d &&other) {
  this->_posX = other._posX;
  this->_posY = other._posY;
  this->_veloX = other._veloX;
  this->_veloY = other._veloY;

  this->_texture = other.getTexture();

  other.setTexture(nullptr);
  return *this;
}

bool Object2d::checkCollision(Object2d &otherObj) const {
  // check if x and y axis overlap
  return std::max(this->getPosX(), otherObj.getPosX()) <
             std::min(this->getPosX() + this->getObjWPoints(),
                      otherObj.getPosX() + otherObj.getObjWPoints()) &&
         std::max(this->getPosY(), otherObj.getPosY()) <
             std::min(this->getPosY() + this->getObjHPoints(),
                      otherObj.getPosY() + otherObj.getObjHPoints());
}

bool Object2d::IsObjOnScreen (void) const{

auto xPoints = this->getPosX();
auto yPoints = this->getPosY();

return this->IsObjOnScreen (xPoints, yPoints);

}

bool Object2d::IsObjOnScreen (int xPoints, int yPoints) const{

  return (xPoints >= config::VRES_POINTS_MIN &&
    (xPoints + this->getObjWPoints()) <= config::VRES_POINTS_MAX &&
    yPoints >= config::VRES_POINTS_MIN &&
    (yPoints + this->getObjHPoints()) <= config::VRES_POINTS_MAX);
}