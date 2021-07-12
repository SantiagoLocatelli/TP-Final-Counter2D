#include "InitialMenue.h"
#include <dirent.h>
#include <algorithm>
#define FONT_PATH "../../common_src/img/digital-7.ttf"
#define BACKGROUND "../../common_src/img/counter.jpeg"
#define CHUNK_PATH "../../common_src/sound/pressButton.mp3"
#define FONT_SIZE 26
void parse(std::vector<std::string>& files);

InitialMenue::InitialMenue(SdlRenderer& renderer, MenueManager& m ,int screenW, int screenH) : 
    Presenter(m, screenW, screenH), background(renderer, BACKGROUND),
    crearMapTexture(renderer, FONT_PATH, FONT_SIZE, "Crear Mapa", 255, 255, 255),
    editarMapTexture(renderer, FONT_PATH, FONT_SIZE, "Editar Mapa", 255, 255, 255){
    std::vector<std::string> vec = {CHUNK_PATH};
    this->chunk = std::unique_ptr<SdlMixer>(new SdlMixer(vec));
    this->editMap = false;
    this->createMap = false;

    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("../../common_src/maps/")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_name[0] != '.'){
                files.emplace_back(ent->d_name);
            }
        }
        closedir (dir);
        delete ent;
    }
    parse(files);
    for (auto &file : files){
        this->editableMaps.emplace_back(renderer, FONT_PATH, FONT_SIZE, file, 255, 255, 255);
        this->mapsID.emplace_back("../../common_src/maps/" + file + ".yaml");
    }
}

void parse(std::vector<std::string>& files){
    std::string prot_end(".");
    for (auto &file : files){
        std::string::iterator prot_i = std::search(file.begin(),
                file.end(), prot_end.begin(), prot_end.end());

        int start_position = prot_i - file.begin();

        file.erase(start_position, file.length());
    }
}

void InitialMenue::render(){
    SDL_Rect screen = Presenter::getCameraBox();
    this->background.render(0, 0, screen.w, screen.h);
    if (editMap){
        int i = 0;
        for (auto &map : editableMaps){
            map.render(250, i);
            i += 100;
        }
    }else{
        this->editarMapTexture.render(250, 100);
        this->crearMapTexture.render(250, 200);
    }
}

void InitialMenue::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            if (editMap){
                int i = 0;
                int position = 0;
                for (auto &map : editableMaps){
                    if (map.isMouseTouching(250, i)){
                        this->chunk->playChunk(0);
                        map.setColor(255, 255, 0);
                        this->createMap = true;
                        this->mapPosition = position; 
                        break;
                    }
                    i += 100;
                    position++;
                }
            }else{
                if (this->editarMapTexture.isMouseTouching(250, 100)){
                    this->chunk->playChunk(0);
                    this->editarMapTexture.setColor(255, 255, 0);
                    this->editMap = true;
                }else if (this->crearMapTexture.isMouseTouching(250, 200)){
                    this->chunk->playChunk(0);
                    this->crearMapTexture.setColor(255, 255, 0);
                    this->createMap = true;
                }
            }
        }
    }
}

void InitialMenue::aceptChanges(){
    if (editMap){
        Presenter::editMap(this->mapsID[this->mapPosition]);
    }else if (createMap){
        Presenter::createMap();
    }
}

bool InitialMenue::finish(){
    if (createMap){
        return true;
    }
    return false;
}

std::string InitialMenue::getTitle(){
    return "Menue";
}