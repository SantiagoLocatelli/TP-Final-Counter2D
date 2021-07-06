#include "OptionsMenue.h"
#include <string>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#define MIN_SIZE 100
#define MAX_SIZE 999
#define FONT_SIZE 26
#define FONT_PATH "../../common_src/img/digital-7.ttf"
#define BACKGROUND "../../common_src/img/counter.jpeg"
#define CHUNK_PATH "../../common_src/sound/pressButton.mp3"
OptionsMenue::OptionsMenue(SdlRenderer& renderer, std::map<std::string, std::shared_ptr<Draggable>>& bombSites,
 std::map<std::string, std::shared_ptr<Draggable>>& spawnSites,int screenW, int screenH)
  : Presenter(bombSites, spawnSites, screenW, screenH), backgroundTexture(renderer, BACKGROUND){
    std::vector<std::string> vec = {CHUNK_PATH};
    this->chunk = std::unique_ptr<SdlMixer>(new SdlMixer(vec));
    this->renderText = false;
    this->selectedTexture = NULL;
    std::vector<SDL_Rect> aux;
    std::vector<std::string> labels = {"Bomb A:", "Bomb B:", "T Spawn", "CT Spawn"};
    SdlMixer chunk();
    Presenter::fillSize(aux);
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
        this->widthTexture.emplace_back(renderer, FONT_PATH, FONT_SIZE, "WIDTH:", 255, 255, 255);
        this->heightTexture.emplace_back(renderer, FONT_PATH, FONT_SIZE, "HEIGHT:", 255, 255, 255);
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
            this->widthTexture[i/2].render(200, posY);
            this->heightTexture[i/2].render(400, posY);
            posX = 300;
        }
        this->inputOrder[i]->render(posX, posY);
        posX = 500;
    }
}

void OptionsMenue::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    int posY = 0;
    int posX = 300;
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            for (unsigned int i = 0; i < inputOrder.size(); i++){
                if (i % 2 == 0){
                    posY += 50;
                    posX = 300;
                }
                if (inputOrder[i]->isMouseTouching(posX, posY)){
                    if (selectedTexture != NULL){
                        this->selectedTexture->setColor(255, 255, 255);
                    }
                    this->selectedTexture = inputOrder[i];
                    this->selectedTexture->setColor(255, 255, 0);
                    this->chunk->playChunk(0);
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
            if (aux >= 48 && aux <= 57){
                //Append character
                inputText += event->text.text;
                this->renderText = true;
                this->options.at(this->selectedTexture) = inputText;
            }
        }
    }
}

void OptionsMenue::aceptChanges(){
    std::vector<int> vector;
    for (auto &input : inputOrder){
        std::string aux = this->options[input];
        if (aux.length() < 3){
            vector.push_back(MIN_SIZE);
        }else if (aux.length() > 3){
            vector.push_back(MAX_SIZE);
        }else{
            vector.push_back(std::stoi(aux, nullptr));
        }
    }
    Presenter::changeSizeOfSites(vector);
}

std::string OptionsMenue::getTitle(){
    return "Options OptionsMenue";
}