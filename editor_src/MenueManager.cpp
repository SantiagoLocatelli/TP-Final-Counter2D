#include "MenueManager.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <utility>
#define TEXTURE_PATH "../../common_src/maps/textures.yaml"

MenueManager::MenueManager(SdlRenderer& r, const std::string path, int screenWidth, int screenHeight) : renderer(r){
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    this->mapID = path;
    TextureFactory factory;
    factory.unmarshalTextures(TEXTURE_PATH, this->map);
    factory.unmarshalMap(path.c_str(), this->map, this->textures, this->mapSize, r);
    factory.unmarshalBombSites(path.c_str(), this->bombSites, r);
    factory.unmarshalSpawnSites(path.c_str(), this->spawnSites, r);
}

std::unique_ptr<Presenter> MenueManager::createEditor(){
    return std::move(std::unique_ptr<Presenter>(new Editor(this->textures, this->map, this->mapSize, this->bombSites, this->spawnSites, screenWidth, screenHeight)));
}

std::unique_ptr<Presenter> MenueManager::createOptionsMenue(){
    return std::move(std::unique_ptr<Presenter>(new OptionsMenue(renderer, this->mapSize, this->bombSites, this->spawnSites, screenWidth, screenHeight)));
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

        out << YAML::Key << "size" << YAML::Value << YAML::Flow << this->mapSize;
    
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