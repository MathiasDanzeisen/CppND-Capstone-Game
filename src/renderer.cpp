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

  // Load textures
  for (const auto& [key, textureFile] : _mapObj2TextFilename) {
    //TODO: remove debug
    //std::cout << '[' << key << "] = " << texture << "; ";
    initTexture(textureFile);
  }
}

Renderer::~Renderer() {
  
  for (const auto& [key, texture] : _sdlTextures) {
    //TODO: remove debug
    //std::cout << '[' << key << "] = " << texture << "; ";
    if (texture != nullptr){
      SDL_DestroyTexture(texture);
    }
  }
  SDL_DestroyWindow(_sdlWindow);
  SDL_Quit();
}

// Clear screen
void Renderer::Clear() {
  SDL_SetRenderDrawColor(_sdlRenderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdlRenderer);
}

void Renderer::Render(Logic *logic) {

  // Render background
    static SDL_Rect dest;
		dest.x = 0;
		dest.y = 0;
		dest.w = _screenWidth;
		dest.h = _screenHeight;

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
    auto iterBullet = logic->_bullets.cbegin();
    while (iterBullet != logic->_bullets.cend()) {
      // if (getObjTexture((*iterBullet)) != nullptr) {
        renderObject2d(*(*iterBullet));
      // } else {
      //   initObject2d(*(*iterBullet), config::BULLET_GRAPIC_SIZE, config::BULLET_GRAPIC_SIZE);
      // }
      iterBullet++;
    }
  }

  // render all enemies
  if (!logic->_enemies.empty()){
    auto iterEnem = logic->_enemies.cbegin();
    while (iterEnem != logic->_enemies.cend()) {
      // if (getObjTexture((*iterEnem)) != nullptr) {
        renderObject2d(*(*iterEnem));
      // } else {
      //   initObject2d(*(*iterEnem),  config::ENEMY_GRAPIC_SIZE, config::ENEMY_GRAPIC_SIZE);
      // }
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

void Renderer::initTexture(const std::string filename) {
  // 
  if (!filename.empty()){
    _sdlTextures.emplace(filename,IMG_LoadTexture(_sdlRenderer, filename.c_str()));
    
    // do error handling
    if (_sdlTextures[filename] == nullptr) {
      std::cout << "IMG_LoadTexture failed: " << SDL_GetError();
    } 
  }

}

SDL_Texture* Renderer::getObjTexture(const Object2d &obj) const{
  Object2dType type = obj.getType();
  auto file = _mapObj2TextFilename.at(type);
  return _sdlTextures.at(file);
}

int Renderer::getObjSizePix(const Object2d &obj) const{
  // all objects are have equal height and width so far
  return Pos2Pix(obj.getObjHPoints());
}

void Renderer::renderObject2d(const Object2d &obj2d) {
  // rendering
  int x = Pos2Pix(obj2d.getPosX());
  int y = Pos2Pix(obj2d.getPosY());

  SDL_Rect dest = {x, y,  getObjSizePix(obj2d),  getObjSizePix(obj2d)};


  // Render texture with original size to dest.x & dest.y
  SDL_RenderCopy(_sdlRenderer, getObjTexture(obj2d), NULL, &dest);
}

int Renderer::Pix2Pos( int pix) const{
  return std::div(pix * config::VRES_POINTS_MAX, this->_screenWidth).quot;
}
int Renderer::Pos2Pix( int pos) const{
  return std::div(pos * this->_screenHeight, config::VRES_POINTS_MAX).quot;
}
