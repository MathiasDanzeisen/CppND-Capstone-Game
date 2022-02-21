#include "renderer.h"
#include "SDL_image.h"
#include "config.h"
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
  for (const auto &[key, textureFile] : _mapObj2TextFilename) {
    initTexture(textureFile);
  }
}

Renderer::~Renderer() {
  for (const auto &[key, texture] : _sdlTextures) {
    if (texture != nullptr) {
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

  static SDL_Texture *textureBackgrd =
      IMG_LoadTexture(_sdlRenderer, config::BACKGROUND_GRAPIC_PATH);
  if (textureBackgrd == nullptr) {
    std::cout << "IMG_LoadTexture failed: " << SDL_GetError();
  }
  SDL_RenderCopy(_sdlRenderer, textureBackgrd, NULL, &dest);

  // put player on screen
  renderObject2d(*(logic->_player1));

  // render all bullets
  if (!logic->_bullets.empty()) {
    auto iterBullet = logic->_bullets.cbegin();
    while (iterBullet != logic->_bullets.cend()) {
      renderObject2d(*(*iterBullet));
      iterBullet++;
    }
  }

  // render all enemies
  if (!logic->_enemies.empty()) {
    auto iterEnem = logic->_enemies.cbegin();
    while (iterEnem != logic->_enemies.cend()) {
      renderObject2d(*(*iterEnem));
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
  if (!filename.empty()) {
    _sdlTextures.emplace(filename,
                         IMG_LoadTexture(_sdlRenderer, filename.c_str()));

    // do error handling
    if (_sdlTextures[filename] == nullptr) {
      std::cerr << "IMG_LoadTexture failed: " << SDL_GetError();
    }
  } else {
    std::cerr << "File not found:" << filename << ".\n";
  }
}

SDL_Texture *Renderer::getObjTexture(const Object2d &obj) const {
  object2dType_t type = obj.getType();
  const std::string file(_mapObj2TextFilename.at(type));
  return this->getObjTexture(file);
}

SDL_Texture *Renderer::getObjTexture(const std::string filename) const {
  return this->_sdlTextures.at(filename);
}

sizePix_t Renderer::getObjSizePix(const Object2d &obj) const {

  auto sizePoints = obj.getObjSizePoints();
  auto sizePix = Pos2Pix(objPosition_t{sizePoints.sizeW, sizePoints.sizeH});

  return sizePix_t{sizePix.pPixX, sizePix.pPixY};
}

void Renderer::renderObject2d(const Object2d &obj2d) {
  // rendering
  auto posPix = Pos2Pix(obj2d.getCurrPos());
  auto sizePix = getObjSizePix(obj2d);
  SDL_Rect dest = {posPix.pPixX, posPix.pPixY, sizePix.sPixW, sizePix.sPixH};

  // Render texture with original size to dest.x & dest.y
  SDL_RenderCopy(_sdlRenderer, getObjTexture(obj2d), NULL, &dest);
}

objPosition_t Renderer::Pix2Pos(positionPix_t pixPos) const {
  objPosition_t ret{0, 0};
  ret.posX =
      std::div(pixPos.pPixX * config::VRES_POINTS_MAX, this->_screenWidth).quot;
  ret.posX =
      std::div(pixPos.pPixY * config::VRES_POINTS_MAX, this->_screenHeight)
          .quot;
  return ret;
}
positionPix_t Renderer::Pos2Pix(objPosition_t pos) const {
  positionPix_t ret{0, 0};
  ret.pPixX =
      std::div(pos.posX * this->_screenWidth, config::VRES_POINTS_MAX).quot;
  ret.pPixY =
      std::div(pos.posY * this->_screenHeight, config::VRES_POINTS_MAX).quot;
  return ret;
}
