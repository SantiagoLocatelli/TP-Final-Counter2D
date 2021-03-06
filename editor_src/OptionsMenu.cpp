#include "OptionsMenu.h"
#include <string>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#define BLANCK_SPACE 50
enum keyForMap : int {WIDTH, HEIGHT, SAVE_MAP, BACK, QUIT_TO_MENU, QUIT, BOMB_SITES, ARROW, NUMBRE_BOMBS};

OptionsMenu::OptionsMenu(SdlRenderer& renderer, MenuManager& m ,int screenW, int screenH)
  : Presenter(m, screenW, screenH), backgroundTexture(renderer, BACKGROUND){
    std::vector<std::string> text = {"WIDTH", "HEIGHT", "Save Map", "Back", "Go back to Menu", "Quit", "Bomb Sites:", "->"};
    for (unsigned int i = 0; i < text.size(); i++){
        if (i == ARROW){
           menuTextures.emplace(i, SdlTexture(renderer, FONT_PATH, FONT_SIZE * 2, text[i], 255, 255, 255)); 
        }else{
            menuTextures.emplace(i, SdlTexture(renderer, FONT_PATH, FONT_SIZE, text[i], 255, 255, 255));
        }
    }
    std::vector<std::string> vec = {CHUNK_PATH};
    this->chunk = std::unique_ptr<SdlMixer>(new SdlMixer(vec));
    this->changeScene = false;
    this->renderText = false;
    this->selectedTexture = NULL;
    std::vector<SDL_Rect> aux;
    Presenter::fillSize(aux);
    std::vector<std::string> labels = {"Map Size:", "Spawn T:", "Spawn CT:", "Bomb A:", "Bomb B:"};
    if (aux.size() == 5){
        this->numberOfBombs = 2;
    }else{
        this->numberOfBombs = 1;
    }
    for (unsigned int i = 0; i < aux.size(); i++){
        std::string width = std::to_string(aux[i].w);
        std::string height = std::to_string(aux[i].h);
        std::shared_ptr<SdlTexture> textureWidth(new SdlTexture(renderer, FONT_PATH, FONT_SIZE, width, 255, 255, 255));
        std::shared_ptr<SdlTexture> textureHeight(new SdlTexture(renderer, FONT_PATH, FONT_SIZE, height, 255, 255, 255));
        this->inputOrder.push_back(textureWidth);
        this->inputOrder.push_back(textureHeight);
        this->options.emplace(std::move(textureWidth), width);
        this->options.emplace(std::move(textureHeight), height);

        this->textTexture.emplace_back(renderer, FONT_PATH, FONT_SIZE, labels[i], 255, 255, 255);
    }
    menuTextures.emplace(NUMBRE_BOMBS, SdlTexture(renderer, FONT_PATH, FONT_SIZE, std::to_string(this->numberOfBombs), 255, 255, 255));
}

void OptionsMenu::render(){
    if (this->renderText){
        std::string inputText = this->options[this->selectedTexture];
        if (inputText == ""){
            this->selectedTexture->changeTextTexture(" ", FONT_PATH, FONT_SIZE, 255, 255, 255);
        }else{
            this->selectedTexture->changeTextTexture(inputText.c_str(), FONT_PATH, FONT_SIZE, 255, 255, 255);
        }
        this->selectedTexture->setColor(255,255,0);
        this->renderText = false;
        Presenter::needToSave();
    }
    int posY = 0;
    int posX = 0;
    SDL_Rect screen = Presenter::getCameraBox();
    this->backgroundTexture.render(0, 0, screen.w, screen.h);
    this->menuTextures.at(SAVE_MAP).render(screen.w - 100, 0);
    this->menuTextures.at(BACK).render(0, screen.h - 20);
    this->menuTextures.at(QUIT).render(screen.w - menuTextures.at(QUIT).getWidth(), screen.h - menuTextures.at(QUIT).getHeight());
    this->menuTextures.at(QUIT_TO_MENU).render(0,0);
    for (unsigned int i = 0; i < inputOrder.size(); i++){
        if (i % 2 == 0){
            posY += 50;
            this->textTexture[i/2].render((screen.w - textTexture[i/2].getWidth())/2 - menuTextures.at(WIDTH).getWidth()*2 - BLANCK_SPACE*2, posY);
            this->menuTextures.at(WIDTH).render((screen.w - menuTextures.at(WIDTH).getWidth())/2 - menuTextures.at(WIDTH).getWidth() - BLANCK_SPACE, posY);
            this->menuTextures.at(HEIGHT).render((screen.w - menuTextures.at(HEIGHT).getWidth())/2 + menuTextures.at(HEIGHT).getWidth() + BLANCK_SPACE, posY);
            posX = (screen.w - menuTextures.at(HEIGHT).getWidth())/2;
        }
        this->inputOrder[i]->render(posX, posY);
        posX = (screen.w - menuTextures.at(HEIGHT).getWidth())/2 + menuTextures.at(HEIGHT).getWidth()*2 + BLANCK_SPACE*2;
    }
    this->menuTextures.at(BOMB_SITES).render((screen.w - menuTextures.at(BOMB_SITES).getWidth())/2 - BLANCK_SPACE*4, posY + 50);
    this->menuTextures.at(ARROW).renderFlip((screen.w - menuTextures.at(ARROW).getWidth())/2 - BLANCK_SPACE*2, posY + 40, SDL_FLIP_HORIZONTAL);
    this->menuTextures.at(NUMBRE_BOMBS).render((screen.w - menuTextures.at(NUMBRE_BOMBS).getWidth())/2 - BLANCK_SPACE*1, posY + 50);
    this->menuTextures.at(ARROW).render((screen.w - menuTextures.at(ARROW).getWidth())/2, posY + 40);
}

void OptionsMenu::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    int posY = 0, posX;
    if (event->type == SDL_KEYDOWN){
        if(event->key.keysym.sym == SDLK_ESCAPE && event->key.repeat == 0){
            this->changeScene = true;
        }
    }
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            SDL_Rect screen = Presenter::getCameraBox();
            if (menuTextures.at(SAVE_MAP).isMouseTouching(screen.w - 100, 0)){
                this->chunk->playChunk(0);
                Presenter::saveMap();
            }else if (menuTextures.at(BACK).isMouseTouching(0, screen.h - 20)){
                this->chunk->playChunk(0);
                this->changeScene = true;
            }else if (menuTextures.at(QUIT_TO_MENU).isMouseTouching(0, 0)){
                Presenter::goToMenu();
                this->changeScene = true;
            }else if (menuTextures.at(QUIT).isMouseTouching(screen.w - menuTextures.at(QUIT).getWidth(), screen.h - 20)){
                Presenter::quit();
            }else{
                for (unsigned int i = 0; i < inputOrder.size(); i++){
                    if (i % 2 == 0){
                        posY += 50;
                        posX = (screen.w - menuTextures.at(HEIGHT).getWidth())/2;
                    }
                    if (inputOrder[i]->isMouseTouching(posX, posY)){
                        this->chunk->playChunk(0);
                        if (selectedTexture != NULL){
                            this->selectedTexture->setColor(255, 255, 255);
                        }
                        this->selectedTexture = inputOrder[i];
                        this->selectedTexture->setColor(255, 255, 0);
                        break;
                    }
                    posX = (screen.w - menuTextures.at(HEIGHT).getWidth())/2 + menuTextures.at(HEIGHT).getWidth()*2 + BLANCK_SPACE*2;
                }
            }if (menuTextures.at(ARROW).isMouseTouching((screen.w - menuTextures.at(ARROW).getWidth())/2 - BLANCK_SPACE*2, posY + 40)){
                this->chunk->playChunk(0);
                this->numberOfBombs = 1;
                this->menuTextures.at(NUMBRE_BOMBS).changeTextTexture("1", FONT_PATH, FONT_SIZE, 255, 255, 255);
            }else if (menuTextures.at(ARROW).isMouseTouching((screen.w - menuTextures.at(ARROW).getWidth())/2, posY + 40)){
                this->chunk->playChunk(0);
                this->numberOfBombs = 2;
                this->menuTextures.at(NUMBRE_BOMBS).changeTextTexture("2", FONT_PATH, FONT_SIZE, 255, 255, 255);
            }
        }
    }else if (selectedTexture != NULL){
        std::string inputText = this->options[this->selectedTexture];
        if (event->type == SDL_KEYDOWN){
            //Handle backspace
            if (event->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0){
                //lop off character
                inputText.pop_back();
                this->renderText = true;
                this->options.at(this->selectedTexture) = inputText;
            }
        }
        //Special text input event
        else if (event->type == SDL_TEXTINPUT){
            char aux = event->text.text[0];
            if ((aux >= 48 && aux <= 57) || aux == 46){
                //Append character
                inputText += event->text.text;
                this->renderText = true;
                this->options.at(this->selectedTexture) = inputText;
            }
        }
    }
}

void OptionsMenu::aceptChanges(){
    std::vector<float> vector;
    int i = 0;
    for (auto &input : inputOrder){
        std::string aux = this->options[input];
        if (i > 1){
            if (aux.length() < 1 || aux[0] == '.'){
                vector.push_back(MIN_SIZE);
            }else{
                float value = std::stof(aux, nullptr);
                if (value > MAX_SIZE){
                    value = MAX_SIZE;
                }else if (value < MIN_SIZE){
                    value = MIN_SIZE;
                }
                vector.push_back(value);
            }
        }else{
            int sizeOfMap = MIN_MAP_SIZE;
            if (aux.length() != 0){
                sizeOfMap = std::stof(aux, nullptr);
                if (sizeOfMap > MAX_MAP_SIZE){
                    sizeOfMap = MAX_MAP_SIZE;
                }else if (sizeOfMap < MIN_MAP_SIZE){
                    sizeOfMap = MIN_MAP_SIZE;
                }
            }
            vector.push_back((int) sizeOfMap);
        }
        i++;
    }
    Presenter::changeSizeOfSites(vector);
    Presenter::putBombSites(this->numberOfBombs);
}

bool OptionsMenu::finish(){
    if (changeScene){
        changeScene = false;
        return true;
    }
    return false;
}

std::string OptionsMenu::getTitle(){
    return "Options OptionsMenu";
}