#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "SDL.h"

#include <vector>
#include <string>
#include <memory>

// base class for 2d objects
class Object2d {
    public:
        Object2d();
        //Object2d(SDL_Texture *_texture); // TODO: remove
        ~Object2d();

        Object2d(const Object2d& other) = delete; // copy constructor
        Object2d(Object2d&& other); // move constructor
        Object2d& operator=(const Object2d& other) = delete; // copy assignment
        Object2d& operator=(Object2d&& other);  // move assignment

        void setTexture(SDL_Texture* texture)  {_texture=texture;};
        SDL_Texture* getTexture() const {return _texture;};

        // position in points (not in pixels)
        void moveToPos(int x, int y){ _posX=x;_posY=y;};
        int getPosX() const{return _posX;}; 
        int getPosY() const{return _posY;}; 

        // object velocity (points per frame)
        void setVelo(int vx, int vy){_veloX = vx; _veloY=vy;};
        int getVeloX()const{return _veloX;};
        int getVeloY()const{return _veloY;};
        void accelerate(int d_vx, int d_vy){_veloX = _veloX+d_vx; _veloY=_veloY+d_vy;};

        //object size
        void setObjSizePix(int w, int h){_objWidPix=w; _objHeiPix=h;};
        int getObjWPix() const{return _objWidPix;};
        int getObjHPix() const{return _objHeiPix;};
        void setObjSizePoints(int w, int h){_objWidPoints=w; _objHeiPoints=h;};
        int getObjWPoints() const{return _objWidPoints;};
        int getObjHPoints() const{return _objHeiPoints;};

        // 
        bool checkCollision(Object2d & otherObj) const;

    private:
        //std::string _image_path; //TODO: remove
        SDL_Texture *_texture;
        int _posX{0};   //postion in VRES_POINTS_MIN..config::VRES_POINTS_MAX points of screen
        int _posY{0};   //postion in VRES_POINTS_MIN..config::VRES_POINTS_MAX points of screen
        int _veloX{0};  //speed in points per frame
        int _veloY{0};  //
        int _objWidPix{0};   // object Width in pixel
        int _objHeiPix{0};
        int _objWidPoints{0};   // object Width in points
        int _objHeiPoints{0};
};

#endif