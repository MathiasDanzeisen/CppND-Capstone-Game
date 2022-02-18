#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include <vector>

#include "config.h"
#include "iobject2d.h"
#include "logic.h"


// position in pixel
struct positionPix_t {
  int pPixX;
  int pPixY;
};

// size in pixel
struct sizePix_t {
  int sPixW;
  int sPixH;
};

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  // Render all objects on the screen
  void Render(Logic *logic);
  
  // Clear screen
  void Clear();
  // Update the text in  window title
  void UpdateWindowTitle(int score, int fps);

  ////// helpers
  // Convert position measured from pixel to position in virtual resultion
  objPosition_t Pix2Pos(positionPix_t pixPos) const;
  // Convert position from virtual resultion to pixel
  positionPix_t Pos2Pix(objPosition_t pos) const;

private:
  SDL_Window *_sdlWindow;
  SDL_Renderer *_sdlRenderer;
  // Store addresses to textures for different objectTypes
  std::map<std::string, SDL_Texture *> _sdlTextures;

  // Size of the screen in pixels
  const std::size_t _screenWidth;
  const std::size_t _screenHeight;

  // Define with objectType is rendered with with files
  const std::map<object2dType_t, std::string> _mapObj2TextFilename{
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
  // Get texture for a filename
  SDL_Texture *getObjTexture(const std::string filename) const;
  // Get size of on object in pixel
  sizePix_t getObjSizePix(const Object2d &obj) const;
};

#endif