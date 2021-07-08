#include "GameViewer.h"

#define WINDOW_LABEL "Counter-Strike 2D"
#define PATH_POINTER "../../common_src/img/pointer.bmp"
#define PATH_TEXTURE "../../common_src/img/players/ct1.bmp"
#define SIZE_CROSSHAIR 25
#define BOX "BOX"
#define BACKGROUND "BG"
#define SIZE_KNIFE 35

struct Color {
    uint8_t r, g, b;
};

const struct Color NEGRO = {0xFF, 0xFF, 0xFF};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};


GameViewer::GameViewer(int window_w, int window_h, LevelInfo level): window(WINDOW_LABEL, window_w, window_h),
    renderer(&window), 
    level(level),
    cam(window_w, window_h),
    pjTexture(this->renderer, PATH_TEXTURE, NEGRO.r, NEGRO.g, NEGRO.b), 
    bullet(renderer){


    loadTexturesWeapons();
    loadMap();

    Weapon knife(*(this->weaponOnPj[PISTOL]), *(this->animWeaponOnPj[PISTOL]), {SIZE_KNIFE/2,SIZE_KNIFE});
    this->mainPlayer = new MainCharacter( level.mainPlayer, pjTexture, 
                std::move(CrossHair(SIZE_CROSSHAIR, SIZE_CROSSHAIR, std::move(SdlTexture(renderer, PATH_POINTER, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b)))),
                std::move(Stencil(this->renderer, window_w, window_h)), std::move(knife));

    for (PlayerInfo player : level.players) {
        //crear cuchillo y cargarlo al personaje
        Weapon weapon(*(this->weaponOnPj[PISTOL]), *(this->animWeaponOnPj[PISTOL]), {SIZE_KNIFE/2,SIZE_KNIFE});
        this->players.push_back(std::move(Character(player, this->pjTexture, std::move(weapon))));
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

    if (!this->textures.empty()) {
        for(auto it = this->textures.begin(); it != this->textures.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->textures.clear();
    }
}




void GameViewer::loadTexturesWeapons(){

//enum WeaponType : char {KNIFE, PISTOL, SHOTGUN, RIFLE, SNIPER, BOMB, DEFUSER};

    this->weaponOnPj[KNIFE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->animWeaponOnPj[KNIFE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/knifeslash.bmp", 0x00, 0x00, 0x00);
    
    // FALTA CARGAR EL EFECTO DE LAS ARMAS
    this->weaponOnPj[PISTOL] = new SdlTexture(this->renderer, "../../common_src/img/weapons/glock.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->animWeaponOnPj[PISTOL] = new SdlTexture(this->renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);
    
    this->weaponOnPj[RIFLE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/ak47.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->animWeaponOnPj[RIFLE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);

    this->weaponOnPj[SNIPER] = new SdlTexture(this->renderer, "../../common_src/img/weapons/awp.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->animWeaponOnPj[SNIPER] = new SdlTexture(this->renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);

    this->weaponOnPj[SHOTGUN] = new SdlTexture(this->renderer, "../../common_src/img/weapons/xm1014.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->animWeaponOnPj[SHOTGUN] = new SdlTexture(this->renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);


    this->weaponsOnFloor[PISTOL] = new SdlTexture(this->renderer, "../../common_src/img/weapons/glock_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[SNIPER] = new SdlTexture(this->renderer, "../../common_src/img/weapons/awp_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[RIFLE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/ak47_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[BOMB] = new SdlTexture(this->renderer, "../../common_src/img/weapons/bomb_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
}


void GameViewer::loadMap() {
    this->textures[BACKGROUND] = new SdlTexture(this->renderer, "../../common_src/img/bg.png");
    this->textures[BOX] = new SdlTexture(this->renderer, "../../common_src/img/green_crate.bmp");
}



// ESTO EN LA VERSION FINAL NO TIENE QUE IR
void GameViewer::renderPlayers(Coordenada cam) {
    for (auto it = this->players.begin(); it != this->players.end(); it++){
        it->render(cam.x, cam.y);
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
    this->textures[BACKGROUND]->render(0, 0, this->level.width, this->level.height);
    for (BoxInfo box : this->level.boxes){
        this->textures[BOX]->render(box.pos.x - cam.x, box.pos.y - cam.y, box.size.w, box.size.h);
    }
}

void GameViewer::renderMainPlayer(Coordenada cam){
    this->mainPlayer->render(cam);
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

    renderer.updateScreen();
}


void GameViewer::createWeapon(PlayerInfo player, ProtPlayer prot){

}


void GameViewer::update(LevelInfo level){
    this->level = level;

    WeaponType type = level.mainPlayer.weapon.type;
    Weapon weapon(*(this->weaponOnPj[type]), *(this->animWeaponOnPj[type]), level.mainPlayer.weapon.size);
    this->mainPlayer->update(level.mainPlayer, std::move(weapon));

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
            WeaponType typePj = player.weapon.type;
            Weapon weaponPj(*(this->weaponOnPj[typePj]), *(this->animWeaponOnPj[typePj]), player.weapon.size);

            it->update(player, std::move(weaponPj));
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