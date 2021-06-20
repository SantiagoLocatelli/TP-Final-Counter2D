#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL2/SDL.h>

class Camera {
    private:
        SDL_Rect camera;
        int level_height;
        int level_width;

    public:
        Camera(int camera_width, int camera_height, 
            int level_width, int level_height);
        void centerCamera(SDL_Rect character);
        void keepInBounds();

        int getPosX();
        int getPosY();
        SDL_Rect* getRect();
};

#endif
