#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "iobject2d.h"
#include "SDL.h"

#include <vector>
#include <string>
#include <memory>

// base class for 2d objects
class Object2d : public IObject2d {
    public:
        Object2d();
        //Object2d(std::string image_path);
        ~Object2d();

        Object2d(const Object2d& other) = delete; // copy constructor
        Object2d(Object2d&& other); // move constructor
        Object2d& operator=(const Object2d& other) = delete; // copy assignment
        Object2d& operator=(Object2d&& other);  // move assignment

        virtual void init();

        // position in points (not in pixels)
        void moveToPos(int x, int y)final{ _posX=x;_posY=y;};
        int getPosX() const final{return _posX;}; 
        int getPosY() const final{return _posY;}; 

        // object velocity (points per frame)
        void setVelo(int vx, int vy) final{_veloX = vx; _veloY=vy;};
        int getVeloX()const final{return _veloX;};
        int getVeloY()const final{return _veloY;};
        // object's increment or decrement of velocity (points per frame)
        void accelerate(int dVx, int dVy)override{_veloX = _veloX+dVx; _veloY=_veloY+dVy;};

        //object size
        // void setObjSizePix(int w, int h){_objWidPix=w; _objHeiPix=h;};
        // int getObjWPix() const{return _objWidPix;};
        // int getObjHPix() const{return _objHeiPix;};
        // void setObjSizePoints(int w, int h){_objWidPoints=w; _objHeiPoints=h;};
        int getObjWPoints() const{return _objWidPoints;};
        int getObjHPoints() const{return _objHeiPoints;};

        // 
        bool checkCollision(IObject2d & otherObj) const override;

        // Check if object at the current position is completely on the screen
        bool isObjOnScreen (void) const;
        // Check if object at the new position would be completely on the screen without moving it
        bool isObjOnScreen (int xPoints, int yPoints) const;

        Object2dType getType() const final {return _type;};

    protected:
        int _posX{0};   //postion in VRES_POINTS_MIN..config::VRES_POINTS_MAX points of screen
        int _posY{0};   //postion in VRES_POINTS_MIN..config::VRES_POINTS_MAX points of screen
        int _veloX{0};  //speed in points per frame
        int _veloY{0};  //
        // int _objWidPix{0};   // object Width in pixel
        // int _objHeiPix{0};
        int _objWidPoints{0};   // object Width in points
        int _objHeiPoints{0};
        Object2dType _type{noObject};
};

#endif