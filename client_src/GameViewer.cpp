#include "GameViewer.h"
#include <cstdio>
#include "../../common_src/TextureMap.h"

#define WINDOW_LABEL "Counter-Strike 2D"
#define PATH_POINTER "../../common_src/img/pointer.bmp"
#define PATH_CT1 "../../common_src/img/players/ct1.bmp"
#define PATH_FONT "../../common_src/img/digital-7.ttf"
#define SIZE_CROSSHAIR 25
#define BOX "BOX"
#define BACKGROUND "BG"
#define SIZE_KNIFE 35
#define MARGIN 15

struct Color {
    uint8_t r,g,b;
};

const struct Color NEGRO = {0xFF, 0xFF, 0xFF};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};
const struct Color HUD_COLOR = {0xAD, 0x86, 0x33};

#define PATH_SHOT "../../common_src/sound/weapons/glock18.wav"

GameViewer::GameViewer(int window_w, int window_h, LevelInfo level): window(WINDOW_LABEL, window_w, window_h),
    renderer(&window), 
    cam(window_w, window_h),
    level(level),
    bullet(renderer){

    SDL_ShowCursor(SDL_DISABLE);
    loadTexturesWeapons();
    loadSkins();
    loadTiles();

    WeaponType mainType = level.mainPlayer.weapon.type;
    printf("size  1 w: %i, h: %i\n", level.mainPlayer.weapon.size.w, level.mainPlayer.weapon.size.h);
    Weapon mainWeapon(*(this->weaponOnPj[mainType]), *(this->animWeaponOnPj[mainType]), level.mainPlayer.weapon.size);
    this->mainPlayer = new MainCharacter( level.mainPlayer, *(this->skins[CT]), 
                std::move(CrossHair(SIZE_CROSSHAIR, SIZE_CROSSHAIR, std::move(SdlTexture(renderer, PATH_POINTER, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b)))),
                std::move(Stencil(this->renderer, window_w, window_h)), mainWeapon);

    for (PlayerInfo player : level.players) {
        //crear cuchillo y cargarlo al personaje
        WeaponType type = player.weapon.type;
        printf("size  2 w: %i, h: %i\n", player.weapon.size.w, player.weapon.size.h);
        Weapon weapon(*(this->weaponOnPj[type]), *(this->animWeaponOnPj[type]), player.weapon.size);
        this->players.push_back(Character(player, *(this->skins[CT]), weapon));
    }
}


GameViewer::~GameViewer(){
    if (!this->weaponsOnFloor.empty()) {
        for(auto it = this->weaponsOnFloor.begin(); it != this->weaponsOnFloor.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->weaponsOnFloor.clear();
    }

    if (!this->weaponOnPj.empty()) {
        for(auto it = this->weaponOnPj.begin(); it != this->weaponOnPj.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->weaponOnPj.clear();
    }

    if (!this->tiles.empty()) {
        for(auto it = this->tiles.begin(); it != this->tiles.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->tiles.clear();
    }

    if (!this->weaponOnHud.empty()) {
        for(auto it = this->weaponOnHud.begin(); it != this->weaponOnHud.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->weaponOnHud.clear();
    }

    if (!this->animWeaponOnPj.empty()) {
        for(auto it = this->animWeaponOnPj.begin(); it != this->animWeaponOnPj.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->animWeaponOnPj.clear();
    }

    if (!this->skins.empty()) {
        for(auto it = this->skins.begin(); it != this->skins.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->skins.clear();
    }


}


void GameViewer::loadSkins(){
    this->skins[CT] = new SdlTexture(this->renderer, PATH_CT1, NEGRO.r, NEGRO.g, NEGRO.b);
}


bool isInVector(std::vector<uint8_t> vector, uint8_t element) {
    int max = (int) vector.size();
    int i = 0;
    bool foundIt = false;
    while (i < max && !foundIt) {
        foundIt = (vector[i] == element);
        i++;
    }
    return foundIt;
}

void selectDistinct(std::vector<TileInfo> tiles, std::vector<uint8_t>& distinctTiles) {
    for (TileInfo tile : tiles) {
        if (!isInVector(distinctTiles, tile.id)) {
            distinctTiles.push_back(tile.id);
        }
    }
}

void GameViewer::loadTiles(){
    std::vector<uint8_t> distinctTiles;
    TextureMap textureMap;

    selectDistinct(level.tiles, distinctTiles);
    
    for (uint8_t tile : distinctTiles) {
        this->tiles[tile] = new SdlTexture(this->renderer, textureMap[tile].texturePath); 
    }

}

void GameViewer::loadTexturesWeapons(){

//enum WeaponType : char {KNIFE, PISTOL, SHOTGUN, RIFLE, SNIPER, BOMB, DEFUSER};

    this->weaponOnPj[KNIFE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponOnPj[PISTOL] = new SdlTexture(this->renderer, "../../common_src/img/weapons/glock.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponOnPj[RIFLE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/ak47.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponOnPj[SNIPER] = new SdlTexture(this->renderer, "../../common_src/img/weapons/awp.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponOnPj[SHOTGUN] = new SdlTexture(this->renderer, "../../common_src/img/weapons/m3.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    
    // FALTA CARGAR EL EFECTO DE LAS ARMAS
    this->animWeaponOnPj[KNIFE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/knifeslash.bmp", 0x00, 0x00, 0x00);
    //buscar un efecto de arma piola
    this->animWeaponOnPj[PISTOL] = new SdlTexture(this->renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);
    this->animWeaponOnPj[RIFLE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);
    this->animWeaponOnPj[SNIPER] = new SdlTexture(this->renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);
    this->animWeaponOnPj[SHOTGUN] = new SdlTexture(this->renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);

    this->weaponsOnFloor[PISTOL] = new SdlTexture(this->renderer, "../../common_src/img/weapons/glock_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[SHOTGUN] = new SdlTexture(this->renderer, "../../common_src/img/weapons/m3_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[SNIPER] = new SdlTexture(this->renderer, "../../common_src/img/weapons/awp_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[RIFLE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/ak47_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[BOMB] = new SdlTexture(this->renderer, "../../common_src/img/weapons/bomb_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);

    this->weaponOnHud[PISTOL] = new SdlTexture(this->renderer, "../../common_src/img/weapons/glock_m.bmp", FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b);
    this->weaponOnHud[SNIPER] = new SdlTexture(this->renderer, "../../common_src/img/weapons/awp_m.bmp", FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b);
    this->weaponOnHud[RIFLE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/ak47_m.bmp", FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b);
    this->weaponOnHud[SHOTGUN] = new SdlTexture(this->renderer, "../../common_src/img/weapons/m3_m.bmp", FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b);
    this->weaponOnHud[BOMB] = new SdlTexture(this->renderer, "../../common_src/img/weapons/bomb_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
}


// ESTO EN LA VERSION FINAL NO TIENE QUE IR
void GameViewer::renderPlayers(Coordenada cam) {
    for (auto it = this->players.begin(); it != this->players.end(); it++){
        if (!it->isDead()) {
            it->render(cam.x, cam.y);
        }
    }
}

void GameViewer::renderShots(Coordenada cam){
    for (BulletInfo bul : level.bullets) {
        this->bullet.setTrajectory(bul.pos, bul.dst);
        this->bullet.render(cam);
    }
}

void GameViewer::renderWeapons(Coordenada cam){
    for(DropInfo wp : level.drops){
        this->weaponsOnFloor[wp.type]->render(wp.pos.x - cam.x, wp.pos.y - cam.y, wp.size.w, wp.size.h);
    }
}

void GameViewer::renderMap(Coordenada cam){
    int max = (int)this->level.tiles.size();
    for (int i = 0; i < max; i++) {
        uint8_t tile = this->level.tiles[i].id;
        Coordenada pos = this->level.tiles[i].pos;
        Size size = this->level.tiles[i].size;
        this->tiles[tile]->render(pos.x-cam.x, pos.y-cam.y, size.w, size.h);
    }
}

void GameViewer::renderMainPlayer(Coordenada cam){
    this->mainPlayer->render(cam);
}


void GameViewer::renderHud(){
    char ammoText[100];
    sprintf(ammoText, "Ammo: %d", this->level.mainPlayer.ammo);
    SDL_Point dst = {this->cam.getWidth() - MARGIN, this->cam.getHeight() - MARGIN};

    SdlTexture ammo(this->renderer, PATH_FONT, 30, ammoText, HUD_COLOR.r, HUD_COLOR.g, HUD_COLOR.b );
    ammo.setAlpha(100);
    ammo.setBlendMode(SDL_BLENDMODE_BLEND);
    ammo.render(dst.x - ammo.getWidth(), dst.y - ammo.getHeight());
}

void GameViewer::render(){

    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    Coordenada cam = {this->cam.getPosX(), this->cam.getPosY()};
    
    renderMap(cam);
    renderShots(cam);
    renderPlayers(cam);
    renderWeapons(cam);
    renderMainPlayer(cam);
    renderHud();

    renderer.updateScreen();
}



void GameViewer::update(LevelInfo level){
    this->level = level;

    WeaponType mainType = level.mainPlayer.weapon.type;
    // printf("tipo 1: %i\n", mainType);
    // printf("size  1 w: %i, h: %i\n",level.mainPlayer.weapon.size.w, level.mainPlayer.weapon.size.h);

    Weapon mainWeapon(*(this->weaponOnPj[mainType]), *(this->animWeaponOnPj[mainType]), level.mainPlayer.weapon.size);
    this->mainPlayer->update(level.mainPlayer, mainWeapon);

    this->level.drops.clear();
    this->level.drops.insert(this->level.drops.begin(), level.drops.begin(), level.drops.end());

    this->level.players.clear();
    this->level.players.insert(this->level.players.begin(), level.players.begin(), level.players.end());
    
    this->level.bullets.clear();
    this->level.bullets.insert(this->level.bullets.begin(), level.bullets.begin(), level.bullets.end());

    auto it = this->players.begin();
    auto end = this->players.end();
    for (PlayerInfo player : this->level.players) {
        if (!player.dead && it != end) {
            WeaponType type = player.weapon.type;
            // printf("tipo 2: %i\n", type);
            // printf("size  2 w: %i, h: %i\n", player.weapon.size.w, player.weapon.size.h);
            Weapon weapon(*(this->weaponOnPj[type]), *(this->animWeaponOnPj[type]), player.weapon.size);
            it->update(player, weapon);
        }
    }
    // revisar el constructor por movimiento del character

    this->cam.centerCamera(level.mainPlayer.pos);
    this->cam.keepInBounds(level.width, level.height);
    
}
void GameViewer::setCrossHair(Coordenada pos){this->mainPlayer->setCrossHair(pos);}

Coordenada GameViewer::mainPlayerRelativePos(){
    return {this->mainPlayer->getPosX() - this->cam.getPosX(),
            this->mainPlayer->getPosY() - this->cam.getPosY()};
}