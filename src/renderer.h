#ifndef RENDERER_H
#define RENDERER_H


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
  SDL_Window *_sdlWindow;
  SDL_Renderer *_sdlRenderer;

  const std::size_t _screenWidth;
  const std::size_t _screenHeight;

  // Load image into boject and set size
  void initObject2d(Object2d &obj, const std::string filename, const int wPix, const int hPix);
  // Put object on window
  void renderObject2d(const Object2d &obj);
  // TODO: remove
};

#endif