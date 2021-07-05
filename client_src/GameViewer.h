#ifndef __GAME_VIEWER_H__
#define __GAME_VIEWER_H__


#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "Character/particleBullets.h"
#include "Character/character.h"
#include "Character/camera.h"
#include <string>   
#include <list>
#include <map>

class GameViewer{

private:
    
    SdlWindow window;
    SdlRenderer renderer;
    Camera cam;


    std::map<WeaponType, SdlTexture*> weaponOnPj;
    std::map<WeaponType, SdlTexture*> weaponsOnFloor;
    std::map<std::string, SdlTexture*> textures;


    ParticleBullets bullet;
    std::list<Character> players;
    MainCharacter mainPlayer;

    // provisorio para poder renderizar a los demas pjs
    SdlTexture pjTexture;


    void renderPlayers(int camX, int camY);
    void renderBoxes(int camX, int camY);

    void renderShots(int camX, int camY);
    void renderWeapons(int camX, int camY);
    void addPlayer(const char* pathTexture, struct Color color);
    void initializeGame(ModelInfo model);
    // ver si es necesaria
    void addTexture(const char* pathTexture, struct Color color);
    void loadWeapons();
public:

    GameViewer(int window_w, int window_h, LevelInfo level);
    ~GameViewer();

    void setCrossHair(Coordenada pos);
    Coordenada mainPlayerRelativePos();
    void render();

    GameViewer& operator=(const GameViewer&) = delete;
    GameViewer(const GameViewer& other) = delete;
};

#endif