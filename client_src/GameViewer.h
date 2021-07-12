#ifndef __GAME_VIEWER_H__
#define __GAME_VIEWER_H__

#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "Character/particleBullets.h"
#include "Character/mainCharacter.h"
#include "Character/character.h"
#include "Character/camera.h"
#include "TextureManager.h"
#include "SoundEffects.h"
#include <list>
#include <map>

class GameViewer{

private:
    
    SdlWindow window;
    SdlRenderer renderer;
    SoundEffects sounds;
    TextureManager textureManager;

    Camera cam;

    LevelInfo level;

    std::map<WeaponType, Weapon> weapons;
    ParticleBullets bullet;
    std::list<Character> players;
    MainCharacter* mainPlayer;


    void createWeapon(PlayerInfo player, ProtPlayer prot);
    void renderMainPlayer(Coordenada cam);
    void renderPlayers(Coordenada cam);
    void renderWeapons(Coordenada cam);
    void renderShots(Coordenada cam);
    void renderMap(Coordenada cam);
    void renderHud();

public:

    GameViewer(int window_w, int window_h, LevelInfo level);
    ~GameViewer();

    void setCrossHair(Coordenada pos);
    Coordenada mainPlayerRelativePos();
    void render();
    void update(LevelInfo level);

    GameViewer& operator=(const GameViewer&) = delete;
    GameViewer(const GameViewer& other) = delete;
};

#endif