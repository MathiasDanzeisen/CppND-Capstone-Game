#ifndef PLAYER_H
#define PLAYER_H

#include "object2d.h"

class Player : public Object2d {
public:
  // constructor
  Player();

  // Fire a bullet
  void fire();
  // check if player is ready to fire
  bool isReadyToFire() const;
  // update player
  void update();

private:
  int _reloadCounter{0};
};
#endif