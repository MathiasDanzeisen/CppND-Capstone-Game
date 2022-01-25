#ifndef GAME_H
#define GAME_H

#include "config.h"
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
  long int GetScore() const;


private:

  void Update(bool &running);
  void AddEnemy();

  long int _score{0};
  

  std::shared_ptr<Logic> _logic;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;
  
  //
  int _enemySpornIntervall{config::ENEMY_SPORN_INTERVALL_INIT};
  int _enemySpeed{config::ENEMY_SPEED_INIT};
};

#endif