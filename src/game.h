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
  int score{0};
  void Update();
  std::shared_ptr<Logic> _logic;

  //
  static constexpr int  _SPEED_INC_PLAYER{1};  // speed increment of player: points per frame
  static constexpr int  _SPEED_CONST_BULLET{10};  // const speed of bullet: points per frame

};

#endif