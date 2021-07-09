#include "presenter.h"
#include "TextureFactory.h"
#include <fstream>
#include <stdio.h>

Presenter::Presenter(MenueManager& m, int screenW, int screenH) : menueManager(m), camera(screenW, screenH){}

void Presenter::renderTextures(){
    this->menueManager.renderTextures(this->camera.getRect());
}

void Presenter::renderBombSites(){
    this->menueManager.renderBombSites(this->camera.getRect());
}

void Presenter::renderSpawnSites(){
    this->menueManager.renderSpawnSites(this->camera.getRect());
}

void Presenter::handleBombSitesEvent(SDL_Event* event){
    this->menueManager.handleBombSitesEvent(event, this->camera.getRect());
}
void Presenter::handleSpawnSitesEvent(SDL_Event* event){
    this->menueManager.handleSpawnSitesEvent(event, this->camera.getRect());
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

void Presenter::changeTexture(const int& type){
    this->menueManager.changeTexture(type, this->camera.getRect());
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

std::string Presenter::getTypeName(const int& type){
    return this->menueManager.getTypeName(type);
}

int Presenter::getTileSize(){
    return this->menueManager.getTileSize();
}
