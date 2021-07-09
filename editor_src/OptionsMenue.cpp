#include "OptionsMenue.h"
#include <string>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#define MIN_MAP_SIZE 5
#define MAX_MAP_SIZE 30
#define MIN_SIZE 1
#define MAX_SIZE 5
#define FONT_SIZE 26
#define FONT_PATH "../../common_src/img/digital-7.ttf"
#define BACKGROUND "../../common_src/img/counter.jpeg"
#define CHUNK_PATH "../../common_src/sound/pressButton.mp3"
OptionsMenue::OptionsMenue(SdlRenderer& renderer, MenueManager& m ,int screenW, int screenH)
  : Presenter(m, screenW, screenH), backgroundTexture(renderer, BACKGROUND),
    widthTexture(renderer, FONT_PATH, FONT_SIZE, "WIDTH:", 255, 255, 255),
    heightTexture(renderer, FONT_PATH, FONT_SIZE, "HEIGHT:", 255, 255, 255){
    this->changeScene = false;
    std::vector<std::string> vec = {CHUNK_PATH};
    this->chunk = std::unique_ptr<SdlMixer>(new SdlMixer(vec));
    this->renderText = false;
    this->selectedTexture = NULL;
    std::vector<SDL_Rect> aux;
    Presenter::fillSize(aux);
    std::vector<std::string> labels = {"Map Size:", "Bomb A:", "Bomb B:", "T Spawn", "CT Spawn"};
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
}

void OptionsMenue::render(){
    if (this->renderText){
        std::string inputText = this->options[this->selectedTexture];
        if (inputText == ""){
            this->selectedTexture->changeTextTexture(" ", FONT_SIZE, 255, 255, 255);
        }else{
            this->selectedTexture->changeTextTexture(inputText.c_str(), FONT_SIZE, 255, 255, 255);
        }
        this->selectedTexture->setColor(255,255,0);
        this->renderText = false;
    }
    int posY = 0;
    int posX = 0;
    SDL_Rect screen = Presenter::getCameraBox();
    this->backgroundTexture.render(0, 0, screen.w, screen.h);
    for (unsigned int i = 0; i < inputOrder.size(); i++){
        if (i % 2 == 0){
            posY += 50;
            this->textTexture[i/2].render(100, posY);
            this->widthTexture.render(200, posY);
            this->heightTexture.render(400,posY);
            posX = 300;
        }
        this->inputOrder[i]->render(posX, posY);
        posX = 500;
    }
}

void OptionsMenue::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    int posY = 0;
    int posX = 300;
    if (event->type == SDL_KEYDOWN){
        if(event->key.keysym.sym == SDLK_ESCAPE){
            this->changeScene = true;
        }
    }
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            for (unsigned int i = 0; i < inputOrder.size(); i++){
                if (i % 2 == 0){
                    posY += 50;
                    posX = 300;
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
                posX = 500;
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

void OptionsMenue::aceptChanges(){
    std::vector<float> vector;
    int i = 0;
    for (auto &input : inputOrder){
        std::string aux = this->options[input];
        if (i > 1){
            if (aux.length() < 1 || aux == "."){
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
}

bool OptionsMenue::finish(){
    if (changeScene){
        changeScene = false;
        return true;
    }
    return false;
}

std::string OptionsMenue::getTitle(){
    return "Options OptionsMenue";
}