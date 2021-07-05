#ifndef __GAME_VIEWER_H__
#define __GAME_VIEWER_H__


#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "Character/particleBullets.h"
#include "Character/character.h"
#include "Character/camera.h"
#include "crosshair.h"
#include "stencil.h"
#include <vector>
#include <map>

class GameViewer{

private:
    SdlWindow window;
    SdlRenderer renderer;

    Camera cam;


    std::map<WeaponType, SdlTexture*> weaponsOnFloor;

    // provisorio {
    std::vector<SdlTexture> textures;
    // }

    std::vector<Character> players;
    CrossHair crosshair;
    Stencil stencil;
    ParticleBullets bullet;
    SdlTexture pjTexture;

public:

    GameViewer(int window_w, int window_h);
    ~GameViewer();

    void setCrossHair(int posX, int posY);
    void render();
    int getRelativePlayerPosX();
    int getRelativePlayerPosY();
};

#endif