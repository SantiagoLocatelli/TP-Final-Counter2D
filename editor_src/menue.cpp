#include "menue.h"
#include <string>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#define MIN_SIZE "100"
#define MAX_SIZE "999"
#define FONT_SIZE 26
Menue::Menue(const std::string path, SdlRenderer& renderer, int screenW, int screenH) : Presenter(path, renderer, screenW, screenH){
    this->renderText = false;
    this->selectedTexture = NULL;
    std::string fontPath("../../common_src/img/digital-7.ttf");
    std::vector<SDL_Rect> aux;
    Presenter::fillSize(aux);
    for (int i = 0; i < aux.size(); i++){
        std::string width = std::to_string(aux[i].w);
        printf("%s: ", width.c_str());
        width.pop_back();
        printf("%s\n", width.c_str());
        std::string height = std::to_string(aux[i].h);
        this->options.emplace(new SdlTexture(renderer, fontPath, FONT_SIZE, width, 0, 0, 0), width);
        this->options.emplace(new SdlTexture(renderer, fontPath, FONT_SIZE, height, 0, 0, 0), height);
    }
}

void Menue::render(){
    if (this->renderText){
        std::string inputText = this->options[this->selectedTexture];
        if (inputText != ""){
            this->selectedTexture->changeTextTexture(" ", FONT_SIZE, 0, 0, 0);
        }else{
            this->selectedTexture->changeTextTexture(inputText.c_str(), FONT_SIZE, 0, 0, 0);
        }
    }
    int i = 0;
    for (auto &texture : this->options){
        texture.first->render(100, i);
        i += 50;
    }
}

void Menue::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    int i = 0;
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            for (auto &option : options){
                if (option.first->isMouseTouching(100, i)){
                    this->selectedTexture = option.first;
                    break;
                }
                i += 50;
            }
        }
    }else if (selectedTexture != NULL){ 
        SDL_StartTextInput();
        std::string inputText = this->options[this->selectedTexture];
        if (event->type == SDL_KEYDOWN){
            //Handle backspace
            if (event->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0){
                //lop off character
                inputText.pop_back();
                this->renderText = true;
                this->options.at(this->selectedTexture) = inputText;
            }
            //Special text input event
			else if (event->type == SDL_TEXTINPUT){
                int aux = atoi(event->text.text);
                if ( aux > 48 || aux < 57){
                    //Append character
                    inputText += event->text.text;
                    this->renderText = true;
                    this->options.at(this->selectedTexture) = inputText;
                }
            }
        }
    }
}

std::string Menue::getTitle(){
    return "Options Menue";
}