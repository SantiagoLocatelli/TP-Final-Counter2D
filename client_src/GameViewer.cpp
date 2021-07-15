#include "GameViewer.h"
#include "Events/gameMath.h"
#include <cstdio>

#define WINDOW_LABEL "Counter-Strike 2D"
#define PATH_POINTER "../../common_src/img/pointer.bmp"
#define PATH_FONT_DIGITAL "../../common_src/img/digital-7.ttf"
#define PATH_FONT_AERIAL "../../common_src/img/aerial.ttf"
#define SIZE_CROSSHAIR 25
#define MARGIN 10

#define OPACITY_DAMAGE 100
#define SIZE_DAMAGE 25

#define OPACITY_MENU 150
#define SIZE_BORDER_MENU 5

#define SIZE_EXPLOSION 200

#define HUD_AMMO 0
#define HUD_HEALTH 1
#define HUD_TIME 2
#define SITE 3

#define DELAY_SOUND_BOMB 20
#define DELAY_SOUND_BOMB_QUICK 5
#define ABOUT_TO_EXPLODE 5.0

const struct Color ROJO_CLARO = {0xa7, 0x03, 0x03};
const struct Color ROJO = {0xff, 0x00, 0x00};
const struct Color HUD_COLOR = {0xAD, 0x86, 0x33};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};
const struct Color NEGRO = {0x00, 0x00, 0x00};
const struct Color WHITE = {0xff, 0xff, 0xff};

const struct Size SIZE_SMALL_GUN = {22, 32};
const struct Size SIZE_BIG_GUN = {20, 60};

const struct Size SIZE_SMALL_GUN_HUD = {20, 20};
const struct Size SIZE_BIG_GUN_HUD = {40, 25};


GameViewer::GameViewer(Size windowSize, LevelInfo level): window(WINDOW_LABEL, windowSize.w, windowSize.h),
    renderer(&window), 
    textureManager(renderer, level.tiles),
    cam(windowSize),
    level(level),
    hudText(renderer, PATH_FONT_DIGITAL, 30),
    buyMenuText(renderer, PATH_FONT_AERIAL, 10),
    bullet(renderer){

    SDL_ShowCursor(SDL_DISABLE);
    loadHudTextures();
    loadWeapons();
    loadPlayers(windowSize);
}


SkinType getPjSkin(PlayerInfo player) {
    if (player.team == COUNTER) {
        return (SkinType) Math::getRandomNumberBetween((int)CT1, (int)CT4);
    }
    return (SkinType) Math::getRandomNumberBetween((int)TT1, (int)TT4);
}

void GameViewer::loadPlayers(Size window){
    srand((unsigned)time(NULL));
    WeaponType mainWeaponType = this->level.mainPlayer.weapon.type;
    SkinType mainSkinType = getPjSkin(this->level.mainPlayer);
    this->mainPlayer = new MainCharacter( level.mainPlayer, *(this->textureManager.getSkin(mainSkinType)), 
                std::move(CrossHair(SIZE_CROSSHAIR, SIZE_CROSSHAIR, std::move(SdlTexture(renderer, PATH_POINTER, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b)))),
                std::move(Stencil(this->renderer, window)), this->weapons[mainWeaponType]);


    for (PlayerInfo player : this->level.players) {

        WeaponType typeWeapon = player.weapon.type;
        SkinType typeSkin = getPjSkin(player);
        this->players.push_back(Character(player, *(this->textureManager.getSkin(typeSkin)), this->weapons[typeWeapon]));
    }
}


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
    this->hud[HUD_AMMO] = new TextTexture(this->renderer, PATH_FONT_DIGITAL, 30);
    this->hud[HUD_AMMO]->setText(ammoText, HUD_COLOR);
    
    char healtText[100];
    sprintf(healtText, "Health: %d", (int)this->level.mainPlayer.health);
    this->hud[HUD_HEALTH] = new TextTexture(this->renderer, PATH_FONT_DIGITAL, 30);
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
        
        this->textureManager.getWeaponOnFloor(wp.type)->render(wp.pos.x - cam.x - wp.size.w/2, wp.pos.y - cam.y - wp.size.h/2, wp.size.w, wp.size.h);
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

void GameViewer::renderBorder(Coordinate pos, Size sizeRect, int borderWidth, struct Color color, int opacity){
    SDL_Rect left = {pos.x, pos.y, borderWidth, sizeRect.h};
    this->renderer.setDrawColor(color.r, color.g, color.b, opacity);
    this->renderer.fillRect(left);

    SDL_Rect right = {sizeRect.w - borderWidth + pos.x, pos.y, borderWidth, sizeRect.h};
    this->renderer.setDrawColor(color.r, color.g, color.b, opacity);
    this->renderer.fillRect(right);

    SDL_Rect top = {borderWidth + pos.x, pos.y, sizeRect.w - borderWidth*2, borderWidth};
    this->renderer.setDrawColor(color.r, color.g, color.b, opacity);
    this->renderer.fillRect(top);

    SDL_Rect bottom = {borderWidth + pos.y, sizeRect.h-borderWidth + pos.y, sizeRect.w - borderWidth*2, borderWidth};
    this->renderer.setDrawColor(color.r, color.g, color.b, opacity);
    this->renderer.fillRect(bottom);
}

void GameViewer::renderHud(){
    Size cam = this->cam.getSize();

    Size sizeAmmo =  this->hud[HUD_AMMO]->getSize();
    Coordinate dstAmmo = { cam.w - MARGIN - sizeAmmo.w, cam.h - MARGIN - sizeAmmo.h};
    this->hud[HUD_AMMO]->render(dstAmmo);

    Size sizeHealth = this->hud[HUD_HEALTH]->getSize();
    Coordinate dstHealth = {MARGIN, cam.h - MARGIN - sizeHealth.h};
    this->hud[HUD_HEALTH]->render(dstHealth);



    if (this->level.bomb.planted) {

        char timeBomb[100];
        sprintf(timeBomb, "Bomb: %d", (int)this->level.bomb.time);
        // seteo el color segun el tiempo restante
        if (this->level.bomb.time > ABOUT_TO_EXPLODE) {
            this->hudText.setText(timeBomb, HUD_COLOR);
        } else {
            this->hudText.setText(timeBomb, ROJO_CLARO);
        }
        Size sizeTime = this->hudText.getSize();
        Coordinate pos = {cam.w/2 - sizeTime.w/2, MARGIN};
        this->hudText.render(pos);
    }

    Size sizeWeapon = {40, 40};
    Coordinate dstWeapon = {cam.w, cam.h-100};
    WeaponType type = this->level.mainPlayer.weapon.type;

    if (type != KNIFE) {
        SdlTexture& weapon = *this->textureManager.getWeaponOnHud(type); 
        weapon.render(dstWeapon.x - sizeWeapon.w - MARGIN, dstWeapon.y - sizeWeapon.h, sizeWeapon.w, sizeWeapon.h);
    }

    if (this->level.mainPlayer.damaged) {
        renderBorder({0,0}, cam, SIZE_DAMAGE, ROJO, OPACITY_DAMAGE);
    }
}

void GameViewer::renderBombSites(Coordinate cam){

    auto siteA = this->level.bombSites.begin();
    
    SDL_Rect dst = {siteA->pos.x - cam.x, siteA->pos.y - cam.y, siteA->size.w, siteA->size.h};
    this->renderer.setDrawColor(ROJO.r, ROJO.g, ROJO.b, 100);
    this->renderer.fillRect(dst);

    Coordinate pos = {dst.x + dst.w/2, dst.y + dst.h/2};
    this->hudText.setText("A", ROJO_CLARO);
    this->hudText.render(pos);

    siteA++;
    if (siteA != this->level.bombSites.end()) {
            
        dst = {siteA->pos.x - cam.x, siteA->pos.y - cam.y, siteA->size.w, siteA->size.h};
        this->renderer.setDrawColor(ROJO.r, ROJO.g, ROJO.b, 100);
        this->renderer.fillRect(dst);

        pos = {dst.x + dst.w/2, dst.y + dst.h/2};
        this->hudText.setText("B", ROJO_CLARO);
        this->hudText.render(pos);
    }

}

void GameViewer::renderExplosion(Coordinate cam) {
    SdlTexture* explosion = this->textureManager.getExplosionAnim();

    Coordinate pos = this->level.bomb.pos;
    pos.x = pos.x - cam.x - SIZE_EXPLOSION/2;  
    pos.y = pos.y - cam.y - SIZE_EXPLOSION/2;  
    SDL_Rect clip;
    clip.w = explosion->getWidth()/5;
    clip.h = explosion->getHeight()/5;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            clip.x = j*clip.w; 
            clip.y = i*clip.h;
            explosion->render(pos.x, pos.y, SIZE_EXPLOSION, SIZE_EXPLOSION, &clip);
        }
    }
}

void GameViewer::renderBomb(Coordinate cam){

    if (this->level.bomb.planted) {
        Coordinate pos = {this->level.bomb.pos.x - cam.x, this->level.bomb.pos.y - cam.y};
        this->textureManager.getWeaponOnPj(BOMB)->render(pos.x, pos.y, SIZE_SMALL_GUN.w, SIZE_SMALL_GUN.h);
        
        this->delaySound++;

        // seteo el delay segun el tiempo restante
        if (this->delaySound == DELAY_SOUND_BOMB && this->level.bomb.time > ABOUT_TO_EXPLODE) {
            this->sounds.playWeaponSound(BOMB_PIP); 
            this->delaySound = 0;
        } else if (this->delaySound >= DELAY_SOUND_BOMB_QUICK && this->level.bomb.time < ABOUT_TO_EXPLODE){
            this->sounds.playWeaponSound(BOMB_PIP); 
            this->delaySound = 0;
        }

        if (this->level.bomb.time < 0.1) {
            this->renderExplosion(cam);
            this->sounds.playWeaponSound(BOMD_EXPLODE);
        }
    }
}


void GameViewer::renderWeaponOnMenu(WeaponType weapon, SDL_Rect box, Size unit, const char* text){
    Size cam = this->cam.getSize();

    this->buyMenuText.setText(text, WHITE);
    Size textSize = this->buyMenuText.getSize();
    Coordinate textPos = {box.x + unit.w/2 , box.y + unit.h/2 - textSize.h/2};
    this->buyMenuText.render(textPos);

    SdlTexture* weaponOnHud = this->textureManager.getWeaponOnHud(weapon);
    Coordinate weaponPos = {box.x + unit.w , box.y + unit.h - textSize.h/2};
    Size weaponSize = unit;
    weaponOnHud->render(weaponPos.x, weaponPos.y, weaponSize.w, weaponSize.h);

    this->renderer.setDrawColor(WHITE.r, WHITE.g, WHITE.b, 0xff);
    this->renderer.drawLine(cam.w/2, weaponPos.y, cam.w/2, weaponPos.y + unit.h);

    SdlTexture* weaponOnPj = this->textureManager.getWeaponOnPj(weapon);
    int heightTexture = weaponOnPj->getHeight();
    int widthTexure = weaponOnPj->getWidth();
    weaponOnPj->render(cam.w/2 + unit.w + weaponSize.w/2, weaponPos.y + widthTexure/2, 10, 30, NULL, 90.0);


    SdlTexture* skin = this->textureManager.getSkin(CT1);
    if (this->level.mainPlayer.team == TERROR) {
        skin = this->textureManager.getSkin(TT1);
    }
    SDL_Rect clip = {0, 64, 32, 32};
    skin->render(cam.w/2 + unit.w, weaponPos.y, weaponSize.w, weaponSize.h, &clip, 90.0);
}

void GameViewer::renderBuyMenu(){
    Size cam = this->cam.getSize();
    if (buyMenuOpen) {

        // rectangulo principal con su borde
        SDL_Rect menu = {cam.w/6, cam.h/6, 2*cam.w/3 - SIZE_BORDER_MENU, 2*cam.h/3 - SIZE_BORDER_MENU};
        Size border = {menu.w + SIZE_BORDER_MENU, menu.h + SIZE_BORDER_MENU};
        Coordinate pos = {menu.x, menu.y};
        this->renderer.setDrawColor(HUD_COLOR.r, HUD_COLOR.g, HUD_COLOR.b, OPACITY_MENU);
        this->renderer.fillRect(menu);
        this->renderBorder(pos, border, SIZE_BORDER_MENU, NEGRO, 255);

        SDL_Rect box = {menu.x + cam.w/12, menu.y + cam.h/24, cam.w/2, cam.h/6};
        this->renderer.setDrawColor(NEGRO.r, NEGRO.g, NEGRO.b, 200);
        this->renderer.fillRect(box);
        
        char text[100];
        sprintf(text, "Press 8 to buy Awp:");
        renderWeaponOnMenu(SNIPER, box, {cam.w/12, cam.h/12}, text);

        box.y = box.y + cam.h/6 + cam.h/24;
        this->renderer.setDrawColor(NEGRO.r, NEGRO.g, NEGRO.b, 200);
        this->renderer.fillRect(box);
        sprintf(text, "Press 9 to buy Shotgun:");
        renderWeaponOnMenu(SHOTGUN, box, {cam.w/12, cam.h/12}, text);
        
        box.y = box.y + cam.h/6 + cam.h/24;
        this->renderer.setDrawColor(NEGRO.r, NEGRO.g, NEGRO.b, 200);
        this->renderer.fillRect(box);
        sprintf(text, "Press 0 to buy Rifle:");
        renderWeaponOnMenu(RIFLE, box, {cam.w/12, cam.h/12}, text);
    }
}

void GameViewer::render(){
    std::unique_lock<std::mutex> lock(m);
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    Coordinate cam = {this->cam.getPosX(), this->cam.getPosY()};
    
    renderMap(cam);
    renderBombSites(cam);
    renderBomb(cam);
    renderShots(cam);
    renderPlayers(cam);
    renderWeapons(cam);
    renderMainPlayer(cam);
    renderBuyMenu();
    renderHud();

    renderer.updateScreen();
}


void GameViewer::updateHud(LevelInfo level){
    if (this->level.mainPlayer.health != level.mainPlayer.health) {
        char healtText[100];
        sprintf(healtText, "Health: %d", (int)this->level.mainPlayer.health);
        this->hud[HUD_HEALTH]->setText(healtText, HUD_COLOR);
    } 


    if (this->level.mainPlayer.ammo != level.mainPlayer.ammo) {
        char ammoText[100];
        sprintf(ammoText, "Ammo: %d", (int)this->level.mainPlayer.ammo);
        this->hud[HUD_AMMO]->setText(ammoText, HUD_COLOR);
    } 
}


void GameViewer::update(LevelInfo level){
    std::unique_lock<std::mutex> lock(m);
    updateHud(level);

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
        WeaponType type = player.weapon.type;
        it->update(player, this->weapons[type]);
        it++;
    }

    this->cam.centerCamera(level.mainPlayer.pos);
    this->cam.keepInBounds(level.size.w, level.size.h);
    this->level = level;
}

void GameViewer::setCrossHair(Coordinate pos){this->mainPlayer->setCrossHair(pos);}

Coordinate GameViewer::mainPlayerRelativePos(){
    std::unique_lock<std::mutex> lock(m);
    return {this->mainPlayer->getPosX() - this->cam.getPosX(),
            this->mainPlayer->getPosY() - this->cam.getPosY()};
}



void GameViewer::toggleBuyMenu(){
    std::unique_lock<std::mutex> lock(m);
    if (buyMenuOpen) buyMenuOpen = false;
    else buyMenuOpen = true;
}