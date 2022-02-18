#ifndef IOBJECT2D_H
#define IOBJECT2D_H

#include <memory>
#include <string>
#include <vector>

enum object2dType_t : int { noObject, objectPlayer, objectBullet, objectEnemy };

// size in points (virtual resolution)
struct objSize_t {
  int sizeW;
  int sizeH;
};

// position in points (virtual resolution)
struct objPosition_t {
  int posX;
  int posY;
};

// velocity in points (virtual resolution)/ per frame
struct objVelo_t {
  int veloX;
  int veloY;
};

// interface class for 2d objects
class IObject2d {
public:
  // position in points (not in pixels)
  virtual void setCurrPos(objPosition_t) = 0;
  virtual int getCurrPosX() const = 0;
  virtual int getCurrPosY() const = 0;
  virtual objPosition_t getCurrPos() const = 0;
  virtual objPosition_t getNextPos() const = 0;

  // object velocity (points per frame)
  virtual void setVelo(int vx, int vy) = 0;
  virtual int getVeloX() const = 0;
  virtual int getVeloY() const = 0;
  // object's increment or decrement of velocity (points per frame)
  virtual void accelerate(int dVx, int dVy) = 0;

  // object size
  virtual objSize_t getObjSizePoints() const = 0;
  virtual int getObjWPoints() const = 0;
  virtual int getObjHPoints() const = 0;

  //
  virtual bool checkCollision(IObject2d &Object2d) const = 0;

  // Check if object at the current position is completely on the screen
  virtual bool isObjOnScreen(void) const = 0;
  // Check if object at the new position would be completely on the screen
  // without moving it
  virtual bool isObjOnScreen(objPosition_t pos) const = 0;

  // Get type of object
  virtual object2dType_t getType() const = 0;
};

#endif