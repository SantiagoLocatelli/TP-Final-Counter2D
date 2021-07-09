#include "InitialMenue.h"
#define FONT_PATH "../../common_src/img/digital-7.ttf"
#define BACKGROUND "../../common_src/img/counter.jpeg"
#define CHUNK_PATH "../../common_src/sound/pressButton.mp3"
#define FONT_SIZE 26
InitialMenue::InitialMenue(SdlRenderer& renderer, MenueManager& m ,int screenW, int screenH) : 
    Presenter(m, screenW, screenH), background(renderer, BACKGROUND),
    crearMapTexture(renderer, FONT_PATH, FONT_SIZE, "Crear Mapa", 255, 255, 255),
    editarMapTexture(renderer, FONT_PATH, FONT_SIZE, "Editar Mapa", 255, 255, 255){
        std::vector<std::string> vec = {CHUNK_PATH};
        this->chunk = std::unique_ptr<SdlMixer>(new SdlMixer(vec));
        this->editMap = false;
        this->createMap = false;
    }


void InitialMenue::render(){
    SDL_Rect screen = Presenter::getCameraBox();
    this->background.render(0, 0, screen.w, screen.h);
    this->editarMapTexture.render(250, 100);
    this->crearMapTexture.render(250, 200);
}

void InitialMenue::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
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

void InitialMenue::aceptChanges(){
    if (editMap){
        Presenter::editMap();
    }else if (createMap){
        Presenter::createMap();
    }
}

bool InitialMenue::finish(){
    if (editMap){
        return true;
    }if (createMap){
        return true;
    }
    return false;
}

std::string InitialMenue::getTitle(){
    return "Menue";
}