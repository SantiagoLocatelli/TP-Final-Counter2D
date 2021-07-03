#include "presenter.h"
#include "TextureFactory.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
const int TILE_WIDTH = 80;
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

Presenter::Presenter(const std::string path, SdlRenderer& renderer, int screenW, int screenH) : camera(screenW, screenH){
    this->mapID = path;
    TextureFactory factory;
    factory.unmarshalBombSites(path.c_str(), this->bombSites, renderer);
    factory.unmarshalSpawnSites(path.c_str(), this->spawnSites, renderer);
}

void Presenter::renderBombSites(){
    std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->bombSites.begin();
    while (iterator != this->bombSites.end()){
        iterator->second->setBlendMode(SDL_BLENDMODE_BLEND);
        iterator->second->setAlpha(100);
        iterator->second->render(this->camera.getRect());
        ++iterator;
    }
}

void Presenter::renderSpawnSites(){
    std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->spawnSites.begin();
    while (iterator != this->spawnSites.end()){
        iterator->second->setBlendMode(SDL_BLENDMODE_BLEND);
        iterator->second->setAlpha(100);
        iterator->second->render(this->camera.getRect());
        ++iterator;
    }
}

void Presenter::handleBombSitesEvent(SDL_Event* event){
    std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->bombSites.begin();
    while (iterator != this->bombSites.end()){
        iterator->second->handleEvent(event, this->camera.getRect());
        ++iterator;
    }
}
void Presenter::handleSpawnSitesEvent(SDL_Event* event){
    std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->spawnSites.begin();
    while (iterator != this->spawnSites.end()){
        iterator->second->handleEvent(event, this->camera.getRect());
        ++iterator;
    }
}

void Presenter::centerCamera(){
    this->camera.centerCameraOnMouse(TILE_WIDTH, LEVEL_WIDTH, LEVEL_HEIGHT);
}


void Presenter::loadToFile(std::vector<std::unique_ptr<SdlTexture>>& textures){
    //texture in map
    std::vector<int> textureTypes;
    
    // get the position and dimension from the textures
    SDL_Rect bombSiteA = this->bombSites["A"]->getBox();
    SDL_Rect bombSiteB = this->bombSites["B"]->getBox();
    SDL_Rect spawnSiteT = this->spawnSites["T"]->getBox();
    SDL_Rect spawnSiteCT = this->spawnSites["CT"]->getBox();

    // position of bombs
    std::vector<int> positionA = {bombSiteA.x, bombSiteA.y};
    std::vector<int> positionB = {bombSiteB.x, bombSiteB.y};
    std::vector<int> sizeA = {bombSiteA.w, bombSiteA.h};
    std::vector<int> sizeB = {bombSiteB.w, bombSiteB.h};

    // position of spawns
    std::vector<int> positionT = {spawnSiteT.x, spawnSiteT.y};
    std::vector<int> positionCT = {spawnSiteCT.x, spawnSiteCT.y};
    std::vector<int> sizeT = {spawnSiteT.w, spawnSiteT.h};
    std::vector<int> sizeCT = {spawnSiteCT.w, spawnSiteCT.h};
    
    
    for (auto &texture : textures){
        textureTypes.push_back(texture->getType());
    }

    //creation of yaml file
    YAML::Emitter out;
    out << YAML::BeginMap;
    
        out << YAML::Key << "map" << YAML::Value << YAML::Flow << textureTypes;
        
        out << YAML::Key << "bombSite" << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "A" << YAML::Value << YAML::BeginMap;

                out << YAML::Key << "position" << YAML::Value << YAML::Flow << positionA;
                out << YAML::Key << "size" << YAML::Value << YAML::Flow << sizeA;

            out << YAML::EndMap;
            out << YAML::Key << "B" << YAML::Value << YAML::BeginMap;

                out << YAML::Key << "position" << YAML::Value << YAML::Flow << positionB;
                out << YAML::Key << "size" << YAML::Value << YAML::Flow << sizeB;

            out << YAML::EndMap;
        out << YAML::EndMap;

        out << YAML::Key << "spawnSite" << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "T" << YAML::Value << YAML::BeginMap;

                out << YAML::Key << "position" << YAML::Value << YAML::Flow << positionT;
                out << YAML::Key << "size" << YAML::Value << YAML::Flow << sizeT;

            out << YAML::EndMap;
            out << YAML::Key << "CT" << YAML::Value << YAML::BeginMap;

                out << YAML::Key << "position" << YAML::Value << YAML::Flow << positionCT;
                out << YAML::Key << "size" << YAML::Value << YAML::Flow << sizeCT;

            out << YAML::EndMap;
        out << YAML::EndMap;
    
    out << YAML::EndMap;

    //load into file
    std::ofstream fout(this->mapID.c_str()); 
    fout << out.c_str();
}

void Presenter::fillSize(std::vector<SDL_Rect>& vector){
    vector = {bombSites["A"]->getBox(), bombSites["B"]->getBox(), spawnSites["T"]->getBox(),
     spawnSites["CT"]->getBox()};
}

SDL_Rect Presenter::getCameraBox(){
    return this->camera.getRect();
}
