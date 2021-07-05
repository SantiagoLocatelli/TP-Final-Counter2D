#include "menue.h"
#include <string>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#define MIN_SIZE 100
#define MAX_SIZE 999
#define FONT_SIZE 26
Menue::Menue(SdlRenderer& renderer, std::map<std::string, std::shared_ptr<Draggable>>& bombSites,
 std::map<std::string, std::shared_ptr<Draggable>>& spawnSites,int screenW, int screenH)
  : Presenter(bombSites, spawnSites, screenW, screenH){
    this->renderText = false;
    this->selectedTexture = NULL;
    std::string fontPath("../../common_src/img/digital-7.ttf");
    std::vector<SDL_Rect> aux;
    Presenter::fillSize(aux);
    for (int i = 0; i < aux.size(); i++){
        std::string width = std::to_string(aux[i].w);
        std::string height = std::to_string(aux[i].h);
        std::shared_ptr<SdlTexture> textureWidth(new SdlTexture(renderer, fontPath, FONT_SIZE, width, 0, 0, 0));
        std::shared_ptr<SdlTexture> textureHeight(new SdlTexture(renderer, fontPath, FONT_SIZE, height, 0, 0, 0));
        this->inputOrder.push_back(textureWidth);
        this->inputOrder.push_back(textureHeight);
        this->options.emplace(std::move(textureWidth), width);
        this->options.emplace(std::move(textureHeight), height);
    }
}

void Menue::render(){
    if (this->renderText){
        std::string inputText = this->options[this->selectedTexture];
        if (inputText == ""){
            this->selectedTexture->changeTextTexture(" ", FONT_SIZE, 0, 0, 0);
        }else{
            this->selectedTexture->changeTextTexture(inputText.c_str(), FONT_SIZE, 0, 0, 0);
        }
        this->renderText = false;
    }
    int i = 0;
    for (auto input : inputOrder){
        input->render(100, i);
        i += 50;
    }
}

void Menue::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    int i = 0;
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            for (auto &input : inputOrder){
                if (input->isMouseTouching(100, i)){
                    this->selectedTexture = input;
                    break;
                }
                i += 50;
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

void Menue::aceptChanges(){
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

std::string Menue::getTitle(){
    return "Options Menue";
}