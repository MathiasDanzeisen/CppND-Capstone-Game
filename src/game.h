#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "object2d.h"
#include "renderer.h"
#include <memory>
#include <random>

class Game {
public:
  Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;


private:

  void Update();
  void AddEnemy();

  int score{0};
  int enemySpornIntervall{10}; // Enemy is created every x frames

  std::shared_ptr<Logic> _logic;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  //
  static constexpr int  _SPEED_INC_PLAYER{1};  // speed increment of player: points per frame
  static constexpr int  _SPEED_CONST_BULLET{-10};  // const speed of bullet: points per frame
  static constexpr int  _SPEED_CONST_ENEMY{10};
};

#endif