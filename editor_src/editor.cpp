#include "editor.h"
#include "TextureFactory.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#define TILE_WIDTH 80
#define TILE_HEIGHT 80
#define LEVEL_WIDTH 1280

Editor::Editor(const std::string path, SdlRenderer& renderer){
    this->currentType = 0;
    this->mapID = path;
    TextureFactory factory;
    factory.unmarshalTextures("../common_src/maps/textures.yaml", this->map);

    std::ifstream stream(path);
    if (stream.is_open()){
        factory.unmarshalMap(path.c_str(), this->map, this->textures, renderer);
    }else{
        factory.createMap(this->map, this->textures, renderer);
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

void Editor::put_tile(SDL_Rect& camera, SdlRenderer& renderer){
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
            std::unique_ptr<SdlTexture> texture = std::make_unique<SdlTexture>(renderer, map[this->currentType], currentType);
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
    std::vector<int> textureTypes;
    for (auto &texture : this->textures){
        textureTypes.push_back(texture->getType());
    }
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "map";
    out << YAML::Value << YAML::Flow << textureTypes;

    std::ofstream fout(this->mapID.c_str()); 
    fout << out.c_str();
}

void Editor::render(SDL_Rect& camera){
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