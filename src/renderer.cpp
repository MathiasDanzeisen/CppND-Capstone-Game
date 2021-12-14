#include "renderer.h"
#include "SDL_image.h"
#include <algorithm>
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : _screenWidth(screen_width), _screenHeight(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

  // Create Window
  _sdlWindow = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, _screenWidth,
                                _screenHeight, SDL_WINDOW_SHOWN);

  if (nullptr == _sdlWindow) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  _sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == _sdlRenderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(_sdlWindow);
  SDL_Quit();
}

// Clear screen
void Renderer::Clear() {
  SDL_SetRenderDrawColor(_sdlRenderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdlRenderer);
}

// Init
void Renderer::Init(Logic *logic) {

  // player
  initObject2d(*(logic->_player1), "data/player_skunk.png", 30, 30);

}

void Renderer::Render(Logic *logic) {

  // put player on screen
  renderObject2d(*(logic->_player1));

  // render all bullets
  for (long unsigned int i = 0; i < logic->_bullets.size(); i++) {
    if (logic->_bullets.at(i)->getTexture() != nullptr) {
      renderObject2d(*(logic->_bullets.at(i)));
    } else {
      initObject2d(*(logic->_bullets.at(i)), "data/bullet_green_dn_1.png", 25, 25);
    }
  }

  // Update screen
  SDL_RenderPresent(_sdlRenderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(_sdlWindow, title.c_str());
}

void Renderer::initObject2d(Object2d &obj, const std::string filename,
                            const int wPix, const int hPix) {

  SDL_Texture *texture = IMG_LoadTexture(_sdlRenderer, filename.c_str());
  if (texture == nullptr) {
    std::cout << "IMG_LoadTexture failed: " << SDL_GetError();
  }
  obj.setTexture(texture);

  // TODO: remove: Query size (width and hight from texture)
  // SDL_QueryTexture(logic->_player1->getTexture(), NULL, NULL, &dest.w,

  obj.setObjSizePix(wPix, hPix);
  obj.setObjSizePoints(
      std::div(wPix * Logic::POINTS_MAX, this->_screenWidth).quot,
      std::div(hPix * Logic::POINTS_MAX, this->_screenHeight).quot);
}

void Renderer::renderObject2d(const Object2d &obj2d) {
  // rendering
  int x =
      std::div(obj2d.getPosX() * this->_screenWidth, Logic::POINTS_MAX).quot;
  int y =
      std::div(obj2d.getPosY() * this->_screenHeight, Logic::POINTS_MAX).quot;

  SDL_Rect dest = {x, y, obj2d.getObjWPix(), obj2d.getObjHPix()};

  // Render texture with orignal size to dest.x & dest.y
  SDL_RenderCopy(_sdlRenderer, obj2d.getTexture(), NULL, &dest);
}