#include "object2d.h"
#include "logic.h"
#include <cmath>
#include <algorithm>
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

bool Object2d::checkCollision(Object2d otherObj) const {
  // check if x and y axix overlap
  //std::max(this->get)
//(MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));

  return false;
}