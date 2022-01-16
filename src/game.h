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
  
  ///////////
  // game config
  static constexpr int  _PLAYER_SPEED_INC{1};  // speed increment of player: points per frame
  static constexpr int  _BULLET_SPEED_CONST{-10};  // const speed of bullet: points per frame
  // _SPEED_ENEMY: constant speed of the enenmy
  static constexpr int  _ENEMY_SPEED_INIT{5};  // init value
  static constexpr int  _ENEMY_SPEED_LEV_INC{1};  // increment for each difficulty level

  // ENEMY_SPORN_INTERVALL: Enemy is created every x frames
  static constexpr int _ENEMY_SPORN_INTERVALL_INIT{50}; // init value
  static constexpr int _ENEMY_SPORN_INTERVALL_LEV_INC{-5}; // increment for each difficulty level

  // DIFFICULTY_LEVEL_SCORE: score points which set the difficulty level  
  static constexpr int _DIFFICULTY_LEVEL_SCORE_BASE{10};  // base where the difficulty levels start
  static constexpr int _DIFFICULTY_LEVEL_SCORE_INTERVALL{10}; // score points needed to set the next level

  //
  int _enemySpornIntervall{_ENEMY_SPORN_INTERVALL_INIT};
  int _enemySpeed{_ENEMY_SPEED_INIT};
};

#endif