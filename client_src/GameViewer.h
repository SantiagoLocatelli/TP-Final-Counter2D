#ifndef __GAME_VIEWER_H__
#define __GAME_VIEWER_H__

#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Sdl/TextTexture.h"
#include "Character/particleBullets.h"
#include "Character/mainCharacter.h"
#include "Character/character.h"
#include "Character/camera.h"
#include "TextureManager.h"
#include "SoundEffects.h"
#include <algorithm>
#include <memory>
#include <mutex>
#include <list>
#include <map>

class GameViewer{

private:
    
    std::mutex m;
    SdlWindow window;
    SdlRenderer renderer;
    SoundEffects sounds;
    TextureManager textureManager;
    int delaySound = 0;
    bool buyMenuOpen = false;

    Camera cam;

    LevelInfo level;

    std::map<WeaponType, Weapon*> weapons;
    std::map<int, std::unique_ptr<TextTexture>> hud;
    std::list<Character> players;
    std::unique_ptr<MainCharacter> mainPlayer;
    TextTexture digitalText;
    TextTexture aerialText;
    ParticleBullets bullet;
    
    void renderBorder(Coordinate pos, Size sizeRect, int borderWidth, struct Color color, int opacity);
    void renderWeaponOnMenu(WeaponType weapon, SDL_Rect box, Size unit, const char* text);
    void renderMainPlayer(Coordinate cam);
    void renderBombSites(Coordinate cam);
    void renderExplosion(Coordinate cam);
    void renderPlayers(Coordinate cam);
    void renderWeapons(Coordinate cam);
    void renderShots(Coordinate cam);
    void renderBomb(Coordinate cam);
    void renderMap(Coordinate cam);
    void renderBuyMenu();
    void renderHud();
    void showRoundState();

    void updateHud(LevelInfo level);
    
    void loadPlayers(Size);
    void loadHudTextures();
    void loadWeapons();

public:

    GameViewer(Size windowSize, LevelInfo level);
    ~GameViewer();

    void setCrossHair(Coordinate pos);
    Coordinate mainPlayerRelativePos();
    void render();
    void update(LevelInfo level);
    void toggleBuyMenu();

    GameViewer& operator=(const GameViewer&) = delete;
    GameViewer(const GameViewer& other) = delete;
};

#endif