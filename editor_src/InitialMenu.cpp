#include "InitialMenu.h"
#include <dirent.h>
#include <algorithm>
#define MAPS_PER_PAGE 5
enum keyForMap : int {CREATE_MAP, EDIT_MAP, ARROW, BACK, INTRODUCE_TEXT, MAP_NAME, QUIT};
static void parse(std::vector<std::string>& files);

InitialMenu::InitialMenu(SdlRenderer& renderer, MenuManager& m ,int screenW, int screenH) : 
    Presenter(m, screenW, screenH), background(renderer, BACKGROUND){
    std::vector<std::string> aux = {"Create Map", "Edit Map", "->",
     "Back", "Type map name", "newMap", "quit"};
    for (unsigned int i = 0; i < aux.size(); i++){
        if (i == ARROW){
            menuTextures.emplace(i, SdlTexture(renderer, FONT_PATH, FONT_SIZE * 2, aux[i], 255, 255, 255));    
        }else if (i == MAP_NAME){
            menuTextures.emplace(i, SdlTexture(renderer, FONT_PATH2, FONT_SIZE, aux[i], 255, 255, 255));
        }else{
            menuTextures.emplace(i, SdlTexture(renderer, FONT_PATH, FONT_SIZE, aux[i], 255, 255, 255));
        }
    }
    std::vector<std::string> vec = {CHUNK_PATH};
    this->chunk = std::unique_ptr<SdlMixer>(new SdlMixer(vec));
    this->editMap = false;
    this->createMap = false;
    this->changeScene = false;
    this->renderText = false;
    this->page = 0;
    this->createMapID = aux[MAP_NAME];

    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (MAPS_DIR)) != NULL){
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
        this->mapsID.emplace_back(MAPS_DIR + file + ".yaml");
    }
}

static void parse(std::vector<std::string>& files){
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
    this->menuTextures.at(QUIT).render(screen.w - menuTextures.at(QUIT).getWidth(), screen.h - menuTextures.at(QUIT).getHeight());
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
        this->menuTextures.at(ARROW).render(screen.w/2 + 40, screen.h/5 + 50 * MAPS_PER_PAGE);
        this->menuTextures.at(ARROW).renderFlip(screen.w/2 - menuTextures.at(ARROW).getWidth() - 60, screen.h/5 + 50 * MAPS_PER_PAGE, SDL_FLIP_HORIZONTAL);
        this->menuTextures.at(BACK).render(0, screen.h - 20);
    }else if (createMap){
        if (renderText){
            if (this->createMapID == ""){
            this->menuTextures.at(MAP_NAME).changeTextTexture(" ", FONT_PATH2, FONT_SIZE, 255, 255, 255);
            }else{
                this->menuTextures.at(MAP_NAME).changeTextTexture(this->createMapID.c_str(), FONT_PATH2, FONT_SIZE, 255, 255, 255);
            }
        }
        this->menuTextures.at(INTRODUCE_TEXT).render((screen.w - menuTextures.at(INTRODUCE_TEXT).getWidth())/2, 50);
        this->menuTextures.at(MAP_NAME).render((screen.w - menuTextures.at(MAP_NAME).getWidth())/2, screen.h/2 - 100);
        this->menuTextures.at(BACK).render(0, screen.h - 20);
    }
    
    else{
        this->menuTextures.at(EDIT_MAP).render((screen.w - menuTextures.at(EDIT_MAP).getWidth())/2, screen.h/2 - 100);
        this->menuTextures.at(CREATE_MAP).render((screen.w - menuTextures.at(CREATE_MAP).getWidth())/2, screen.h/2);
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
                if(menuTextures.at(BACK).isMouseTouching(0, screen.h - 20)){
                    this->chunk->playChunk(0);
                    this->createMap = false;
                }else if (menuTextures.at(QUIT).isMouseTouching(screen.w - menuTextures.at(QUIT).getWidth(), screen.h - menuTextures.at(QUIT).getHeight())){
                    Presenter::quit();
                }
            }
        }
        //Special text input event
        else if (event->type == SDL_TEXTINPUT){
            if (event->text.text[0] != 32){
                //Append character
                this->createMapID += event->text.text;
                this->renderText = true;
            }
        }
    }else if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            if (menuTextures.at(QUIT).isMouseTouching(screen.w - menuTextures.at(QUIT).getWidth(), screen.h - menuTextures.at(QUIT).getHeight())){
                    Presenter::quit();
                }else if (editMap){
                if (menuTextures.at(ARROW).isMouseTouching(screen.w/2 + 40, screen.h/5 + 50 * MAPS_PER_PAGE)){
                    this->chunk->playChunk(0);
                    if ((unsigned int) ((this->page + 1) * MAPS_PER_PAGE) < this->editableMaps.size()){
                        this->page++;
                    }
                }else if (menuTextures.at(ARROW).isMouseTouching(screen.w/2 - menuTextures.at(ARROW).getWidth() - 60, screen.h/5 + 50 * MAPS_PER_PAGE)){
                    this->chunk->playChunk(0);
                    if (this->page > 0){
                        this->page--;
                    }
                }else if(menuTextures.at(BACK).isMouseTouching(0, screen.h - 20)){
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
                if (this->menuTextures.at(EDIT_MAP).isMouseTouching((screen.w - menuTextures.at(EDIT_MAP).getWidth())/2, screen.h/2 - 100)){
                    this->chunk->playChunk(0);
                    this->editMap = true;
                }else if (this->menuTextures.at(CREATE_MAP).isMouseTouching((screen.w - menuTextures.at(CREATE_MAP).getWidth())/2, screen.h/2)){
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