#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL.h"
#include "logic.h"

class Controller {
 public:
  void HandleInput(bool &running,Logic& logic) const;
 private:
  // Mapping keyboard keys to game logic
  //  setKeyValue : sets game logic for the specifc action 
  void HandleKeyEvent(SDL_KeyboardEvent &key, Logic &logic, bool setKeyValue) const;

};

#endif