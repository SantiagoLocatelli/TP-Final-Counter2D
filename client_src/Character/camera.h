#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../levelInfo.h"
#include "SDL2/SDL.h"

class Camera {
    private:
        Coordenada pos;
        Size size;

    public:
        Camera(int camera_width, int camera_height);
        void centerCamera(Coordenada pos);
        void centerCameraOnMouse(int tile_width, int level_width, int level_height);
        void keepInBounds(int level_w, int level_h);

        int getHeight();
        int getWidth();
        int getPosX();
        int getPosY();
        SDL_Rect getRect();
};

#endif
