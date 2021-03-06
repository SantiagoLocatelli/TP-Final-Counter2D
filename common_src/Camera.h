#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../client_src/LevelInfo.h"
#include "SDL2/SDL.h"

class Camera {
    private:
        Coordinate pos;
        Size size;

    public:
        Camera(Size size);
        void centerCamera(Coordinate pos);
        void centerCameraOnMouse(int tile_width, int level_width, int level_height);
        void keepInBounds(int level_w, int level_h);

        int getHeight();
        int getWidth();
        int getPosX();
        int getPosY();
        SDL_Rect getRect();
        Size getSize();
};

#endif
