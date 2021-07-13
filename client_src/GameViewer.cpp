#include "GameViewer.h"
#include "Events/gameMath.h"
#include <cstdio>

#define WINDOW_LABEL "Counter-Strike 2D"
#define PATH_POINTER "../../common_src/img/pointer.bmp"
#define PATH_FONT "../../common_src/img/digital-7.ttf"
#define SIZE_CROSSHAIR 25
#define MARGIN 15

#define HUD_AMMO 0
#define HUD_HEALTH 1
#define HUD_TIME 2

const struct Color HUD_COLOR = {0xAD, 0x86, 0x33};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};

const struct Size SIZE_SMALL_GUN = {16, 32};
const struct Size SIZE_BIG_GUN = {20, 60};

const struct Size SIZE_SMALL_GUN_HUD = {20, 20};
const struct Size SIZE_BIG_GUN_HUD = {40, 25};


GameViewer::GameViewer(Size windowSize, LevelInfo level): window(WINDOW_LABEL, windowSize.w, windowSize.h),
    renderer(&window), 
    textureManager(renderer, level.tiles),
    cam(windowSize),
    level(level),
    bullet(renderer){

    SDL_ShowCursor(SDL_DISABLE);
    loadHudTextures();
    loadWeapons();
    loadPlayers(windowSize);
}


SkinType getPjSkin(PlayerInfo player) {
    printf("Team: %i\n", (int)player.team);
    if (player.team == COUNTER) {
        return (SkinType) Math::getRandomNumberBetween((int)CT1, (int)CT4);
    }
    return (SkinType) Math::getRandomNumberBetween((int)TT1, (int)TT4);
}

void GameViewer::loadPlayers(Size window){
    srand((unsigned)time(NULL));
    WeaponType mainWeaponType = this->level.mainPlayer.weapon.type;
    SkinType mainSkinType = getPjSkin(this->level.mainPlayer);
    printf("skin type: %i\n", (int)mainSkinType);
    this->mainPlayer = new MainCharacter( level.mainPlayer, *(this->textureManager.getSkin(mainSkinType)), 
                std::move(CrossHair(SIZE_CROSSHAIR, SIZE_CROSSHAIR, std::move(SdlTexture(renderer, PATH_POINTER, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b)))),
                std::move(Stencil(this->renderer, window)), this->weapons[mainWeaponType]);


    for (PlayerInfo player : this->level.players) {

        WeaponType typeWeapon = player.weapon.type;
        SkinType typeSkin = getPjSkin(player);
        printf("skin type: %i\n", (int)typeSkin);
        this->players.push_back(Character(player, *(this->textureManager.getSkin(typeSkin)), this->weapons[typeWeapon]));
    }
}

// void GameViewer::loadPlayers(Size window){

//     WeaponType mainType = this->level.mainPlayer.weapon.type;

//     this->mainPlayer = new MainCharacter( level.mainPlayer, *(this->textureManager.getSkin(CT1)), 
//                 std::move(CrossHair(SIZE_CROSSHAIR, SIZE_CROSSHAIR, std::move(SdlTexture(renderer, PATH_POINTER, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b)))),
//                 std::move(Stencil(this->renderer, window)), this->weapons[mainType]);


//     for (PlayerInfo player : this->level.players) {

//         WeaponType type = player.weapon.type;
//         this->players.push_back(Character(player, *(this->textureManager.getSkin(CT1)), this->weapons[type]));
//     }
// }

void GameViewer::loadWeapons(){
    this->weapons[KNIFE] = new Weapon(*(this->textureManager.getWeaponOnPj(KNIFE)), *(this->textureManager.getWeaponAnim(KNIFE)), KNIFE);
    this->weapons[PISTOL] = new Weapon(*(this->textureManager.getWeaponOnPj(PISTOL)), *(this->textureManager.getWeaponAnim(PISTOL)), PISTOL);
    this->weapons[RIFLE] = new Weapon(*(this->textureManager.getWeaponOnPj(RIFLE)), *(this->textureManager.getWeaponAnim(RIFLE)), RIFLE);
    this->weapons[SNIPER] = new Weapon(*(this->textureManager.getWeaponOnPj(SNIPER)), *(this->textureManager.getWeaponAnim(SNIPER)), SNIPER);
    this->weapons[SHOTGUN] = new Weapon(*(this->textureManager.getWeaponOnPj(SHOTGUN)), *(this->textureManager.getWeaponAnim(SHOTGUN)), SHOTGUN);
    this->weapons[BOMB] = new Weapon(*(this->textureManager.getWeaponOnPj(BOMB)), *(this->textureManager.getWeaponAnim(BOMB)), BOMB);
}

GameViewer::~GameViewer(){
    delete this->mainPlayer;

    for (auto it = this->hud.begin(); it != this->hud.end(); it++) {
        TextTexture* aux = it->second;
        it++;
        delete aux;
    }

    for (auto it = this->weapons.begin(); it != this->weapons.end(); it++) {
        Weapon* aux = it->second;
        it++;
        delete aux;
    }
}

void GameViewer::loadHudTextures(){
    char ammoText[100];
    sprintf(ammoText, "Ammo: %d", this->level.mainPlayer.ammo);
    // this->hud[HUD_AMMO] = new SdlTexture(this->renderer, PATH_FONT, 30, ammoText, HUD_COLOR.r, HUD_COLOR.g, HUD_COLOR.b );
    this->hud[HUD_AMMO] = new TextTexture(this->renderer, PATH_FONT, 30);
    this->hud[HUD_AMMO]->setText(ammoText, HUD_COLOR);
    
    char healtText[100];
    sprintf(healtText, "❤ %d", (int)this->level.mainPlayer.health);
    // this->hud[HUD_HEALTH] = new SdlTexture(this->renderer, PATH_FONT, 30, healtText, HUD_COLOR.r, HUD_COLOR.g, HUD_COLOR.b );
    this->hud[HUD_HEALTH] = new TextTexture(this->renderer, PATH_FONT, 30);
    this->hud[HUD_HEALTH]->setText(healtText, HUD_COLOR);

}

void GameViewer::renderPlayers(Coordinate cam) {
    for (auto it = this->players.begin(); it != this->players.end(); it++){
        if (!it->isDead()) {
            it->render(cam);

            PlayerInfo player = it->getInfo();
            for (PlayerEffect effect : player.sounds) {
                this->sounds.playPlayerSound(effect);
            }
            if (player.shooting) {
                this->sounds.playWeaponSound(player.weapon.sound);
            }
        }
    }
}

void GameViewer::renderShots(Coordinate cam){
    for (BulletInfo bul : level.bullets) {
        this->bullet.setTrajectory(bul.pos, bul.dst);
        this->bullet.render(cam);
    }
}

void GameViewer::renderWeapons(Coordinate cam){
    for(DropInfo wp : level.drops){
        this->textureManager.getWeaponOnFloor(wp.type)->render(wp.pos.x - cam.x, wp.pos.y - cam.y, wp.size.w, wp.size.h);
    }
}

void GameViewer::renderMap(Coordinate cam){
    int max = (int)this->level.tiles.size();
    for (int i = 0; i < max; i++) {
        uint8_t tile = this->level.tiles[i].id;
        Coordinate pos = this->level.tiles[i].pos;
        Size size = this->level.tiles[i].size;
        this->textureManager.getTiles(tile)->render(pos.x-cam.x, pos.y-cam.y, size.w, size.h);
    }
}

void GameViewer::renderMainPlayer(Coordinate cam){
    this->mainPlayer->render(cam);
}


void GameViewer::renderHud(){

    // char ammoText[100];
    // sprintf(ammoText, "Ammo: %d", this->level.mainPlayer.ammo);
    // this->hud[HUD_AMMO]->changeTextTexture(ammoText, PATH_FONT, 30, HUD_COLOR.r, HUD_COLOR.g, HUD_COLOR.b);

    Coordinate dstAmmo = {this->cam.getWidth() - MARGIN, this->cam.getHeight() - MARGIN};
    this->hud[HUD_AMMO]->render(dstAmmo);
    // this->hud[HUD_AMMO]->setBlendMode(SDL_BLENDMODE_BLEND);
    // this->hud[HUD_AMMO]->setAlpha(100);
    // this->hud[HUD_AMMO]->render(dstAmmo.x - this->hud[HUD_AMMO]->getWidth(), dstAmmo.y - this->hud[HUD_AMMO]->getHeight());


    // char healtText[100];
    // sprintf(healtText, "❤ %d", (int)this->level.mainPlayer.health);
    // this->hud[HUD_HEALTH]->changeTextTexture(healtText, PATH_FONT, 30, HUD_COLOR.r, HUD_COLOR.g, HUD_COLOR.b);

    Coordinate dstHealth = {100, this->cam.getHeight() - MARGIN};
    this->hud[HUD_HEALTH]->render(dstHealth);
    // this->hud[HUD_HEALTH]->setBlendMode(SDL_BLENDMODE_BLEND);
    // this->hud[HUD_HEALTH]->setAlpha(100);
    // this->hud[HUD_HEALTH]->render(dstHealth.x - this->hud[HUD_HEALTH]->getWidth(), dstHealth.y - this->hud[HUD_HEALTH]->getHeight());


    Coordinate dstWeapon = {this->cam.getWidth(), this->cam.getHeight()-100};
    WeaponType type = this->level.mainPlayer.weapon.type;
    Size size = {40, 40};

    // if (type == PISTOL) {
    //     size = SIZE_SMALL_GUN_HUD;
    // } else if (type == RIFLE || type == SNIPER || type == SHOTGUN) {
    //     size = SIZE_BIG_GUN_HUD;
    // }

    if (type != KNIFE) {
        SdlTexture& weapon = *this->textureManager.getWeaponOnHud(type); 
        weapon.render(dstWeapon.x - size.w - MARGIN, dstWeapon.y - size.h, size.w, size.h);
    }
}

void GameViewer::render(){

    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    Coordinate cam = {this->cam.getPosX(), this->cam.getPosY()};
    
    renderMap(cam);
    renderShots(cam);
    renderPlayers(cam);
    renderWeapons(cam);
    renderMainPlayer(cam);
    renderHud();

    renderer.updateScreen();
}



void GameViewer::update(LevelInfo level){

    WeaponType mainType = level.mainPlayer.weapon.type;
    this->mainPlayer->update(level.mainPlayer, this->weapons[mainType]);

    this->level.drops.clear();
    this->level.drops.insert(this->level.drops.begin(), level.drops.begin(), level.drops.end());

    this->level.players.clear();
    this->level.players.insert(this->level.players.begin(), level.players.begin(), level.players.end());
    
    this->level.bullets.clear();
    this->level.bullets.insert(this->level.bullets.begin(), level.bullets.begin(), level.bullets.end());

    auto it = this->players.begin();
    for (PlayerInfo player : this->level.players) {
        if (!player.dead) {
            WeaponType type = player.weapon.type;
            it->update(player, this->weapons[type]);
        }
        it++;
    }

    if (this->level.mainPlayer.health != level.mainPlayer.health) {
        char healtText[100];
        sprintf(healtText, "❤ %d", (int)this->level.mainPlayer.health);
        this->hud[HUD_HEALTH]->setText(healtText, HUD_COLOR);
    } 


    if (this->level.mainPlayer.ammo != level.mainPlayer.ammo) {
        char ammoText[100];
        sprintf(ammoText, "Ammo: %d", (int)this->level.mainPlayer.ammo);
        this->hud[HUD_AMMO]->setText(ammoText, HUD_COLOR);
    } 


    this->cam.centerCamera(level.mainPlayer.pos);
    this->cam.keepInBounds(level.size.w, level.size.h);
    this->level = level;
}

void GameViewer::setCrossHair(Coordinate pos){this->mainPlayer->setCrossHair(pos);}

Coordinate GameViewer::mainPlayerRelativePos(){
    return {this->mainPlayer->getPosX() - this->cam.getPosX(),
            this->mainPlayer->getPosY() - this->cam.getPosY()};
}