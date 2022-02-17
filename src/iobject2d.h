#ifndef IOBJECT2D_H
#define IOBJECT2D_H

#include <vector>
#include <string>
#include <memory>

enum Object2dType : int
{
    noObject,
    objectPlayer,
    objectBullet,
    objectEnemy
};

// interface class for 2d objects
class IObject2d {
    public:
        // position in points (not in pixels)
        virtual void moveToPos(int x, int y) =0;
        virtual int getPosX() const =0;
        virtual int getPosY() const =0; 

        // object velocity (points per frame)
        virtual void setVelo(int vx, int vy) =0;
        virtual int getVeloX()const =0;
        virtual int getVeloY()const =0;
        // object's increment or decrement of velocity (points per frame)
        virtual void accelerate(int dVx, int dVy) =0;

        //object size
        virtual int getObjWPoints() const =0;
        virtual int getObjHPoints() const =0;

        // 
        virtual bool checkCollision(IObject2d & Object2d) const = 0;

        // Check if object at the current position is completely on the screen
        virtual bool isObjOnScreen (void) const = 0;
        // Check if object at the new position would be completely on the screen without moving it
        virtual bool isObjOnScreen (int xPoints, int yPoints) const = 0;

        // Get type of object
        virtual Object2dType getType() const = 0;
};

#endif