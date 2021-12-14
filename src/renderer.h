#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include <vector>

// TODO: remove
#include "object2d.h"
#include "logic.h"

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(Logic *logic);
  // init objects
  void Init(Logic *logic);
  // Clear screen
  void Clear();
  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;

  // TODO: remove
};

#endif