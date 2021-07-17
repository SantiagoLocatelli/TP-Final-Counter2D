#include "textureScreen.h"
#define FONT_PATH "../../common_src/img/digital-7.ttf"
#define BACKGROUND "../../common_src/img/counter.jpeg"
#define CHUNK_PATH "../../common_src/sound/pressButton.mp3"
TextureScreen::TextureScreen(SdlRenderer& renderer, MenuManager& m ,int screenW, int screenH) : Presenter(m, screenW, screenH),
background(renderer, BACKGROUND), floors(renderer, FONT_PATH, FONT_SIZE, "Floors", 255, 255, 255),
walls(renderer, FONT_PATH, FONT_SIZE, "Walls", 255, 255, 255), back(renderer, FONT_PATH, FONT_SIZE, "Back", 0, 0, 0),
weapons(renderer, FONT_PATH, FONT_SIZE, "Weapons", 255, 255, 255), arrow(renderer, FONT_PATH, FONT_SIZE * 2, "->", 0, 0, 0),
backToEditor(renderer, FONT_PATH, FONT_SIZE, "Back to Editor", 0, 0, 0){
    std::vector<std::string> vec = {CHUNK_PATH};
    this->chunk = std::unique_ptr<SdlMixer>(new SdlMixer(vec));
    this->changeScene = false;
    this->renderFloors = false;
    this->renderWalls = false;
    this->renderWeapons = false;
    this->page = 0;
}

void TextureScreen::render(){
    SDL_Rect screen = Presenter::getCameraBox();
    if (renderFloors){
        this->arrow.render(screen.w - 40, Presenter::getTileSize() * 2);
        this->arrow.renderFlip(0, Presenter::getTileSize() * 2, SDL_FLIP_HORIZONTAL);
        this->backToEditor.render(screen.w - backToEditor.getWidth(), screen.h - 20);
        Presenter::renderMapFloors(page);
    }else if (renderWalls){
        this->arrow.render(screen.w - 40, Presenter::getTileSize() * 2);
        this->arrow.renderFlip(0, Presenter::getTileSize() * 2, SDL_FLIP_HORIZONTAL);
        this->backToEditor.render(screen.w - backToEditor.getWidth(), screen.h - 20);
        Presenter::renderMapWalls(page);
    }else if (renderWeapons){
        this->arrow.render(screen.w - 40, Presenter::getTileSize() * 2);
        this->arrow.renderFlip(0, Presenter::getTileSize() * 2, SDL_FLIP_HORIZONTAL);
        this->backToEditor.render(screen.w - backToEditor.getWidth(), screen.h - 20);
        Presenter::renderMapWeapons(page);
    }
    else{
        this->background.render(0, 0, screen.w, screen.h);
        this->floors.render((screen.w - floors.getWidth())/2, (screen.h - floors.getHeight())/2 - 100);
        this->walls.render((screen.w - walls.getWidth())/2, (screen.h - walls.getHeight())/2);
        this->weapons.render((screen.w - weapons.getWidth())/2, (screen.h - weapons.getHeight())/2 + 100);
    }
    this->back.render(0, screen.h - 20);
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
                }else if (backToEditor.isMouseTouching(screen.w - backToEditor.getWidth(), screen.h - 20)){
                    this->chunk->playChunk(0);
                    changeScene = true;
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
                }else if (backToEditor.isMouseTouching(screen.w - backToEditor.getWidth(), screen.h - 20)){
                    this->chunk->playChunk(0);
                    changeScene = true;
                }
            }else if (renderWeapons){
                Presenter::handleWeaponsTexture(event, this->page);
                if (back.isMouseTouching(0,screen.h - 20)){
                    this->chunk->playChunk(0);
                    renderWeapons = false;
                }else if (arrow.isMouseTouching(screen.w - 40, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    page++;
                }else if (arrow.isMouseTouching(0, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    if (this->page > 0){
                        this->page--;
                    }
                }else if (backToEditor.isMouseTouching(screen.w - backToEditor.getWidth(), screen.h - 20)){
                    this->chunk->playChunk(0);
                    changeScene = true;
                }
            }else if (weapons.isMouseTouching((screen.w - weapons.getWidth())/2, (screen.h - weapons.getHeight())/2 + 100)){
                this->chunk->playChunk(0);
                renderWeapons = true;
            }else if (floors.isMouseTouching((screen.w - floors.getWidth())/2, (screen.h - floors.getHeight())/2 - 100)){
                this->chunk->playChunk(0);
                renderFloors = true;
            }else if (walls.isMouseTouching((screen.w - walls.getWidth())/2, (screen.h - walls.getHeight())/2)){
                this->chunk->playChunk(0);
                renderWalls = true;
            }else if (back.isMouseTouching(0, screen.h - 20)){
                this->chunk->playChunk(0);
                this->changeScene = true;
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