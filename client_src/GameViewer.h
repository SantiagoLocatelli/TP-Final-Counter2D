#ifndef __GAME_VIEWER_H__
#define __GAME_VIEWER_H__


#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Sdl/sdl_mixer.h"
#include "Character/particleBullets.h"
#include "Character/mainCharacter.h"
#include "Character/character.h"
#include "Character/camera.h"
#include <string>   
#include <list>
#include <map>

class GameViewer{

private:
    
    SdlWindow window;
    SdlRenderer renderer;
    SdlMixer mixer;
    
    Camera cam;

    LevelInfo level;

    std::map<WeaponType, SdlTexture*> weaponOnPj;
    std::map<WeaponType, SdlTexture*> animWeaponOnPj;
    std::map<WeaponType, SdlTexture*> weaponsOnFloor;
    std::map<std::string, SdlTexture*> textures;


    ParticleBullets bullet;
    std::list<Character> players;
    MainCharacter* mainPlayer;

    // provisorio para poder renderizar a los demas pjs
    SdlTexture pjTexture;

    void createWeapon(PlayerInfo player, ProtPlayer prot);
    void renderMainPlayer(Coordenada cam);
    void renderPlayers(Coordenada cam);
    void renderWeapons(Coordenada cam);
    void renderShots(Coordenada cam);
    void renderMap(Coordenada cam);
    
    void loadTexturesWeapons();
    void loadMap();

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