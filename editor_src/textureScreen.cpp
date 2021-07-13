#include "textureScreen.h"
#define FONT_PATH "../../common_src/img/digital-7.ttf"
#define BACKGROUND "../../common_src/img/counter.jpeg"
#define CHUNK_PATH "../../common_src/sound/pressButton.mp3"
#define FONT_SIZE 26
TextureScreen::TextureScreen(SdlRenderer& renderer, MenueManager& m ,int screenW, int screenH) : Presenter(m, screenW, screenH),
background(renderer, BACKGROUND), floors(renderer, FONT_PATH, FONT_SIZE, "Floors", 255, 255, 255),
walls(renderer, FONT_PATH, FONT_SIZE, "Walls", 255, 255, 255), back(renderer, FONT_PATH, FONT_SIZE, "Back", 0, 0, 0),
arrow(renderer, FONT_PATH, FONT_SIZE * 2, "->", 0, 0, 0){
    std::vector<std::string> vec = {CHUNK_PATH};
    this->chunk = std::unique_ptr<SdlMixer>(new SdlMixer(vec));
    this->changeScene = false;
    this->renderFloors = false;
    this->renderWalls = false;
    this->page = 0;
}

void TextureScreen::render(){
    SDL_Rect screen = Presenter::getCameraBox();
    if (renderFloors){
        back.render(0, screen.h - 20);
        this->arrow.render(screen.w - 40, Presenter::getTileSize() * 2);
        this->arrow.renderFlip(0, Presenter::getTileSize() * 2, SDL_FLIP_HORIZONTAL);
        Presenter::renderMapFloors(page);
    }else if (renderWalls){
        back.render(0,screen.h - 20);
        this->arrow.render(screen.w - 40, Presenter::getTileSize() * 2);
        this->arrow.renderFlip(0, Presenter::getTileSize() * 2, SDL_FLIP_HORIZONTAL);
        Presenter::renderMapWalls(page);
    }else{
        this->background.render(0, 0, screen.w, screen.h);
        this->floors.render(screen.w/2, screen.h/3);
        this->walls.render(screen.w/3, screen.h/3);
    }
}

void TextureScreen::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    SDL_Rect screen = Presenter::getCameraBox();
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0){
        if (event->key.keysym.sym == SDLK_TAB){
            this->changeScene = true;
        }
    }else if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            if (renderFloors){
                Presenter::handleFloorsTexture(event, this->page);
                if (back.isMouseTouching(0,screen.h - 20)){
                    this->chunk->playChunk(0);
                    renderFloors = false;
                }else if (arrow.isMouseTouching(screen.w - 40, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    page++;
                }else if (arrow.isMouseTouching(0, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    if (this->page > 0){
                        this->page--;
                    }
                }
            }else if (renderWalls){
                Presenter::handleWallsTexture(event, this->page);
                if (back.isMouseTouching(0,screen.h - 20)){
                    this->chunk->playChunk(0);
                    renderWalls = false;
                }else if (arrow.isMouseTouching(screen.w - 40, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    page++;
                }else if (arrow.isMouseTouching(0, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    if (this->page > 0){
                        this->page--;
                    }
                }
            }else if (floors.isMouseTouching(screen.w/2, screen.h/3)){
                this->chunk->playChunk(0);
                renderFloors = true;
            }else if (walls.isMouseTouching(screen.w/3, screen.h/3)){
                this->chunk->playChunk(0);
                renderWalls = true;
            }
        }
    }
}

void TextureScreen::aceptChanges(){}

std::string TextureScreen::getTitle(){
    return "Select Texture";
}

bool TextureScreen::finish(){
    if (changeScene){
        changeScene = false;
        return true;
    }
    return false;
}