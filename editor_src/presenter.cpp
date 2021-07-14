#include "presenter.h"
#include "TextureFactory.h"
#include <fstream>
#include <stdio.h>

Presenter::Presenter(MenueManager& m, int screenW, int screenH) : menueManager(m), camera({screenW, screenH}){}

void Presenter::renderTextures(){
    this->menueManager.renderTextures(this->camera.getRect());
}

void Presenter::renderWeapons(){
    this->menueManager.renderWeapons(this->camera.getRect());
}

void Presenter::renderBombSites(){
    this->menueManager.renderBombSites(this->camera.getRect());
}

void Presenter::renderSpawnSites(){
    this->menueManager.renderSpawnSites(this->camera.getRect());
}

void Presenter::renderMapFloors(int& page){
    this->menueManager.renderMapFloors(page);
}

void Presenter::renderMapWalls(int& page){
    this->menueManager.renderMapWalls(page);
}

void Presenter::renderMapWeapons(int& page){
    this->menueManager.renderMapWeapons(page);
}

void Presenter::handleBombSitesEvent(SDL_Event* event){
    this->menueManager.handleBombSitesEvent(event, this->camera.getRect());
}

void Presenter::handleSpawnSitesEvent(SDL_Event* event){
    this->menueManager.handleSpawnSitesEvent(event, this->camera.getRect());
}

void Presenter::handleFloorsTexture(SDL_Event* event, int& page){
    this->menueManager.handleSelectFloor(event, page);
}

void Presenter::handleWallsTexture(SDL_Event* event, int& page){
    this->menueManager.handleSelectWall(event, page);
}

void Presenter::handleWeaponsTexture(SDL_Event* event, int& page){
    this->menueManager.handleSelectWeapon(event, page);
}

void Presenter::centerCamera(){
    this->camera.centerCameraOnMouse(this->menueManager.getTileSize(), this->menueManager.getMapWidth(), this->menueManager.getMapHeight());
}

void Presenter::fillSize(std::vector<SDL_Rect>& vector){
    this->menueManager.fillSize(vector);
}

void Presenter::changeSizeOfSites(std::vector<float>& vector){
    this->menueManager.changeSizeOfSites(vector);
}

void Presenter::changeTexture(){
    this->menueManager.changeTexture(this->camera.getRect());
}

void Presenter::createMap(const std::string mapID){
    this->menueManager.createMap(mapID);
}

void Presenter::editMap(const std::string& mapID){
    this->menueManager.editMap(mapID);
}

void Presenter::needToSave(){
    this->menueManager.needToSave();
}

void Presenter::saveMap(){
    this->menueManager.loadToFile();
}

void Presenter::goToMenue(){
    this->menueManager.goToMenue();
}

SDL_Rect Presenter::getCameraBox(){
    return this->camera.getRect();
}

int Presenter::getMapWidth(){
    return this->menueManager.getMapWidth();
}

int Presenter::getMapHeight(){
    return this->menueManager.getMapHeight();
}

int Presenter::getTextureMapSize(){
    return this->menueManager.getTextureMapSize();
}

int Presenter::getTexturesSize(){
    return this->menueManager.getTexturesSize();
}

int Presenter::getTileSize(){
    return this->menueManager.getTileSize();
}

