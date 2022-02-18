#include "player.h"
#include "config.h"

Player::Player() {
  this->_type = objectPlayer;
  _objSizePoints.sizeW = config::PLAYER1_GRAPIC_SIZE;
  _objSizePoints.sizeH = config::PLAYER1_GRAPIC_SIZE;
}


void Player::fire() { this->_reloadCounter = config::PLAYER_RELOAD_INTERVALL; }

bool Player::isReadyToFire() const { return _reloadCounter == 0; }

void Player::update() {
  if (this->_reloadCounter > 0) {
    this->_reloadCounter--;
  }
  Object2d::update();
}
