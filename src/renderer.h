#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <vector>

#include "iobject2d.h"
#include "logic.h"

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(Logic *logic);
  
  // Clear screen
  void Clear();
  void UpdateWindowTitle(int score, int fps);

  // helpers
  int Pix2Pos(int pix) const;
  int Pos2Pix(int pos) const;

private:
  SDL_Window *_sdlWindow;
  SDL_Renderer *_sdlRenderer;
  std::map<std::string, SDL_Texture *> _sdlTextures;

  const std::size_t _screenWidth;
  const std::size_t _screenHeight;

  std::map<Object2dType, std::string> _mapObj2TextFilename{
      {noObject, ""},
      {objectPlayer, config::PLAYER1_GRAPIC_PATH},
      {objectBullet, config::BULLET_GRAPIC_PATH},
      {objectEnemy, config::ENEMY_GRAPIC_PATH},
  };


  // set size
  void initObject2d(Object2d &obj, const int wPix, const int hPix);
  // Load image
  void initTexture(const std::string filename);
  // Put object on window
  void renderObject2d(const Object2d &obj);
  // Get texture for a object
  SDL_Texture *getObjTexture(const Object2d &obj) const;
  // Get size of on object in pixel
  int getObjSizePix(const Object2d &obj) const;
};

#endif