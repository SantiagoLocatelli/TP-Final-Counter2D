#include "MenueManager.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <utility>
#include <memory>
#define TILE_SIZE 80

MenueManager::MenueManager(SdlRenderer& r, int screenWidth, int screenHeight) : renderer(r){
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    this->currentType = 0;
    this->needsToSave = "";
    for (int i = 0; i < textureMap.size(); i++){
        this->textureScreen.emplace_back(r, textureMap[i].texturePath, i);
    }
}

void MenueManager::createMap(){
    this->mapSize = {10, 10};
    for (int i = 0; i < (int) (mapSize[0] * mapSize[1]); i++){
        this->textures.emplace_back(new SdlTexture(this->renderer, this->textureMap[0].texturePath, 0));
    }
    std::vector<std::string> auxBombs = {"A", "B"};
    std::vector<std::string> auxSpawns = {"T", "CT"};
    for (int i = 0; i < 2; i++){
        this->bombSites.emplace(auxBombs[i], new Draggable(this->renderer, "../../common_src/img/bombSite.png", 0, i * 100, 255, 0, 0));
        bombSites[auxBombs[i]]->setWidthAndHeight(100, 100);

        this->spawnSites.emplace(auxSpawns[i], new Draggable(this->renderer, "../../common_src/img/spawnSite.png", 200, (i * 100), 0, 255, 0));
        spawnSites[auxSpawns[i]]->setWidthAndHeight(100, 100);
    }

    this->mapID = "../../common_src/maps/mapaDePrueba.yaml";
}

void MenueManager::editMap(const std::string& mapID){
    TextureFactory factory;
    this->mapID = mapID;
    factory.unmarshalMap(mapID.c_str(), this->textureMap, this->textures, this->mapSize, this->renderer);
    factory.unmarshalBombSites(mapID.c_str(), this->bombSites, this->renderer, TILE_SIZE);
    factory.unmarshalSpawnSites(mapID.c_str(), this->spawnSites, this->renderer, TILE_SIZE);
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
    std::vector<float> positionA = { (float) bombSiteA.x/ (float) TILE_SIZE, (float) bombSiteA.y/ (float) TILE_SIZE};
    std::vector<float> positionB = {(float) bombSiteB.x/ (float) TILE_SIZE, (float) bombSiteB.y/ (float) TILE_SIZE};
    std::vector<float> sizeA = {(float) bombSiteA.w/ (float) TILE_SIZE, (float) bombSiteA.h/ (float) TILE_SIZE};
    std::vector<float> sizeB = {(float) bombSiteB.w/ (float) TILE_SIZE, (float) bombSiteB.h/ (float) TILE_SIZE};

    // position of spawns
    std::vector<float> positionT = {(float) spawnSiteT.x/(float) TILE_SIZE, (float) spawnSiteT.y/(float) TILE_SIZE};
    std::vector<float> sizeT = {(float) spawnSiteT.w/(float) TILE_SIZE, (float) spawnSiteT.h/(float) TILE_SIZE};
    std::vector<float> positionCT = {(float) spawnSiteCT.x/(float) TILE_SIZE, (float) spawnSiteCT.y/(float) TILE_SIZE};
    std::vector<float> sizeCT = {(float) spawnSiteCT.w/(float) TILE_SIZE, (float) spawnSiteCT.h/(float) TILE_SIZE};
    
    
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

    this->needsToSave = "";
}

void MenueManager::renderTextures(const SDL_Rect& camera){
    int x = 0, y = 0;
    for (auto &texture : this->textures){
        texture->render(x - camera.x, y - camera.y, TILE_SIZE, TILE_SIZE);
        
        //Move to next tile spot
        x += TILE_SIZE;

        //If we've gone too far
        if (x >= this->mapSize[0] * TILE_SIZE){
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_SIZE;
        }
    }
}


void MenueManager::renderBombSites(const SDL_Rect& camera){
    std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->bombSites.begin();
    while (iterator != this->bombSites.end()){
        iterator->second->setBlendMode(SDL_BLENDMODE_BLEND);
        iterator->second->setAlpha(100);
        iterator->second->render(camera);
        ++iterator;
    }
}

void MenueManager::renderSpawnSites(const SDL_Rect& camera){
    std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->spawnSites.begin();
    while (iterator != this->spawnSites.end()){
        iterator->second->setBlendMode(SDL_BLENDMODE_BLEND);
        iterator->second->setAlpha(100);
        iterator->second->render(camera);
        ++iterator;
    }
}

void MenueManager::renderMapTextures(const SDL_Rect& camera){
    int x = 0, y = 0;
    for (auto &texture : this->textureScreen){
        texture.render(x - camera.x, y - camera.y, TILE_SIZE, TILE_SIZE);
        
        //Move to next tile spot
        x += TILE_SIZE;

        //If we've gone too far
        if (x >= this->screenWidth){
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_SIZE;
        }
    }
}

void MenueManager::handleBombSitesEvent(SDL_Event* event, const SDL_Rect& camera){
    std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->bombSites.begin();
    while (iterator != this->bombSites.end()){
        int auxX = iterator->second->getPosX();
        int auxY = iterator->second->getPosY();

        iterator->second->handleEvent(event, camera);
        
        if (auxX != iterator->second->getPosX() || auxY != iterator->second->getPosY()){
            this->needsToSave = "*";
        }
        ++iterator;
    }
}

void MenueManager::handleSpawnSitesEvent(SDL_Event* event, const SDL_Rect& camera){
    std::map<std::string, std::unique_ptr<Draggable>>::iterator iterator = this->spawnSites.begin();
    while (iterator != this->spawnSites.end()){
        int auxX = iterator->second->getPosX();
        int auxY = iterator->second->getPosY();

        iterator->second->handleEvent(event, camera);

        if (auxX != iterator->second->getPosX() || auxY != iterator->second->getPosY()){
            this->needsToSave = "*";
        }
        ++iterator;
    }
}

void MenueManager::handleSelectTexture(SDL_Event* event, const SDL_Rect& camera){
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if(event->button.button == SDL_BUTTON_LEFT){
            int x = 0, y = 0;
            int textureX = 0, textureY = 0;
            
            //Get mouse offsets
            SDL_GetMouseState(&x, &y);
            
            //Adjust to camera
            x += camera.x;
            y += camera.y;

            for (unsigned int i = 0; i < this->textureScreen.size(); i++){
                //If the mouse is inside the tile
                if ((x > textureX) && (x < textureX + TILE_SIZE) && (y > textureY) && (y < textureY + TILE_SIZE)){
                    this->currentType = textureScreen[i].getType();
                    break;
                }
                //Move to next tile spot
                textureX += TILE_SIZE;

                //If we've gone too far
                if (textureX >= this->screenWidth){
                    //Move back
                    textureX = 0;

                    //Move to the next row
                    textureY += TILE_SIZE;
                }
            }
        }
    }
}

//numeros pares con el 0 son los width numeros impares son los height
void MenueManager::changeSizeOfSites(std::vector<float>& vector){
    changeMapSize(vector[0], vector[1]);
    this->mapSize[0] = vector[0];
    this->mapSize[1] = vector[1];
    this->bombSites["A"]->setWidthAndHeight((int) (vector[2] * TILE_SIZE), (int) (vector[3] * TILE_SIZE));
    this->bombSites["B"]->setWidthAndHeight((int) (vector[4] * TILE_SIZE), (int) (vector[5] * TILE_SIZE));
    this->spawnSites["T"]->setWidthAndHeight((int) (vector[6] * TILE_SIZE), (int) (vector[7] * TILE_SIZE));
    this->spawnSites["CT"]->setWidthAndHeight((int) (vector[8] * TILE_SIZE), (int) (vector[9] * TILE_SIZE));
}

void MenueManager::changeMapSize(const int& width, const int& height){
    int endOfRowPosition = 0;
    int newColumns = width - this->mapSize[0];
    int rows = height;
    int newRows = rows - this->mapSize[1];
    //Me fijo si sacaron filas
    if (newRows < 0){
        for (int i = 0; i < (newRows * -1); i++){
            for (int i = 0; i < (this->mapSize[0]); i++){
                this->textures.pop_back();
            }
        }
    }
    for (int i = 0; i < rows; i++){
        endOfRowPosition += this->mapSize[0];
        //si agregan filas
        if ((unsigned int) endOfRowPosition > this->textures.size()){
            for (int j = 0; j < width/TILE_SIZE; j++){
                this->textures.emplace_back(new SdlTexture(this->renderer, this->textureMap[5].texturePath, 5));
            }
            endOfRowPosition += newColumns;
        //si agregar columnas
        }else if (newColumns >= 0){
            for (int j = 0; j < newColumns; j++){
                auto it = this->textures.begin();
                std::advance(it, endOfRowPosition);
                this->textures.insert(it, std::unique_ptr<SdlTexture>
                (new SdlTexture(this->renderer, this->textureMap[5].texturePath, 5)));
                endOfRowPosition++;
            }
        //si sacan columnas
        }else{
            for (int j = 0; j < (newColumns * -1); j++){
                auto it = this->textures.begin();
                std::advance(it, ((this->mapSize[0] * (rows - i) ) - j) - 1);
                this->textures.erase(it);
            }
        }
    }
}

void MenueManager::changeTexture(const SDL_Rect& camera){
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
            textures.insert(it, std::unique_ptr<SdlTexture>(new SdlTexture(renderer,textureMap[currentType].texturePath, currentType)));
			this->needsToSave = "*";
            break;
        }
        //Move to next tile spot
        textureX += TILE_SIZE;

        //If we've gone too far
        if (textureX >= (this->mapSize[0] * TILE_SIZE)){
            //Move back
            textureX = 0;

            //Move to the next row
            textureY += TILE_SIZE;
        }
    }
}

void MenueManager::fillSize(std::vector<SDL_Rect>& vector){
    vector = {{0,0,(int) (mapSize[0] * TILE_SIZE), (int)(mapSize[1] * TILE_SIZE)}, bombSites["A"]->getBox(), bombSites["B"]->getBox(), spawnSites["T"]->getBox(), spawnSites["CT"]->getBox()};
    changeToMeters(vector);
}

void MenueManager::changeToMeters(std::vector<SDL_Rect>& vector){
    for (auto &value : vector){
        value.x = value.x/TILE_SIZE;
        value.y = value.y/TILE_SIZE;
        value.w = value.w/TILE_SIZE;
        value.h = value.h/TILE_SIZE;
    }
}

void MenueManager::needToSave(){
    this->needsToSave = "*";
}

std::string MenueManager::getSaveState(){
    return needsToSave;
}

int MenueManager::getMapWidth(){
    return this->mapSize[0] * TILE_SIZE;
}

int MenueManager::getMapHeight(){
    return this->mapSize[1] * TILE_SIZE;
}

int MenueManager::getTextureMapSize(){
    return this->textureMap.size();
}

int MenueManager::getTexturesSize(){
    return textures.size();
}

int MenueManager::getTileSize(){
    return TILE_SIZE;
}

int MenueManager::getScreenWidth(){
    return this->screenWidth;
}

int MenueManager::getScreenHeight(){
    return this->screenHeight;
}