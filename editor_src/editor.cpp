#include "editor.h"
#include "TextureFactory.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <stdio.h>
#include <memory>
#include <utility>
#define TILE_WIDTH 80
#define TILE_HEIGHT 80
#define LEVEL_WIDTH 1280

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

Editor::Editor(const std::string path, SdlRenderer& renderer){
    this->currentType = 0;
    this->renderBombSites = false;
    this->renderSpawnSites = false;
    this->mapID = path;
    TextureFactory factory;
    factory.unmarshalTextures("../../common_src/maps/textures.yaml", this->map);

    std::ifstream stream(path);
    if (stream.is_open()){
        factory.unmarshalMap(path.c_str(), this->map, this->textures, renderer);
        factory.unmarshalBombSites(path.c_str(), this->bombSites, renderer);
        factory.unmarshalSpawnSites(path.c_str(), this->spawnSites, renderer);
    }else{
        createMap(renderer);
    }
}

void Editor::handleEvents(SDL_Event* event, SDL_Rect camera){
    if (event->type == SDL_MOUSEWHEEL){
        //On mouse wheel scroll
        if (event->wheel.y > 0){
            //Scroll through tiles
            currentType--;
            if (currentType < 0){
                currentType = this->map.size() - 1;
            }
        }else if (event->wheel.y < 0){
            //Scroll through tiles
            currentType++;
            if (currentType > this->map.size() - 1){
                currentType = 0;
            }
        }
    }

    if (renderBombSites){
        std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->bombSites.begin();
        while (iterator != this->bombSites.end()){
            iterator->second->handleEvent(event, camera);
            ++iterator;
        }
    }

    if (renderSpawnSites){
        std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->spawnSites.begin();
        while (iterator != this->spawnSites.end()){
            iterator->second->handleEvent(event, camera);
            ++iterator;
        }
    }
}

void Editor::initMenue(){
    this->menue->init();
}

void Editor::presentBombSites(){
    this->renderBombSites = true;
}

void Editor::stopPresentingBombSites(){
    this->renderBombSites = false;
}

void Editor::presentSpawnSites(){
    this->renderSpawnSites = true;
}

void Editor::stopPresentingSpawnSites(){
    this->renderSpawnSites = false;
}

void Editor::put_tile(SDL_Rect camera, SdlRenderer& renderer){
    //Mouse offsets
    int x = 0, y = 0;
    
    //Get mouse offsets
    SDL_GetMouseState(&x, &y);
    
    //Adjust to camera
    x += camera.x;
    y += camera.y;

    int textureX = 0, textureY = 0;

	for (int i = 0; i < textures.size(); i++){
        //If the mouse is inside the tile
        if ((x > textureX) && (x < textureX + TILE_WIDTH) && (y > textureY) && (y < textureY + TILE_HEIGHT)){
            //Get rid of old tile
			textures.erase(textures.begin() + i);
            std::unique_ptr<SdlTexture> texture = make_unique<SdlTexture>(renderer, map[this->currentType], currentType);
			textures.insert(textures.begin() + i, std::move(texture));
			break;
        }
        //Move to next tile spot
        textureX += TILE_WIDTH;

        //If we've gone too far
        if (textureX >= LEVEL_WIDTH){
            //Move back
            textureX = 0;

            //Move to the next row
            textureY += TILE_HEIGHT;
        }
    }
}

void Editor::saveMap(){
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

void Editor::render(SDL_Rect camera){
    int x = 0, y = 0;
    for (auto &texture : this->textures){
        texture->render(x - camera.x, y - camera.y, TILE_WIDTH, TILE_HEIGHT);
        
        //Move to next tile spot
        x += TILE_WIDTH;

        //If we've gone too far
        if (x >= LEVEL_WIDTH){
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_HEIGHT;
        }
    }
    if (renderBombSites){
        std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->bombSites.begin();
        while (iterator != this->bombSites.end()){
            iterator->second->setBlendMode(SDL_BLENDMODE_BLEND);
            iterator->second->setAlpha(100);
            iterator->second->render(camera);
            ++iterator;
        }
    }
    if (renderSpawnSites){
        std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->spawnSites.begin();
        while (iterator != this->spawnSites.end()){
            iterator->second->setBlendMode(SDL_BLENDMODE_BLEND);
            iterator->second->setAlpha(100);
            iterator->second->render(camera);
            ++iterator;
        }
    }
}

std::string Editor::getTitle(){
    return this->map[this->currentType];
}

void Editor::createMap(SdlRenderer& renderer){
    for (int i = 0; i < 192; i++){
        this->textures.emplace_back(new SdlTexture(renderer, this->map[0], 0));
    }
}