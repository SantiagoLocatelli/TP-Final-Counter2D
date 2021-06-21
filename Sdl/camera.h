#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL2/SDL.h>

class Camera {
    private:
        SDL_Rect camera;

    public:
        Camera(int camera_width, int camera_height);
        void centerCamera(SDL_Rect character);
        void keepInBounds(int level_w, int level_h);

        int getPosX();
        int getPosY();
        SDL_Rect* getRect();
};

#endif
