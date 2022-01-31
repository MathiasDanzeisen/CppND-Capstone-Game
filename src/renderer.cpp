#include "config.h"
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
  initObject2d(*(logic->_player1), config::PLAYER1_GRAPIC_PATH, config::PLAYER1_GRAPIC_SIZE, config::PLAYER1_GRAPIC_SIZE);

}

void Renderer::Render(Logic *logic) {

  // Render background
    static SDL_Rect dest;
		dest.x = 0;
		dest.y = 0;
		dest.w = _screenWidth;
		dest.h = _screenHeight;

  // TODO: set file names in header file
  static SDL_Texture *textureBackgrd = IMG_LoadTexture(_sdlRenderer, config::BACKGROUND_GRAPIC_PATH);
  // #TODO: do error handling
  if (textureBackgrd == nullptr) {
    std::cout << "IMG_LoadTexture failed: " << SDL_GetError();
  }
  SDL_RenderCopy(_sdlRenderer, textureBackgrd, NULL, &dest);


  // put player on screen
  renderObject2d(*(logic->_player1));

  // render all bullets
  if (!logic->_bullets.empty()){
    auto iterBullet = logic->_bullets.begin();
    while (iterBullet != logic->_bullets.end()) {
      if ((*iterBullet)->getTexture() != nullptr) {
        renderObject2d(*(*iterBullet));
      } else {
        initObject2d(*(*iterBullet), config::BULLET_GRAPIC_PATH, config::BULLET_GRAPIC_SIZE, config::BULLET_GRAPIC_SIZE);
      }
      iterBullet++;
    }
  }

  // render all enemies
  if (!logic->_enemies.empty()){
    auto iterEnem = logic->_enemies.begin();
    while (iterEnem != logic->_enemies.end()) {
      if ((*iterEnem)->getTexture() != nullptr) {
        renderObject2d(*(*iterEnem));
      } else {
        initObject2d(*(*iterEnem), config::ENEMY_GRAPIC_PATH, config::ENEMY_GRAPIC_SIZE, config::ENEMY_GRAPIC_SIZE);
      }
      iterEnem++;
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
  // #TODO: do error handling
  if (texture == nullptr) {
    std::cout << "IMG_LoadTexture failed: " << SDL_GetError();
  }
  obj.setTexture(texture);

  // TODO: remove: Query size (width and hight from texture)
  // SDL_QueryTexture(logic->_player1->getTexture(), NULL, NULL, &dest.w,

  obj.setObjSizePix(wPix, hPix);
  obj.setObjSizePoints(
      std::div(wPix * config::VRES_POINTS_MAX, this->_screenWidth).quot,
      std::div(hPix * config::VRES_POINTS_MAX, this->_screenHeight).quot);
}

void Renderer::renderObject2d(const Object2d &obj2d) {
  // rendering
  int x =
      std::div(obj2d.getPosX() * this->_screenWidth, config::VRES_POINTS_MAX).quot;
  int y =
      std::div(obj2d.getPosY() * this->_screenHeight, config::VRES_POINTS_MAX).quot;

  SDL_Rect dest = {x, y, obj2d.getObjWPix(), obj2d.getObjHPix()};

  // Render texture with original size to dest.x & dest.y
  SDL_RenderCopy(_sdlRenderer, obj2d.getTexture(), NULL, &dest);
}