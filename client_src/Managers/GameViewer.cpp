#include "GameViewer.h"
#include "../../common_src/Colors.h"
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <memory>

#define WINDOW_LABEL "Counter-Strike 2D"
#define PATH_POINTER "../../common_src/img/pointer.bmp"
#define PATH_FONT_DIGITAL "../../common_src/img/digital-7.ttf"
#define PATH_FONT_AERIAL "../../common_src/img/aerial.ttf"
#define SIZE_CROSSHAIR 25
#define MARGIN 10

#define OPACITY_DAMAGE 100
#define SIZE_DAMAGE 25

#define OPACITY_TEXT_HUD 200
#define OPACITY_MENU 150
#define SIZE_BORDER_MENU 5

#define SIZE_EXPLOSION 200

#define DELAY_SOUND_BOMB 20
#define DELAY_SOUND_BOMB_QUICK 5
#define ABOUT_TO_EXPLODE 5.0


#define BUY_RIFLE 0
#define BUY_SNIPER 8
#define BUY_SHOTGUN 9

const struct Size SIZE_SMALL_GUN = {22, 32};
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
    loadWeapons();
    loadPlayers(windowSize);
    loadHudTextures();
}

SkinType GameViewer::getPjSkin(PlayerInfo player) {
    if (player.team == COUNTER) {
        return this->level.counterskin;
    }
    return this->level.terrorSkin;
}

void GameViewer::loadPlayers(Size window){
    srand((unsigned)time(NULL));
    WeaponType mainWeaponType = this->level.mainPlayer.weapon.type;
    SkinType mainSkinType = getPjSkin(this->level.mainPlayer);


    this->mainPlayer = std::unique_ptr<MainCharacter> (new MainCharacter( level.mainPlayer, *(this->textureManager.getSkin(mainSkinType)), 
                std::move(CrossHair(SIZE_CROSSHAIR, SIZE_CROSSHAIR, std::move(SdlTexture(renderer, PATH_POINTER, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b)))),
                std::move(Stencil(this->renderer, window)), this->weapons[mainWeaponType]));


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
    for (auto it = this->weapons.begin(); it != this->weapons.end(); it++) {
        Weapon* aux = it->second;
        it++;
        delete aux;
    }
}

void GameViewer::loadHudTextures(){
    char ammoText[100];
    sprintf(ammoText, "Ammo: %d", this->level.mainPlayer.ammo);
    this->hud[AMMO] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT_DIGITAL, 30));
    this->hud[AMMO]->setText(ammoText, HUD_TEXT_COLOR);
    
    char healtText[100];
    sprintf(healtText, "Health: %d", (int)this->level.mainPlayer.health);
    this->hud[HEALTH] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT_DIGITAL, 30));
    this->hud[HEALTH]->setText(healtText, HUD_TEXT_COLOR);

    char moneyText[100];
    sprintf(moneyText, "$: %d", (int)this->level.mainPlayer.money);
    this->hud[MONEY] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT_DIGITAL, 30));
    this->hud[MONEY]->setText(moneyText, HUD_TEXT_COLOR);

    this->hud[TIME] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT_DIGITAL, 30));

    this->hud[TITLE] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT_AERIAL, this->cam.getWidth()/40));
    this->hud[SUBTITLE] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT_AERIAL, 20));
    this->hud[TEXT] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT_AERIAL, this->cam.getWidth()/65));
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
        TextureInfo tileInfo = this->textureManager.getTileInfo(tile);

        if (tileInfo.clip.x == -1) {
            this->textureManager.getTiles(tile)->render(pos.x-cam.x, pos.y-cam.y, size.w, size.h);
        } else {
            this->textureManager.getTiles(tile)->render(pos.x-cam.x, pos.y-cam.y, size.w, size.h, &tileInfo.clip);
        }
    }
}

void GameViewer::renderMainPlayer(Coordinate cam){
    this->mainPlayer->render(cam);
    for (PlayerEffect effect : this->level.mainPlayer.sounds) {
        this->sounds.playPlayerSound(effect);
    }
    if (this->level.mainPlayer.shooting) {
        this->sounds.playWeaponSound(this->level.mainPlayer.weapon.sound);
    }
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

    SDL_Rect bottom = {borderWidth + pos.x, sizeRect.h-borderWidth + pos.y, sizeRect.w - borderWidth*2, borderWidth};
    this->renderer.setDrawColor(color.r, color.g, color.b, opacity);
    this->renderer.fillRect(bottom);
}

void GameViewer::renderHud(){
    Size cam = this->cam.getSize();

    Size sizeAmmo =  this->hud[AMMO]->getSize();
    Coordinate dstAmmo = { cam.w - MARGIN - sizeAmmo.w, cam.h - MARGIN - sizeAmmo.h};
    this->hud[AMMO]->setOpacity(OPACITY_TEXT_HUD);
    this->hud[AMMO]->render(dstAmmo);

    Size sizeHealth = this->hud[HEALTH]->getSize();
    Coordinate dstHealth = {MARGIN, cam.h - MARGIN - sizeHealth.h};
    this->hud[HEALTH]->setOpacity(OPACITY_TEXT_HUD);
    this->hud[HEALTH]->render(dstHealth);

    Coordinate dstMoney = {MARGIN, MARGIN};
    this->hud[MONEY]->setOpacity(OPACITY_TEXT_HUD);
    this->hud[MONEY]->render(dstMoney);

    if (this->level.bomb.planted) {

        char timeBomb[100];
        sprintf(timeBomb, "Bomb: %d", (int)this->level.bomb.time);
        // seteo el color segun el tiempo restante
        if (this->level.bomb.time > ABOUT_TO_EXPLODE) {
            this->hud[TIME]->setText(timeBomb, HUD_TEXT_COLOR);
        } else {
            this->hud[TIME]->setText(timeBomb, ROJO_CLARO);
        }
        Size sizeTime = this->hud[TIME]->getSize();
        Coordinate pos = {cam.w/2 - sizeTime.w/2, MARGIN};
        this->hud[TIME]->render(pos);
    } else {
        char time[100];
        sprintf(time, "Time: %d", (int)this->level.timeRemaining);
        this->hud[TIME]->setText(time, HUD_TEXT_COLOR);
        Size sizeTime = this->hud[TIME]->getSize();
        Coordinate dstTime = {cam.w/2 - sizeTime.w/2, cam.h - MARGIN - sizeTime.h};
        this->hud[TIME]->render(dstTime);
    }


    Size size = {40, 40};

    auto it = this->level.mainPlayer.weapons.begin();
    auto end = this->level.mainPlayer.weapons.end();
    int i = 1;
    for (; it != end; it++) {
        if (*it != KNIFE && *it != NO_WEAPON) {
            SdlTexture* weapon = this->textureManager.getWeaponOnHud(*it);

            weapon->setBlendMode(SDL_BLENDMODE_BLEND);
            weapon->setAlpha(255);
            if (*it != this->level.mainPlayer.weapons[this->level.mainPlayer.currentSlot]) {
                weapon->setAlpha(100);
            }
            Coordinate dst = {cam.w - size.w - MARGIN, cam.h - 40 - 60*i};
            weapon->render(dst.x, dst.y, size.w, size.h);
            i++;
        }
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
    this->hud[TITLE]->setText("A", ROJO_CLARO);
    this->hud[TITLE]->render(pos);

    siteA++;
    if (siteA != this->level.bombSites.end()) {
            
        dst = {siteA->pos.x - cam.x, siteA->pos.y - cam.y, siteA->size.w, siteA->size.h};
        this->renderer.setDrawColor(ROJO.r, ROJO.g, ROJO.b, 100);
        this->renderer.fillRect(dst);

        pos = {dst.x + dst.w/2, dst.y + dst.h/2};
        this->hud[TITLE]->setText("B", ROJO_CLARO);
        this->hud[TITLE]->render(pos);
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

    this->renderer.setDrawColor(BLACK.r, BLACK.g, BLACK.b, 200);
    this->renderer.fillRect(box);

    this->hud[TEXT]->setText(text, WHITE);
    Size textSize = this->hud[TEXT]->getSize();
    Coordinate textPos = {box.x + unit.w/2 , box.y + unit.h/2 - textSize.h/2};
    this->hud[TEXT]->render(textPos);

    SdlTexture* weaponOnHud = this->textureManager.getWeaponOnHud(weapon);
    Coordinate weaponPos = {box.x + unit.w , box.y + unit.h - textSize.h/2};
    Size weaponSize = unit;
    weaponOnHud->render(weaponPos.x, weaponPos.y, weaponSize.w, weaponSize.h/2);

    this->renderer.setDrawColor(WHITE.r, WHITE.g, WHITE.b, 0xff);
    this->renderer.drawLine(cam.w/2, weaponPos.y, cam.w/2, weaponPos.y + unit.h);

    SdlTexture* weaponOnPj = this->textureManager.getWeaponOnPj(weapon);
    weaponOnPj->render(cam.w/2 + unit.w + weaponSize.w/2, weaponPos.y, 15, unit.h, NULL, 90.0);


    SdlTexture* skin = this->textureManager.getSkin(CT1);
    if (this->level.mainPlayer.team == TERROR) {
        skin = this->textureManager.getSkin(TT1);
    }
    SDL_Rect clip = {0, 64, 32, 32};
    skin->render(cam.w/2 + unit.w, weaponPos.y, weaponSize.w, weaponSize.h, &clip, 90.0);
}

void GameViewer::showRoundState(){

    if (this->level.state.roundState == END && (this->level.state.gameState == PLAYING)) {
        Size cam = this->cam.getSize();
        SDL_Rect menu = {cam.w/12, cam.h/6, 5*cam.w/6 - SIZE_BORDER_MENU, cam.h/6 - SIZE_BORDER_MENU};
        Size border = {menu.w + SIZE_BORDER_MENU, menu.h + SIZE_BORDER_MENU};
        Coordinate pos = {menu.x, menu.y};

 
        // enum RoundResult : char {T_DEAD, BOMB_DEFUSED, TIME_ENDED, /*CT WIN*/
        //                CT_DEAD, BOMB_EXPLODED}; /*T WIN*/
        char team[100];
        char text[100];
        if (this->level.state.endResult == T_DEAD) {
            sprintf(team, "Counter Terrorist Win!");
            sprintf(text, "Ace!");
        } else if (this->level.state.endResult == BOMB_DEFUSED) {
            sprintf(team, "Counter Terrorist Win!");
            sprintf(text, "The Bomb has been defused");
        } else if (this->level.state.endResult == TIME_ENDED) {
            sprintf(team, "Counter Terrorist Win!");
            sprintf(text, "No Time");
        } else if (this->level.state.endResult == CT_DEAD) {
            sprintf(team, "Terrorist Win!");
            sprintf(text, "Ace!");
        } else {
            sprintf(team, "Terrorist Win!");
            sprintf(text, "The Bomb exploded");
        }
        this->hud[TITLE]->setText(team, WHITE);
        Size teamsize = this->hud[TITLE]->getSize();
        Coordinate teamPos = {cam.w/2 - teamsize.w/2, menu.y + SIZE_BORDER_MENU + MARGIN};

        SDL_Rect title = {menu.x + SIZE_BORDER_MENU, menu.y + SIZE_BORDER_MENU, menu.w, teamsize.h + MARGIN};
        this->renderer.setDrawColor(HUD_MENU_COLOR.r, HUD_MENU_COLOR.g, HUD_MENU_COLOR.b, OPACITY_MENU + 50);
        this->renderer.fillRect(title);
        this->hud[TITLE]->render(teamPos);
        
        
        this->hud[SUBTITLE]->setText(text, WHITE);
        Size textSize = this->hud[SUBTITLE]->getSize();
        Coordinate textPos = {cam.w/2 - textSize.w/2, teamPos.y + teamsize.h + MARGIN};

        SDL_Rect description = {title.x, title.y + title.h, menu.w, menu.h - title.h};
        this->renderer.setDrawColor(HUD_MENU_COLOR.r, HUD_MENU_COLOR.g, HUD_MENU_COLOR.b, OPACITY_MENU);
        this->renderer.fillRect(description);
        this->hud[SUBTITLE]->render(textPos);

        this->renderBorder(pos, border, SIZE_BORDER_MENU, BLACK, 255);
    }
}

void GameViewer::renderBuyMenu(){
    Size cam = this->cam.getSize();
    if (this->level.state.roundState == BUY) {

        // rectangulo principal con su borde
        SDL_Rect menu = {cam.w/6, cam.h/6, 2*cam.w/3 - SIZE_BORDER_MENU, 2*cam.h/3 - SIZE_BORDER_MENU};
        Size border = {menu.w + SIZE_BORDER_MENU, menu.h + SIZE_BORDER_MENU};
        Coordinate pos = {menu.x, menu.y};
        this->renderer.setDrawColor(HUD_MENU_COLOR.r, HUD_MENU_COLOR.g, HUD_MENU_COLOR.b, OPACITY_MENU);
        this->renderer.fillRect(menu);
        this->renderBorder(pos, border, SIZE_BORDER_MENU, BLACK, 255);

        SDL_Rect box = {menu.x + cam.w/12, menu.y + cam.h/24, cam.w/2, cam.h/6};
        char text[100];
        sprintf(text, "Press %d to buy Awp: $ %d", BUY_SNIPER, this->level.weaponPrices[SNIPER]);
        renderWeaponOnMenu(SNIPER, box, {cam.w/12, cam.h/12}, text);
        box.y = box.y + cam.h/6 + cam.h/24;

        sprintf(text, "Press %d to buy Shotgun: $ %d", BUY_SHOTGUN, this->level.weaponPrices[SHOTGUN]);
        renderWeaponOnMenu(SHOTGUN, box, {cam.w/12, cam.h/12}, text);
        
        box.y = box.y + cam.h/6 + cam.h/24;
        sprintf(text, "Press %d to buy Rifle: $ %d", BUY_RIFLE, this->level.weaponPrices[RIFLE]);
        renderWeaponOnMenu(RIFLE, box, {cam.w/12, cam.h/12}, text);
    }
}

void GameViewer::showGameState() {
    //enum GameState{PLAYING, T_WON, CT_WON, TIE};
    if (this->level.state.gameState != PLAYING) {
        Size cam = this->cam.getSize();
        char title[100];
        if (this->level.state.gameState == T_WON) {
            sprintf(title, "Terrorist team win the game");
        } else if (this->level.state.gameState == CT_WON) {
            sprintf(title, "Counter Terrorist team win the game");
        } else {
            sprintf(title, "The game ended in a draw");
        }
        

        SDL_Rect menu = {cam.w/12 - SIZE_BORDER_MENU, cam.h/6 - SIZE_BORDER_MENU, 5*cam.w/6 - SIZE_BORDER_MENU*2, 2*cam.h/6 - SIZE_BORDER_MENU*2};
        
        Size border = {menu.w + SIZE_BORDER_MENU, menu.h + SIZE_BORDER_MENU};
        Coordinate pos = {menu.x, menu.y};
        SDL_Rect titleRect = {menu.x, menu.y, menu.w, menu.h/2};

        this->renderer.setDrawColor(HUD_MENU_COLOR.r, HUD_MENU_COLOR.g, HUD_MENU_COLOR.b, OPACITY_MENU + 50);
        this->renderer.fillRect(titleRect);
        this->hud[TITLE]->setText(title, WHITE);
        Size sizeTitle = this->hud[TITLE]->getSize();
        Coordinate posTitle = {cam.w/2 - sizeTitle.w/2, menu.y - sizeTitle.h/2 + titleRect.h/2};
        this->hud[TITLE]->render(posTitle);
        
        SDL_Rect textRect = {menu.x, menu.y + titleRect.h, menu.w, menu.h/2};
        this->renderer.setDrawColor(HUD_MENU_COLOR.r, HUD_MENU_COLOR.g, HUD_MENU_COLOR.b, OPACITY_MENU);
        this->renderer.fillRect(textRect);
        char text[100];
        sprintf(text, "Press Enter to exit...");
        this->hud[TEXT]->setText(text, WHITE);
        Size textSize = this->hud[TEXT]->getSize();
        Coordinate textPos = {cam.w/2 - textSize.w/2, textRect.y - textSize.h/2 + textRect.h/2};
        this->hud[TEXT]->render(textPos);
        this->renderBorder(pos, border, SIZE_BORDER_MENU, BLACK, 255);
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
    showRoundState();

    renderer.updateScreen();
}

void GameViewer::renderGameResult() {
    std::unique_lock<std::mutex> lock(m);
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    Coordinate cam = {this->cam.getPosX(), this->cam.getPosY()};

    renderMap(cam);
    renderBombSites(cam);
    renderWeapons(cam);
    renderHud();
    showGameState();

    renderer.updateScreen();
}

void GameViewer::updateHud(LevelInfo level){
    if (this->level.mainPlayer.health != level.mainPlayer.health) {
        char healtText[100];
        sprintf(healtText, "Health: %d", (int)level.mainPlayer.health);
        this->hud[HEALTH]->setText(healtText, HUD_TEXT_COLOR);
    } 

    if (this->level.mainPlayer.ammo != level.mainPlayer.ammo) {
        
        char ammoText[100];
        sprintf(ammoText, "Ammo: %d", (int)level.mainPlayer.ammo);
        this->hud[AMMO]->setText(ammoText, HUD_TEXT_COLOR);
    } 

    if (this->level.mainPlayer.money != level.mainPlayer.money) {
        char moneyText[100];
        sprintf(moneyText, "$: %d", (int)level.mainPlayer.money);
        this->hud[MONEY]->setText(moneyText, HUD_TEXT_COLOR);
    }
}

void GameViewer::update(LevelInfo newLevel){
    std::unique_lock<std::mutex> lock(m);

    updateHud(newLevel);
    WeaponType mainType = newLevel.mainPlayer.weapon.type;
    this->mainPlayer->update(newLevel.mainPlayer, this->weapons[mainType]);

    auto it = this->players.begin();
    for (PlayerInfo player : this->level.players) {
        WeaponType type = player.weapon.type;
        it->update(player, this->weapons[type]);
        it++;
    }

    this->cam.centerCamera(newLevel.mainPlayer.pos);
    this->cam.keepInBounds(this->level.size.w, this->level.size.h);
    this->level = newLevel;
}

void GameViewer::setCrossHair(Coordinate pos){this->mainPlayer->setCrossHair(pos);}

Coordinate GameViewer::mainPlayerRelativePos(){
    std::unique_lock<std::mutex> lock(m);
    return {this->mainPlayer->getPosX() - this->cam.getPosX(),
            this->mainPlayer->getPosY() - this->cam.getPosY()};
}
