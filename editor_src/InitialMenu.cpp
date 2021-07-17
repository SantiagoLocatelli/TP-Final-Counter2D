#include "InitialMenu.h"
#include <dirent.h>
#include <algorithm>
#define FONT_PATH "../../common_src/img/digital-7.ttf"
#define FONT_PATH2 "../../common_src/img/aerial.ttf"
#define BACKGROUND "../../common_src/img/counter.jpeg"
#define CHUNK_PATH "../../common_src/sound/pressButton.mp3"
#define MAPS_PER_PAGE 3
void parse(std::vector<std::string>& files);

InitialMenu::InitialMenu(SdlRenderer& renderer, MenuManager& m ,int screenW, int screenH) : 
    Presenter(m, screenW, screenH), background(renderer, BACKGROUND),
    crearMapTexture(renderer, FONT_PATH, FONT_SIZE, "Crear Mapa", 255, 255, 255),
    editarMapTexture(renderer, FONT_PATH, FONT_SIZE, "Editar Mapa", 255, 255, 255),
    arrow(renderer, FONT_PATH, FONT_SIZE * 2, "->", 255, 255, 255),
    back(renderer, FONT_PATH, FONT_SIZE, "Back", 255, 255, 255),
    introduceText(renderer, FONT_PATH, FONT_SIZE, "Introduzca el nombre del mapa", 255, 255, 255),
    mapName(renderer, FONT_PATH2, FONT_SIZE, "Nombre del mapa...", 255, 255, 255),
    quit(renderer, FONT_PATH, FONT_SIZE, "quit", 255, 255, 255){
    std::vector<std::string> vec = {CHUNK_PATH};
    this->chunk = std::unique_ptr<SdlMixer>(new SdlMixer(vec));
    this->editMap = false;
    this->createMap = false;
    this->changeScene = false;
    this->renderText = false;
    this->page = 0;
    this->createMapID = "Nombre del mapa...";

    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("../../common_src/maps/")) != NULL){
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL){
            if (ent->d_name[0] != '.'){
                files.emplace_back(ent->d_name);
            }
        }
        closedir (dir);
        delete ent;
    }
    parse(files);
    for (auto &file : files){
        this->editableMaps.emplace_back(renderer, FONT_PATH2, FONT_SIZE, file, 255, 255, 255);
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

void InitialMenu::render(){
    SDL_Rect screen = Presenter::getCameraBox();
    this->background.render(0, 0, screen.w, screen.h);
    this->quit.render(screen.w - quit.getWidth(), screen.h - quit.getHeight());
    if (editMap){
        int posY = screen.h/5, numerMap = 0;
        for (unsigned int i = page * MAPS_PER_PAGE; i < editableMaps.size(); i++){
            if (numerMap >= MAPS_PER_PAGE){
                break;
            }
            editableMaps[i].render((screen.w - editableMaps[i].getWidth())/2, posY);
            posY += 50;
            numerMap++;
        }
        this->arrow.render(screen.w/2 + 40, screen.h/5 + 50 * MAPS_PER_PAGE);
        this->arrow.renderFlip(screen.w/2 - arrow.getWidth() - 60, screen.h/5 + 50 * MAPS_PER_PAGE, SDL_FLIP_HORIZONTAL);
        this->back.render(0, screen.h - 20);
    }else if (createMap){
        if (renderText){
            if (this->createMapID == ""){
            this->mapName.changeTextTexture(" ", FONT_PATH2, FONT_SIZE, 255, 255, 255);
            }else{
                this->mapName.changeTextTexture(this->createMapID.c_str(), FONT_PATH2, FONT_SIZE, 255, 255, 255);
            }
        }
        this->introduceText.render((screen.w - introduceText.getWidth())/2, 50);
        this->mapName.render((screen.w - mapName.getWidth())/2, screen.h/2 - 100);
        this->back.render(0, screen.h - 20);
    }
    
    else{
        this->editarMapTexture.render((screen.w - editarMapTexture.getWidth())/2, screen.h/2 - 100);
        this->crearMapTexture.render((screen.w - crearMapTexture.getWidth())/2, screen.h/2);
    }
}

void InitialMenu::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    SDL_Rect screen = Presenter::getCameraBox();
    if (createMap){
        if (event->type == SDL_KEYDOWN){
            //Handle backspace
            if (event->key.keysym.sym == SDLK_BACKSPACE && this->createMapID.length() > 0){
                //lop off character
                this->createMapID.pop_back();
                this->renderText = true;
            }else if (event->key.keysym.sym == SDLK_RETURN){
                this->changeScene = true;
            }
        }else if (event->type == SDL_MOUSEBUTTONDOWN){
            if (event->button.button == SDL_BUTTON_LEFT){
                if(back.isMouseTouching(0, screen.h - 20)){
                    this->chunk->playChunk(0);
                    this->createMap = false;
                }else if (quit.isMouseTouching(screen.w - quit.getWidth(), screen.h - quit.getHeight())){
                    Presenter::quit();
                }
            }
        }
        //Special text input event
        else if (event->type == SDL_TEXTINPUT){
            //Append character
            this->createMapID += event->text.text;
            this->renderText = true;        
        }
    }else if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            if (quit.isMouseTouching(screen.w - quit.getWidth(), screen.h - quit.getHeight())){
                    Presenter::quit();
                }else if (editMap){
                if (arrow.isMouseTouching(screen.w/2 + 40, screen.h/5 + 50 * MAPS_PER_PAGE)){
                    this->chunk->playChunk(0);
                    if ((unsigned int) ((this->page + 1) * MAPS_PER_PAGE) < this->editableMaps.size()){
                        this->page++;
                    }
                }else if (arrow.isMouseTouching(screen.w/2 - arrow.getWidth() - 60, screen.h/5 + 50 * MAPS_PER_PAGE)){
                    this->chunk->playChunk(0);
                    if (this->page > 0){
                        this->page--;
                    }
                }else if(back.isMouseTouching(0, screen.h - 20)){
                    this->chunk->playChunk(0);
                    this->editMap = false;
                }else{
                    int posY = screen.h/5, position = page * MAPS_PER_PAGE, numerMap = 0;
                    for (unsigned int i = page * MAPS_PER_PAGE; i < editableMaps.size(); i++){
                        if (numerMap >= MAPS_PER_PAGE){
                            break;
                        }
                        if (editableMaps[i].isMouseTouching((screen.w - editableMaps[i].getWidth())/2, posY)){
                            this->chunk->playChunk(0);
                            this->changeScene = true;
                            this->mapPosition = position; 
                            break;
                        }
                        posY += 50;
                        position++;
                        numerMap++;
                    }
                }
            }else{
                if (this->editarMapTexture.isMouseTouching((screen.w - editarMapTexture.getWidth())/2, screen.h/2 - 100)){
                    this->chunk->playChunk(0);
                    this->editMap = true;
                }else if (this->crearMapTexture.isMouseTouching((screen.w - crearMapTexture.getWidth())/2, screen.h/2)){
                    this->chunk->playChunk(0);
                    this->createMap = true;
                }
            }
        }
    }
}

void InitialMenu::aceptChanges(){
    if (editMap){
        Presenter::editMap(this->mapsID[this->mapPosition]);
    }else if (createMap){
        Presenter::createMap(this->createMapID);
    }
}

bool InitialMenu::finish(){
    if (changeScene){
        changeScene = false;
        return true;
    }
    return false;
}

std::string InitialMenu::getTitle(){
    return "Menu";
}