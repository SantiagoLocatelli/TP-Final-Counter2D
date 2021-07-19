#include "textureScreen.h"
#define FONT_PATH "/usr/local/share/counter2d/resources/common/img/digital-7.ttf"
#define BACKGROUND "/usr/local/share/counter2d/resources/common/img/counter.jpeg"
#define CHUNK_PATH "/usr/local/share/counter2d/resources/common/sound/pressButton.mp3"

enum keyForMap : int {FLOORS, WALLS, BACK, WEAPONS, ARROW, BACK_TO_EDITOR};

TextureScreen::TextureScreen(SdlRenderer& renderer, MenuManager& m ,int screenW, int screenH) : Presenter(m, screenW, screenH),
background(renderer, BACKGROUND){
    std::vector<std::string> text = {"Floors", "Walls", "Back", "Weapons", "->", "Back to Editor"};
    for (unsigned int i = 0; i < text.size(); i++){
        if (text[i] == "Floors" || text[i] == "Walls" || text[i] == "Weapons"){
            menuTextures.emplace(i, SdlTexture(renderer, FONT_PATH, FONT_SIZE, text[i], 255, 255, 255));
        }else if (text[i] == "->"){
            menuTextures.emplace(i, SdlTexture(renderer, FONT_PATH, FONT_SIZE * 2, text[i], 0, 0, 0));
        }
        else{
            menuTextures.emplace(i, SdlTexture(renderer, FONT_PATH, FONT_SIZE, text[i], 0, 0, 0));
        }
    }
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
    if (renderFloors || renderWalls || renderWeapons){
        this->menuTextures.at(ARROW).render(screen.w - 40, Presenter::getTileSize() * 2);
        this->menuTextures.at(ARROW).renderFlip(0, Presenter::getTileSize() * 2, SDL_FLIP_HORIZONTAL);
        this->menuTextures.at(BACK_TO_EDITOR).render(screen.w - menuTextures.at(BACK_TO_EDITOR).getWidth(), screen.h - 20);
    }
    if (renderFloors){
        Presenter::renderMapFloors(page);
    }else if (renderWalls){
        Presenter::renderMapWalls(page);
    }else if (renderWeapons){
        Presenter::renderMapWeapons(page);
    }
    else{
        this->background.render(0, 0, screen.w, screen.h);
        this->menuTextures.at(FLOORS).render((screen.w - menuTextures.at(FLOORS).getWidth())/2, (screen.h - menuTextures.at(FLOORS).getHeight())/2 - 100);
        this->menuTextures.at(WALLS).render((screen.w - menuTextures.at(WALLS).getWidth())/2, (screen.h - menuTextures.at(WALLS).getHeight())/2);
        this->menuTextures.at(WEAPONS).render((screen.w - menuTextures.at(WEAPONS).getWidth())/2, (screen.h - menuTextures.at(WEAPONS).getHeight())/2 + 100);
    }
    this->menuTextures.at(BACK).render(0, screen.h - 20);
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
                if (menuTextures.at(BACK).isMouseTouching(0,screen.h - 20)){
                    this->chunk->playChunk(0);
                    renderFloors = false;
                }else if (menuTextures.at(ARROW).isMouseTouching(screen.w - 40, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    page++;
                }else if (menuTextures.at(ARROW).isMouseTouching(0, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    if (this->page > 0){
                        this->page--;
                    }
                }else if (menuTextures.at(BACK_TO_EDITOR).isMouseTouching(screen.w - menuTextures.at(BACK_TO_EDITOR).getWidth(), screen.h - 20)){
                    this->chunk->playChunk(0);
                    changeScene = true;
                }
            }else if (renderWalls){
                Presenter::handleWallsTexture(event, this->page);
                if (menuTextures.at(BACK).isMouseTouching(0,screen.h - 20)){
                    this->chunk->playChunk(0);
                    renderWalls = false;
                }else if (menuTextures.at(ARROW).isMouseTouching(screen.w - 40, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    page++;
                }else if (menuTextures.at(ARROW).isMouseTouching(0, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    if (this->page > 0){
                        this->page--;
                    }
                }else if (menuTextures.at(BACK_TO_EDITOR).isMouseTouching(screen.w - menuTextures.at(BACK_TO_EDITOR).getWidth(), screen.h - 20)){
                    this->chunk->playChunk(0);
                    changeScene = true;
                }
            }else if (renderWeapons){
                Presenter::handleWeaponsTexture(event, this->page);
                if (menuTextures.at(BACK).isMouseTouching(0,screen.h - 20)){
                    this->chunk->playChunk(0);
                    renderWeapons = false;
                }else if (menuTextures.at(ARROW).isMouseTouching(screen.w - 40, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    page++;
                }else if (menuTextures.at(ARROW).isMouseTouching(0, Presenter::getTileSize() * 2)){
                    this->chunk->playChunk(0);
                    if (this->page > 0){
                        this->page--;
                    }
                }else if (menuTextures.at(BACK_TO_EDITOR).isMouseTouching(screen.w - menuTextures.at(BACK_TO_EDITOR).getWidth(), screen.h - 20)){
                    this->chunk->playChunk(0);
                    changeScene = true;
                }
            }else if (menuTextures.at(WEAPONS).isMouseTouching((screen.w - menuTextures.at(WEAPONS).getWidth())/2, (screen.h - menuTextures.at(WEAPONS).getHeight())/2 + 100)){
                this->chunk->playChunk(0);
                renderWeapons = true;
            }else if (menuTextures.at(FLOORS).isMouseTouching((screen.w - menuTextures.at(FLOORS).getWidth())/2, (screen.h - menuTextures.at(FLOORS).getHeight())/2 - 100)){
                this->chunk->playChunk(0);
                renderFloors = true;
            }else if (menuTextures.at(WALLS).isMouseTouching((screen.w - menuTextures.at(WALLS).getWidth())/2, (screen.h - menuTextures.at(WALLS).getHeight())/2)){
                this->chunk->playChunk(0);
                renderWalls = true;
            }else if (menuTextures.at(BACK).isMouseTouching(0, screen.h - 20)){
                this->chunk->playChunk(0);
                this->changeScene = true;
            }
        }
    }
}

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