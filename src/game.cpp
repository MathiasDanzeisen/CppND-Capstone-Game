#include "game.h"
#include <iostream>
#include "SDL.h"
#include "logic.h"

Game::Game() {
  _logic = std::make_shared<Logic>();

}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true; 

  // TODO: Init
  renderer.Init(_logic.get());
  //this->_player1= texture ;

  while (running) {
    frame_start = SDL_GetTicks();

    // Clean screen
    renderer.Clear();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running);
    _logic->_player1->moveToPos(_logic->_player1->getPosX()+1,_logic->_player1->getPosX()+1);
    Update();
    renderer.Render(_logic.get());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

// void Game::PlaceFood() {
  // int x, y;
  // while (true) {
  //   x = random_w(engine);
  //   y = random_h(engine);
  //   // Check that the location is not occupied by a snake item before placing
  //   // food.
  //   if (!snake.SnakeCell(x, y)) {
  //     food.x = x;
  //     food.y = y;
  //     return;
  //   }
  // }
// }

void Game::Update() {
 
}

int Game::GetScore() const { return score; }