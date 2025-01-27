#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "SDL.h"
#include "iobject2d.h"

#include <memory>
#include <string>
#include <vector>

// base class for 2d objects
class Object2d : public IObject2d {
public:
  Object2d();
  ~Object2d();

  Object2d(const Object2d &other) = delete;            // copy constructor
  Object2d(Object2d &&other);                          // move constructor
  Object2d &operator=(const Object2d &other) = delete; // copy assignment
  Object2d &operator=(Object2d &&other);               // move assignment

  virtual void init();

  // position in points (not in pixels)
  void setCurrPos(const objPosition_t &pos) final { _pos = pos; };
  int getCurrPosX() const final { return _pos.posX; };
  int getCurrPosY() const final { return _pos.posY; };
  const objPosition_t& getCurrPos() const final { return _pos; };
  objPosition_t getNextPos() const final;

  // object velocity (points per frame)
  void setVelo(int vx, int vy) final {
    _veloX = vx;
    _veloY = vy;
  };
  int getVeloX() const final { return _veloX; };
  int getVeloY() const final { return _veloY; };
  // object's increment or decrement of velocity (points per frame)
  void accelerate(int dVx, int dVy) override {
    _veloX = _veloX + dVx;
    _veloY = _veloY + dVy;
  };

  // Update object, e.g move to position according to current velocity
  virtual void update();

  // object size
  objSize_t getObjSizePoints() const { return _objSizePoints; };
  int getObjWPoints() const { return _objSizePoints.sizeW; };
  int getObjHPoints() const { return _objSizePoints.sizeH; };

  // Check if this object collides with otherObj
  bool checkCollision(const IObject2d &otherObj) const override;

  // Check if object at the current position is completely on the screen
  bool isObjOnScreen(void) const;
  // Check if object at the new position would be completely on the screen
  // without moving it
  bool isObjOnScreen(const objPosition_t &pos) const;

  // Get the type of this object
  object2dType_t getType() const final { return _type; };

protected:
  objPosition_t _pos{0,
                     0}; // postion in VRES_POINTS_MIN..config::VRES_POINTS_MAX
                         // points of screen
  int _veloX{0};                  // speed in points per frame
  int _veloY{0};                  //
  objSize_t _objSizePoints{0, 0}; // object Width in points
  object2dType_t _type{noObject};
};

#endif