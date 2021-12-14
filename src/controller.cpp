#include "controller.h"
#include "SDL.h"
#include <iostream>

void Controller::HandleInput(bool &running, Logic &logic) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN:
      HandleKeyEvent(e.key,logic, true);
      break;
    case SDL_KEYUP:
      HandleKeyEvent(e.key, logic, false);
      break;
    default:
      break;
    }
  }
}

void Controller::HandleKeyEvent(SDL_KeyboardEvent &key, Logic &logic, bool setKeyValue) const {
  // ignore repeated key pressed
  if (key.repeat == 0) {
    switch (key.keysym.scancode) {
    case SDL_SCANCODE_UP:
      logic.keyInUp = setKeyValue;
      break;

    case SDL_SCANCODE_DOWN:
      logic.keyInDown = setKeyValue;
      break;

    case SDL_SCANCODE_LEFT:
      logic.keyInLeft = setKeyValue;
      break;

    case SDL_SCANCODE_RIGHT:
      logic.keyInRight = setKeyValue;
      break;
    case SDL_SCANCODE_SPACE:
      logic.keyInAction1 = setKeyValue;
      break;
    default:
      break;
    }
  }
}