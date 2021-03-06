#include "MenuManager.h"
#include "yaml-cpp/yaml.h"
#include "../common_src/Utils.h"
#include <fstream>
#include <utility>
#include <memory>

MenuManager::MenuManager(SdlRenderer& r, int screenWidth, int screenHeight) : renderer(r){
    std::vector<std::string> vec = {CHUNK_PATH};
    this->music = std::unique_ptr<SdlMixer>(new SdlMixer(MELODY, vec));
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    this->currentType = 0;
    this->needsToSave = "";
    this->goToStart = false;
    this->isWeapon = false;
    this->quitEditor = false;
    
    YAML::Node yaml_map = YAML::LoadFile(WEAPONS_PATH);
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        std::pair<std::string, int> texture = it->as<std::pair<std::string, int>>();
        if (texture.second != BOMB){
            this->weaponTextureScreen.emplace_back(r, texture.first, 255, 255, 255, texture.second);
            this->weaponMap.emplace(texture.second, SdlTexture(r, texture.first, 255, 255, 255, texture.second));
        }
    }

    for (int i = 0; i < textureMap.size(); i++){
        if (textureMap[i].isBox == 1){
            this->wallTextureScreen.emplace_back(r, textureMap[i].texturePath, i);
        }else{
            this->floorTextureScreen.emplace_back(r, textureMap[i].texturePath, i);
        }
    }

    this->borderType = wallTextureScreen.front().getType();
}

void MenuManager::createMap(const std::string mapID){
    this->mapSize = {17, 17};
    this->currentType = 0;
    this->isWeapon = false;
    for (int i = 0; i < (int) (mapSize[0] * mapSize[1]); i++){
        if ((i % mapSize[0]) == 0 || i <= mapSize[0] || ((i + 1) % mapSize[0]) == 0 || i > (mapSize[0] * mapSize[1]) - mapSize[0]){
            this->textures.emplace_back(new SdlTexture(this->renderer, this->textureMap[borderType].texturePath, borderType));    
        }else{
            this->textures.emplace_back(new SdlTexture(this->renderer, this->textureMap[0].texturePath, 0));
        }
    }
    for (int i = 0; i < (int) (mapSize[0] * mapSize[1]); i++){
        this->weaponTypes.push_back(-1);
    }
    std::vector<std::string> spawnSites = {"T", SPAWN_SITE_T, "CT", SPAWN_SITE_CT};
    for (unsigned int i = 0; i < spawnSites.size() - 1; i++){
        this->rectSites.emplace(spawnSites[i], new Draggable(this->renderer, spawnSites[i+1], 3 * TILE_SIZE, i * 3 * TILE_SIZE, 0, 255, 0));
        rectSites[spawnSites[i]]->setWidthAndHeight(3 * TILE_SIZE, 3 * TILE_SIZE);
        i++;
    }
    std::vector<std::string> bombSites = {"A", BOMB_SITE_A , "B", BOMB_SITE_B};
    for (unsigned int i = 0; i < bombSites.size() - 1; i++){
        this->rectSites.emplace(bombSites[i], new Draggable(this->renderer, bombSites[i+1], 6 * TILE_SIZE, i * 6 * TILE_SIZE, 255, 0, 0));
        rectSites[bombSites[i]]->setWidthAndHeight(3 * TILE_SIZE, 3 * TILE_SIZE);
        i++;
    }

    this->mapID = MAPS_DIR + mapID + ".yaml";
}

void MenuManager::editMap(const std::string& mapID){
    TextureFactory factory;
    this->mapID = mapID;
    this->currentType = 0;
    this->isWeapon = false;
    factory.unmarshalMap(mapID.c_str(), this->textureMap, this->textures, this->mapSize, this->renderer);
    factory.unmarshalSites(mapID.c_str(), this->rectSites, this->renderer, TILE_SIZE);
    factory.unmarshalWeapons(mapID.c_str(), this->weaponTypes);
}

void MenuManager::loadToFile(){
    //texture in map
    std::vector<int> textureTypes;
    
    // get the position and dimension from the textures
    SDL_Rect bombSiteA = this->rectSites["A"]->getBox();
    SDL_Rect bombSiteB = {0,0,0,0};
    if (rectSites.size() == 4){
        bombSiteB = this->rectSites["B"]->getBox();
    }
    SDL_Rect spawnSiteT = this->rectSites["T"]->getBox();
    SDL_Rect spawnSiteCT = this->rectSites["CT"]->getBox();

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

        out << YAML::Key << "weapons" << YAML::Value << YAML::Flow << this->weaponTypes;
    
    out << YAML::EndMap;

    //load into file
    std::ofstream fout(this->mapID.c_str()); 
    fout << out.c_str();

    this->needsToSave = "";
}

void MenuManager::renderTextures(const SDL_Rect& camera){
    int x = 0, y = 0;
    for (auto &texture : this->textures){
        if (this->textureMap[texture->getType()].clip.x == -1){
            texture->render(x - camera.x, y - camera.y, TILE_SIZE, TILE_SIZE);
        }else{
            SDL_Rect aux = this->textureMap[texture->getType()].clip;
            texture->render(x - camera.x, y - camera.y, TILE_SIZE, TILE_SIZE, &aux);
        }
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

void MenuManager::renderWeapons(const SDL_Rect& camera){
    int x = 0, y = 0;
    for (auto &type : this->weaponTypes){
        if (type != -1){
            this->weaponMap.at(type).render(x - camera.x, y - camera.y);
        }
        
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

void MenuManager::renderBombSites(const SDL_Rect& camera){
    std::vector<std::string> aux = {"A"};
    if (rectSites.size() == 4){
        aux.push_back("B");
    }
    for (auto label : aux){
        this->rectSites[label]->setBlendMode(SDL_BLENDMODE_BLEND);
        this->rectSites[label]->setAlpha(100);
        this->rectSites[label]->render(camera);
    }
}

void MenuManager::renderSpawnSites(const SDL_Rect& camera){
    for (auto label : {"T", "CT"}){
        this->rectSites[label]->setBlendMode(SDL_BLENDMODE_BLEND);
        this->rectSites[label]->setAlpha(100);
        this->rectSites[label]->render(camera);
    }
}

void MenuManager::renderMapFloors(int& page){
    renderMapTextures(page, this->floorTextureScreen);
}

void MenuManager::renderMapWalls(int& page){
    renderMapTextures(page, this->wallTextureScreen);
}

void MenuManager::renderMapWeapons(int& page){
    renderMapTextures(page, this->weaponTextureScreen);
}

void MenuManager::renderMapTextures(int& page, std::vector<SdlTexture>& textures){
    int x = 0, y = 0, j = 0;
    //numRenderTexture es la variable que indica cuantas texturas entran en la pantalla.
    //el menos 2 tileSize es donde van las flechas, mientras que la fila de menos es donde esta puesto el BACK.
    int numRenderTexture = (this->screenWidth/TILE_SIZE * (this->screenHeight/TILE_SIZE - 1)) - 2;
    int i = page * numRenderTexture;
    while ((unsigned int) i >= textures.size()){
        page--;
        i = page * numRenderTexture;
    }
    for (; (unsigned int) i < textures.size(); i++){
        if (j == numRenderTexture){
            break;
        }
        j++;
        if (this->textureMap[textures[i].getType()].clip.x == -1){
            textures[i].render(x, y, TILE_SIZE, TILE_SIZE);
        }else{
            SDL_Rect aux = this->textureMap[textures[i].getType()].clip;
            textures[i].render(x, y, TILE_SIZE, TILE_SIZE, &aux);
        }
        
        //Move to next tile spot
        x += TILE_SIZE;

        //right arrow position
        if (y == TILE_SIZE * 2 && x == this->screenWidth - TILE_SIZE){
            x += TILE_SIZE;
        }

        //If we've gone too far
        if (x >= this->screenWidth){
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_SIZE;
            // left arrow position
            if (y == TILE_SIZE * 2){
                x += TILE_SIZE;
            }
        }
    }
}

void MenuManager::handleBombSitesEvent(SDL_Event* event, const SDL_Rect& camera){
    std::vector<std::string> aux = {"A"};
    if (rectSites.size() == 4){
        aux.push_back("B");
    }
    for (auto label : aux){
        int auxX = this->rectSites[label]->getPosX();
        int auxY = this->rectSites[label]->getPosY();

        this->rectSites[label]->handleEvent(event, camera);

        if (auxX != this->rectSites[label]->getPosX() || auxY != this->rectSites[label]->getPosY()){
            this->needsToSave = "*";
        } 
    }
}

void MenuManager::handleSpawnSitesEvent(SDL_Event* event, const SDL_Rect& camera){
    for (auto label : {"T", "CT"}){
        int auxX = this->rectSites[label]->getPosX();
        int auxY = this->rectSites[label]->getPosY();

        this->rectSites[label]->handleEvent(event, camera);

        if (auxX != this->rectSites[label]->getPosX() || auxY != this->rectSites[label]->getPosY()){
            this->needsToSave = "*";
        } 
    }
}

void MenuManager::handleSelectFloor(SDL_Event* event, int& page){
    this->isWeapon = false;
    handleSelectTexture(event, page, this->floorTextureScreen);
}

void MenuManager::handleSelectWall(SDL_Event* event, int& page){
    this->isWeapon = false;
    handleSelectTexture(event, page, this->wallTextureScreen);
}

void MenuManager::handleSelectWeapon(SDL_Event* event, int& page){
    this->isWeapon = true;
    handleSelectTexture(event, page, this->weaponTextureScreen);
}

void MenuManager::handleSelectTexture(SDL_Event* event, int& page, std::vector<SdlTexture>& textures){
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if(event->button.button == SDL_BUTTON_LEFT){
            int x = 0, y = 0, j = 0;
            int textureX = 0, textureY = 0;

            int numRenderTexture = (this->screenWidth/TILE_SIZE * (this->screenHeight/TILE_SIZE - 1)) - 2;
            int i = page * numRenderTexture;
            
            //Get mouse offsets
            SDL_GetMouseState(&x, &y);
            while ((unsigned int) i >= textures.size()){
                page--;
                i = page * numRenderTexture;
            }
            for (; (unsigned int) i < textures.size(); i++){
                if (j == numRenderTexture){
                    break;
                }
                j++;
                //If the mouse is inside the tile
                if ((x > textureX) && (x < textureX + TILE_SIZE) && (y > textureY) && (y < textureY + TILE_SIZE)){
                    this->music->playChunk(0);
                    this->currentType = textures[i].getType();
                    break;
                }
                //Move to next tile spot
                textureX += TILE_SIZE;

                //right arrow position
                if (textureY == TILE_SIZE * 2 && textureX == this->screenWidth - TILE_SIZE){
                    textureX += TILE_SIZE;
                }

                //If we've gone too far
                if (textureX >= this->screenWidth){
                    //Move back
                    textureX = 0;

                    //Move to the next row
                    textureY += TILE_SIZE;

                    //left arrow position
                    if (textureY == TILE_SIZE * 2){
                        textureX += TILE_SIZE;
                    }
                }
            }
        }
    }
}

//numeros pares con el 0 son los width numeros impares son los height
void MenuManager::changeSizeOfSites(std::vector<float>& vector){
    if (vector[0] != mapSize[0] || vector[1] != mapSize[1]){
        changeMapSize(vector[0], vector[1]);
        this->mapSize[0] = (int) vector[0];
        this->mapSize[1] = (int) vector[1];
    }
    this->rectSites["T"]->setWidthAndHeight((int) (vector[2] * TILE_SIZE), (int) (vector[3] * TILE_SIZE));
    this->rectSites["CT"]->setWidthAndHeight((int) (vector[4] * TILE_SIZE), (int) (vector[5] * TILE_SIZE));
    this->rectSites["A"]->setWidthAndHeight((int) (vector[6] * TILE_SIZE), (int) (vector[7] * TILE_SIZE));
    if (rectSites.size() == 4){
        this->rectSites["B"]->setWidthAndHeight((int) (vector[8] * TILE_SIZE), (int) (vector[9] * TILE_SIZE));
    }
}

void MenuManager::changeMapSize(const int& width, const int& height){
    int endOfRowPosition = 0;
    int newColumns = width - this->mapSize[0];
    int rows = height;
    int newRows = rows - this->mapSize[1];
    //Me fijo si sacaron filas
    if (newRows < 0){
        deleteTextureRows(newRows * -1);
    }
    for (int i = 0; i < rows; i++){
        endOfRowPosition += this->mapSize[0];
        //si agregan filas
        if ((unsigned int) endOfRowPosition > this->textures.size() && newRows > 0){
            for (int i = 0; i < newRows; i++){
                insertTextureRows(width);
            }
            if (newColumns < 0){
                deleteTextureColumns(rows, i, newColumns * -1);
            }
            break;
        //si agregan columnas
        }else if (newColumns > 0){
            insertTextureColumns(endOfRowPosition, newColumns);
            endOfRowPosition += newColumns;
        //si sacan columnas
        }else if (newColumns < 0){
            deleteTextureColumns(rows, i, newColumns * -1);
        }
    }
    for (int i = 0; i < width * height; i++){
        if ((i % width) == 0 || i <= width || ((i + 1) % width) == 0 || i > (width * height) - width){
            if (!this->textureMap[this->textures[i]->getType()].isBox){
                this->textures[i] = std::unique_ptr<SdlTexture>(new SdlTexture(this->renderer, this->textureMap[borderType].texturePath, borderType));
            }
            this->weaponTypes[i] = -1;
        }
    }
}

void MenuManager::deleteTextureColumns(const int numberOfRows, const int rowNumber, const int newColumns){
    int rowEnd = this->mapSize[0] * (numberOfRows - rowNumber) - 1;
    for (int i = 0; i < newColumns; i++){
        this->textures.erase(this->textures.begin() + rowEnd);
        this->weaponTypes.erase(this->weaponTypes.begin() + rowEnd);
        rowEnd--;
    }
}

void MenuManager::deleteTextureRows(const int newRows){
    for (int i = 0; i < newRows; i++){
        for (int j = 0; j < this->mapSize[0]; j++){
            this->textures.pop_back();
            this->weaponTypes.pop_back();
        }
    }
}

void MenuManager::insertTextureColumns(const int endOfRowPosition , const int newColumns){
    for (int i = 0; i < newColumns; i++){
        this->textures.insert(textures.begin() + endOfRowPosition, std::unique_ptr<SdlTexture>
        (new SdlTexture(this->renderer, this->textureMap[0].texturePath, 0)));

        this->weaponTypes.insert(weaponTypes.begin() + endOfRowPosition, -1);
    }
}

void MenuManager::insertTextureRows(const int columnsNumber){
    for (int i = 0; i < columnsNumber; i++){
        this->textures.emplace_back(new SdlTexture(this->renderer, this->textureMap[0].texturePath, 0));
        this->weaponTypes.push_back(-1);
    }
}

void MenuManager::changeTexture(const SDL_Rect& camera){
    int x = 0, y = 0;
    
    //Get mouse offsets
    SDL_GetMouseState(&x, &y);
    
    //Adjust to camera
    x += camera.x;
    y += camera.y;

    int textureX = 0, textureY = 0;

	for (unsigned int i = 0; i < this->textures.size(); i++){
        //if the mouse is inside the tile
        if ((x > textureX) && (x < textureX + TILE_SIZE) && (y > textureY) && (y < textureY + TILE_SIZE)){
            if (isWeapon){
                if (!this->textureMap[textures[i]->getType()].isBox){
                    weaponTypes[i] = currentType;
                }
            }else if ((i % mapSize[0]) == 0 || (int) i <= mapSize[0] || ((i + 1) % mapSize[0]) == 0 || (int) i > (mapSize[0] * mapSize[1]) - mapSize[0]){
                //only change the border if is a wall
                if (this->textureMap[currentType].isBox){
                    textures[i] = std::unique_ptr<SdlTexture>(new SdlTexture(renderer,textureMap[currentType].texturePath, currentType));
                }

            }else{
                textures[i] = std::unique_ptr<SdlTexture>(new SdlTexture(renderer,textureMap[currentType].texturePath, currentType));
                weaponTypes[i] = -1;
            }
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

void MenuManager::putBombSites(const int numberOfBombs){
    if (numberOfBombs == 1 && this->rectSites.size() == 4){
        this->rectSites.erase("B");
        this->needsToSave = "*";
    }else if (numberOfBombs == 2 && this->rectSites.size() == 3){
        this->rectSites.emplace("B", new Draggable(this->renderer, BOMB_SITE_B, 100, 400, 255, 0, 0));
        this->rectSites["B"]->setWidthAndHeight(3 * TILE_SIZE, 3 * TILE_SIZE);
        this->needsToSave = "*";
    }
}

void MenuManager::fillSize(std::vector<SDL_Rect>& vector){
    vector = {{0,0, mapSize[0] * TILE_SIZE, mapSize[1] * TILE_SIZE}, rectSites["T"]->getBox(), rectSites["CT"]->getBox(), rectSites["A"]->getBox()};
    if (rectSites.size() == 4){
        vector.push_back(rectSites["B"]->getBox());
    }
    changeToMeters(vector);
}

void MenuManager::changeToMeters(std::vector<SDL_Rect>& vector){
    for (auto &value : vector){
        value.x = value.x/TILE_SIZE;
        value.y = value.y/TILE_SIZE;
        value.w = value.w/TILE_SIZE;
        value.h = value.h/TILE_SIZE;
    }
}

void MenuManager::playMusic(){
    this->music->play();
}

void MenuManager::pauseMusic(){
    this->music->pause();
}

void MenuManager::goToMenu(){
    this->goToStart = true;
}

void MenuManager::requestQuit(){
    this->quitEditor = true;
}

bool MenuManager::quitToMenu(){
    if (goToStart){
        goToStart = false;
        return true;
    }
    return false;
}

void MenuManager::needToSave(){
    this->needsToSave = "*";
}

std::string MenuManager::getSaveState(){
    return needsToSave;
}

int MenuManager::getMapWidth(){
    return this->mapSize[0] * TILE_SIZE;
}

int MenuManager::getMapHeight(){
    return this->mapSize[1] * TILE_SIZE;
}

int MenuManager::getTextureMapSize(){
    return this->textureMap.size();
}

int MenuManager::getTexturesSize(){
    return textures.size();
}

int MenuManager::getTileSize(){
    return TILE_SIZE;
}

bool MenuManager::quit(){
    if (this->quitEditor){
        this->quitEditor = false;
        return true;
    }
    return false;
}