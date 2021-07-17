#include "presenter.h"
#include "TextureFactory.h"
#include <fstream>
#include <stdio.h>

Presenter::Presenter(MenuManager& m, int screenW, int screenH) : menuManager(m), camera({screenW, screenH}){}

void Presenter::renderTextures(){
    this->menuManager.renderTextures(this->camera.getRect());
}

void Presenter::renderWeapons(){
    this->menuManager.renderWeapons(this->camera.getRect());
}

void Presenter::renderBombSites(){
    this->menuManager.renderBombSites(this->camera.getRect());
}

void Presenter::renderSpawnSites(){
    this->menuManager.renderSpawnSites(this->camera.getRect());
}

void Presenter::renderMapFloors(int& page){
    this->menuManager.renderMapFloors(page);
}

void Presenter::renderMapWalls(int& page){
    this->menuManager.renderMapWalls(page);
}

void Presenter::renderMapWeapons(int& page){
    this->menuManager.renderMapWeapons(page);
}

void Presenter::handleBombSitesEvent(SDL_Event* event){
    this->menuManager.handleBombSitesEvent(event, this->camera.getRect());
}

void Presenter::handleSpawnSitesEvent(SDL_Event* event){
    this->menuManager.handleSpawnSitesEvent(event, this->camera.getRect());
}

void Presenter::handleFloorsTexture(SDL_Event* event, int& page){
    this->menuManager.handleSelectFloor(event, page);
}

void Presenter::handleWallsTexture(SDL_Event* event, int& page){
    this->menuManager.handleSelectWall(event, page);
}

void Presenter::handleWeaponsTexture(SDL_Event* event, int& page){
    this->menuManager.handleSelectWeapon(event, page);
}

void Presenter::centerCamera(){
    this->camera.centerCameraOnMouse(this->menuManager.getTileSize(), this->menuManager.getMapWidth(), this->menuManager.getMapHeight());
}

void Presenter::fillSize(std::vector<SDL_Rect>& vector){
    this->menuManager.fillSize(vector);
}

void Presenter::changeSizeOfSites(std::vector<float>& vector){
    this->menuManager.changeSizeOfSites(vector);
}

void Presenter::changeTexture(){
    this->menuManager.changeTexture(this->camera.getRect());
}

void Presenter::createMap(const std::string mapID){
    this->menuManager.createMap(mapID);
}

void Presenter::editMap(const std::string& mapID){
    this->menuManager.editMap(mapID);
}

void Presenter::needToSave(){
    this->menuManager.needToSave();
}

void Presenter::saveMap(){
    this->menuManager.loadToFile();
}

void Presenter::goToMenu(){
    this->menuManager.goToMenu();
}

SDL_Rect Presenter::getCameraBox(){
    return this->camera.getRect();
}

int Presenter::getMapWidth(){
    return this->menuManager.getMapWidth();
}

int Presenter::getMapHeight(){
    return this->menuManager.getMapHeight();
}

int Presenter::getTextureMapSize(){
    return this->menuManager.getTextureMapSize();
}

int Presenter::getTexturesSize(){
    return this->menuManager.getTexturesSize();
}

int Presenter::getTileSize(){
    return this->menuManager.getTileSize();
}

void Presenter::quit(){
    this->menuManager.requestQuit();
}
