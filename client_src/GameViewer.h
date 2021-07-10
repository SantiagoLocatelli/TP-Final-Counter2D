#ifndef __GAME_VIEWER_H__
#define __GAME_VIEWER_H__

#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Sdl/sdl_mixer.h"
#include "Character/particleBullets.h"
#include "Character/mainCharacter.h"
#include "Character/character.h"
#include "Character/camera.h"
#include "SoundEffects.h"
#include <string>   
#include <vector>
#include <list>
#include <map>

class GameViewer{

private:
    
    SdlWindow window;
    SdlRenderer renderer;
    SoundEffects sounds;

    Camera cam;

    LevelInfo level;

    std::map<SkinType, SdlTexture*> skins;
    std::map<WeaponType, SdlTexture*> weaponOnPj;
    std::map<WeaponType, SdlTexture*> animWeaponOnPj;
    std::map<WeaponType, SdlTexture*> weaponsOnFloor;
    std::map<WeaponType, SdlTexture*> weaponOnHud;
    std::map<uint8_t, SdlTexture*> tiles;


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
    
    void loadTexturesWeapons();
    void loadSkins();
    void loadTiles();

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