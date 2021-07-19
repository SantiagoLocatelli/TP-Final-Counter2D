#include "IpMenu.h"
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FONT_PATH "../../common_src/img/digital-7.ttf"
#define FONT_PATH2 "../../common_src/img/aerial.ttf"
#define BACKGROUND "../../common_src/img/counter.jpeg"
#define FONT_SIZE 26
#define FONT_SIZE_TYPE 20

const struct Color WHITE = {0xFF, 0xFF, 0xFF};
enum TextTextureType : int {PUT_TEXT, VARIABLE_TEXT};

IpMenu::IpMenu():window("IpMenu", SCREEN_WIDTH, SCREEN_HEIGHT),
    renderer(&window), background(renderer, BACKGROUND){
    this->renderText = false;
    this->variableText = " ";
    this->ip = "";
    this->port = "";

    this->map.emplace(PUT_TEXT, new TextTexture(renderer, FONT_PATH, FONT_SIZE));
    this->map[PUT_TEXT]->setText("Type the IP", WHITE);

    this->map.emplace(VARIABLE_TEXT, new TextTexture(renderer, FONT_PATH2, FONT_SIZE_TYPE));
    this->map[VARIABLE_TEXT]->setText(this->variableText, WHITE);
}

void IpMenu::start(){
    bool quit = false;
    SDL_Event event;
    isPort = false;
    while (!quit) {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_BACKSPACE && this->variableText.length() > 0){
                    this->variableText.pop_back();
                    this->renderText = true;
                }else if (event.key.keysym.sym == SDLK_RETURN){
                    if (variableText[0] == ' '){
                        variableText.erase(variableText.begin());
                    }
                    if (isPort){
                        this->port = variableText;
                        quit = true;
                    }else{
                        this->ip = variableText;
                        std::cout << this->ip << std::endl;
                        this->variableText = "";
                        this->map[PUT_TEXT]->setText("Type the Port", WHITE);
                        renderText = true;
                        isPort = true;
                    }
                }
            }else if (event.type == SDL_TEXTINPUT){
                if (isPort){
                    char aux = event.text.text[0];
                    if (aux >= 48 && aux <= 57){
                        this->variableText += event.text.text;
                    }
                }else{
                    this->variableText += event.text.text;
                }
                this->renderText = true;
            }
        }
        if (renderText){
            if (this->variableText == ""){
                this->map[VARIABLE_TEXT]->setText(" ", WHITE);
            }else{
                this->map[VARIABLE_TEXT]->setText(this->variableText, WHITE);
            }
        }
        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();

        this->background.render(0, 0, window.getWidth(), window.getHeight());

        this->map[PUT_TEXT]->render({(window.getWidth() - this->map[PUT_TEXT]->getSize().w)/2,
         (window.getHeight() - this->map[PUT_TEXT]->getSize().h)/2 - 100});

        this->map[VARIABLE_TEXT]->render({(window.getWidth() - this->map[VARIABLE_TEXT]->getSize().w)/2,
         (window.getHeight() - this->map[VARIABLE_TEXT]->getSize().h)/2});

        renderer.updateScreen();
    }
}

std::string IpMenu::getIp(){
    return this->ip;
}

std::string IpMenu::getPort(){
    return this->port;
}
