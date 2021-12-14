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
        ~Object2d();

        Object2d(const Object2d& other) = delete; // copy constructor
        Object2d(Object2d&& other); // move constructor
        Object2d& operator=(const Object2d& other) = delete; // copy assignment
        Object2d& operator=(Object2d&& other);  // move assignment

        void setTexture(SDL_Texture* texture)  {_texture=texture;};
        SDL_Texture* getTexture() const {return _texture;};

        void moveToPos(int x, int y){ _posX=x;_posY=y;};
        int getPosX() const{return _posX;};
        int getPosy() const{return _posY;};

    private:
        std::string _image_path;
        SDL_Texture *_texture;
        int _posX{0};   //postion in 0..1000 points of screen
        int _posY{0};   //postion in 0..1000 points of screen
        int _veloX{0};  //speed in points per frame
        int _veloY{0};  //

};

#endif