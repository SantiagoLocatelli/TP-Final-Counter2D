#include "MenueManager.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <utility>
#include <memory>
#define TEXTURE_PATH "../../common_src/maps/textures.yaml"
#define TILE_SIZE 80
#define LEVEL_WIDTH 1280

MenueManager::MenueManager(SdlRenderer& r, const std::string path, int screenWidth, int screenHeight) : renderer(r){
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    this->mapID = path;
    TextureFactory factory;
    factory.unmarshalTextures(TEXTURE_PATH, this->textureMap);
    factory.unmarshalMap(path.c_str(), this->textureMap, this->textures, this->mapSize, r);
    factory.unmarshalBombSites(path.c_str(), this->bombSites, r);
    factory.unmarshalSpawnSites(path.c_str(), this->spawnSites, r);
}

void MenueManager::loadToFile(){
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
    
    
    for (auto &texture : this->textures){
        textureTypes.push_back(texture->getType());
    }

    //creation of yaml file
    YAML::Emitter out;
    out << YAML::BeginMap;

        out << YAML::Key << "mapSize" << YAML::Value << YAML::Flow << this->mapSize;
    
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

void MenueManager::renderTextures(const SDL_Rect& camera){
    int x = 0, y = 0;
    for (auto &texture : this->textures){
        texture->render(x - camera.x, y - camera.y, TILE_SIZE, TILE_SIZE);
        
        //Move to next tile spot
        x += TILE_SIZE;

        //If we've gone too far
        if (x >= this->mapSize[0]){
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_SIZE;
        }
    }
}


void MenueManager::renderBombSites(const SDL_Rect& camera){
    std::map<std::string, std::shared_ptr<Draggable>>::iterator iterator = this->bombSites.begin();
    while (iterator != this->bombSites.end()){
        iterator->second->setBlendMode(SDL_BLENDMODE_BLEND);
        iterator->second->setAlpha(100);
        iterator->second->render(camera);
        ++iterator;
    }
}

void MenueManager::renderSpawnSites(const SDL_Rect& camera){
    std::map<std::string, std::shared_ptr<Draggable>>::iterator iterator = this->spawnSites.begin();
    while (iterator != this->spawnSites.end()){
        iterator->second->setBlendMode(SDL_BLENDMODE_BLEND);
        iterator->second->setAlpha(100);
        iterator->second->render(camera);
        ++iterator;
    }
}

void MenueManager::handleBombSitesEvent(SDL_Event* event, const SDL_Rect& camera){
    std::map<std::string, std::shared_ptr<Draggable>>::iterator iterator = this->bombSites.begin();
    while (iterator != this->bombSites.end()){
        iterator->second->handleEvent(event, camera);
        ++iterator;
    }
}
void MenueManager::handleSpawnSitesEvent(SDL_Event* event, const SDL_Rect& camera){
    std::map<std::string, std::shared_ptr<Draggable>>::iterator iterator = this->spawnSites.begin();
    while (iterator != this->spawnSites.end()){
        iterator->second->handleEvent(event, camera);
        ++iterator;
    }
}

//numeros pares con el 0 son los width numeros impares son los height
void MenueManager::changeSizeOfSites(std::vector<int>& vector){ 
    int insertPosition = 0;
    int newColumns = vector[0]/TILE_SIZE - this->mapSize[0]/TILE_SIZE;
    int rows = vector[1]/TILE_SIZE;
    for (int i = 0; i < rows; i++){
        insertPosition += this->mapSize[0]/TILE_SIZE;
        if (insertPosition > this->textures.size()){
            for (int j = 0; j < vector[0]/TILE_SIZE; j++){
                this->textures.emplace_back(new SdlTexture(this->renderer, this->textureMap[5], 5));
            }
            insertPosition += newColumns;
        }else{
            for (int j = 0; j < newColumns; j++){
                auto it = textures.begin();
                std::advance(it,insertPosition);
                this->textures.insert(it, std::unique_ptr<SdlTexture>
                (new SdlTexture(this->renderer, this->textureMap[5], 5)));
                insertPosition++;
            }
        }
    }
    this->mapSize[0] = vector[0];
    this->mapSize[1] = vector[1];
    this->bombSites["A"]->setWidthAndHeight(vector[2], vector[3]);
    this->bombSites["B"]->setWidthAndHeight(vector[4], vector[5]);
    this->spawnSites["T"]->setWidthAndHeight(vector[6], vector[7]);
    this->spawnSites["CT"]->setWidthAndHeight(vector[8], vector[9]);
}

void MenueManager::changeTexture(const int& type, const SDL_Rect& camera){
    int x = 0, y = 0;
    
    //Get mouse offsets
    SDL_GetMouseState(&x, &y);
    
    //Adjust to camera
    x += camera.x;
    y += camera.y;

    int textureX = 0, textureY = 0;

	for (unsigned int i = 0; i < this->textures.size(); i++){
        //If the mouse is inside the tile
        if ((x > textureX) && (x < textureX + TILE_SIZE) && (y > textureY) && (y < textureY + TILE_SIZE)){
            auto it = textures.begin();
            std::advance(it,i);
            textures.erase(it);
            it = textures.begin();
            std::advance(it,i);
            textures.insert(it, std::unique_ptr<SdlTexture>(new SdlTexture(renderer,textureMap[type], type)));
			break;
        }
        //Move to next tile spot
        textureX += TILE_SIZE;

        //If we've gone too far
        if (textureX >= this->mapSize[0]){
            //Move back
            textureX = 0;

            //Move to the next row
            textureY += TILE_SIZE;
        }
    }
}

void MenueManager::fillSize(std::vector<SDL_Rect>& vector){
    vector = {{0,0,mapSize[0], mapSize[1]}, bombSites["A"]->getBox(), bombSites["B"]->getBox(), spawnSites["T"]->getBox(),
     spawnSites["CT"]->getBox()};
}

int MenueManager::getMapWidth(){
    return this->mapSize[0];
}

int MenueManager::getMapHeight(){
    return this->mapSize[1];
}

int MenueManager::getTextureMapSize(){
    return this->textureMap.size();
}

int MenueManager::getTexturesSize(){
    return textures.size();
}

std::string MenueManager::getTypeName(const int& type){
    return this->textureMap[type];
}
