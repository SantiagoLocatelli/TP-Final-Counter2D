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
    this->mapID = path;
    TextureFactory factory;
    factory.unmarshalTextures("../../common_src/maps/textures.yaml", this->map);

    std::ifstream stream(path);
    if (stream.is_open()){
        factory.unmarshalMap(path.c_str(), this->map, this->textures, renderer);
        factory.unmarshalBombSites(path.c_str(), this->bombSiteA, this->bombSiteB);
        factory.unmarshalSpawnSites(path.c_str(), this->spawnSiteT, this->spawnSiteCT);
    }else{
        createMap(renderer);
    }
}

void Editor::handleEvents(SDL_Event* event){
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
        if((x > textureX) && (x < textureX + TILE_WIDTH) && (y > textureY) && (y < textureY + TILE_HEIGHT)){
            //Get rid of old tile
			textures.erase(textures.begin() + i);
            std::unique_ptr<SdlTexture> texture = make_unique<SdlTexture>(renderer, map[this->currentType], currentType);
			textures.insert(textures.begin() + i, std::move(texture));
			break;
        }
        //Move to next tile spot
        textureX += TILE_WIDTH;

        //If we've gone too far
        if(textureX >= LEVEL_WIDTH){
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
    
    // position of bombs
    std::vector<int> positionA = {this->bombSiteA.x, this->bombSiteA.y};
    std::vector<int> positionB = {this->bombSiteB.x, this->bombSiteB.y};
    std::vector<int> sizeA = {this->bombSiteA.w, this->bombSiteA.h};
    std::vector<int> sizeB = {this->bombSiteB.w, this->bombSiteB.h};

    // position of spawns
    std::vector<int> positionT = {this->spawnSiteT.x, this->spawnSiteT.y};
    std::vector<int> positionCT = {this->spawnSiteCT.x, this->spawnSiteCT.y};
    std::vector<int> sizeT = {this->spawnSiteT.w, this->spawnSiteT.h};
    std::vector<int> sizeCT = {this->spawnSiteCT.w, this->spawnSiteCT.h};
    
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
}

std::string Editor::getTitle(){
    return this->map[this->currentType];
}

std::vector<SDL_Rect> Editor::getBombSite(){
    return {bombSiteA, bombSiteB};
}

void Editor::setBombSite(std::vector<SDL_Rect> rect){
    this->bombSiteA = rect[0];
    this->bombSiteB = rect[1];
}

std::vector<SDL_Rect> Editor::getSpawnSite(){
    return {spawnSiteT, spawnSiteCT};
}

void Editor::setSpawnSite(std::vector<SDL_Rect> rect){
    this->spawnSiteT = rect[0];
    this->spawnSiteCT = rect[1];
}

void Editor::createMap(SdlRenderer& renderer){
    for (int i = 0; i < 192; i++){
        this->textures.emplace_back(new SdlTexture(renderer, this->map[0], 0));
    }
    this->bombSiteA.x = 50;
    this->bombSiteA.y = 50;
    this->bombSiteA.w = 200;
    this->bombSiteA.h = 200;

    this->bombSiteB.x = 50;
    this->bombSiteB.y = 500;
    this->bombSiteB.w = 200;
    this->bombSiteB.h = 200;

    this->spawnSiteT.x = 1000;
    this->spawnSiteT.y = 50;
    this->spawnSiteT.w = 100;
    this->spawnSiteT.h = 100;

    this->spawnSiteCT.x = 0;
    this->spawnSiteCT.y = 250;
    this->spawnSiteCT.w = 100;
    this->spawnSiteCT.h = 100;
}