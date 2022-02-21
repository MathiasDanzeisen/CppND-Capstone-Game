#ifndef LOGIC_H
#define LOGIC_H

#include "SDL.h"
#include "bullet.h"
#include "enemy.h"
#include "object2d.h"
#include "player.h"

#include <list>
#include <memory>
#include <string>

// base class for logic
class Logic {
public:
  Logic();
  // store user keyboard input
  bool keyInUp{false};
  bool keyInDown{false};
  bool keyInRight{false};
  bool keyInLeft{false};
  bool keyInAction1{false};

  // Pointer to player
  std::unique_ptr<Player> _player1;
  // List of bullets in the game
  std::list<std::unique_ptr<Bullet>> _bullets;
  // List of enemies in the game
  std::list<std::unique_ptr<Enemy>> _enemies;
};

#endif