#include <dirent.h>
#include "Menu.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>

#define MAPS_PATH "../../common_src/maps/"

#define WINDOW_LABEL "Counter Strike 2D - Main Menu"
#define BACKGROUND_PATH "../../common_src/img/counter.jpeg"
#define SIZE_FONT 30
#define QUIT 0
#define NEW_GAME 1
#define JOIN 2
#define MARGIN 20
#define PATH_FONT "../../common_src/img/digital-7.ttf"

const struct Color WHITE = {0xff, 0xff, 0xff};

Menu::Menu(Size windowSize, Protocol& server):window(WINDOW_LABEL, windowSize.w, windowSize.h),
    renderer(&window), size(windowSize), 
    background(this->renderer, BACKGROUND_PATH), server(server){

    loadMaps();
    loadButtons();
}


void Menu::loadMaps(){
    DIR *dir;
    struct dirent *ent;
    std::list<std::string> mapsPaths;
    if ((dir = opendir (MAPS_PATH)) != NULL) {

        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_name[0] != '.'){
                mapsPaths.push_back(ent->d_name);
            }
        }
        closedir (dir);
        delete ent;
    }
    
    std::string prot_end(".");
    for (auto &path : mapsPaths){
        std::string::iterator prot_i = std::search(path.begin(),
                path.end(), prot_end.begin(), prot_end.end());

        int start_position = prot_i - path.begin();

        path.erase(start_position, path.length());
        this->maps[path] = new TextTexture(this->renderer, path, SIZE_FONT);
    }
}

void Menu::loadButtons(){
    this->buttons[QUIT] = new TextTexture(this->renderer, PATH_FONT, SIZE_FONT);
    this->buttons[QUIT]->setText("Quit Game", WHITE);
    Size size = this->buttons[QUIT]->getSize();
    Coordinate pos = {MARGIN, this->size.h - MARGIN - size.h}; 
    this->buttons[QUIT]->setCoordinate(pos);


    this->buttons[NEW_GAME] = new TextTexture(this->renderer, PATH_FONT, SIZE_FONT);
    this->buttons[NEW_GAME]->setText("Creat Game", WHITE);
    size = this->buttons[NEW_GAME]->getSize();
    pos.y = pos.y - size.h - MARGIN;
    this->buttons[NEW_GAME]->setCoordinate(pos);

    this->buttons[JOIN] = new TextTexture(this->renderer, PATH_FONT, SIZE_FONT);
    this->buttons[JOIN]->setText("Join Game", WHITE);
    size = this->buttons[JOIN]->getSize();
    pos.y = pos.y - size.h - MARGIN;
    this->buttons[JOIN]->setCoordinate(pos);
}

Menu::~Menu(){
    for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
        TextTexture* aux = it->second;
        it++;
        delete aux;
    }

    for (auto it = this->maps.begin(); it != this->maps.end(); it++) {
        TextTexture* aux = it->second;
        it++;
        delete aux;
    }
}

void Menu::renderInitMenu(){
    
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    this->background.render(0, 0, this->size.w, this->size.h);

    this->buttons[QUIT]->render();
    this->buttons[NEW_GAME]->render();
    this->buttons[JOIN]->render();

    renderer.updateScreen();
}


void Menu::renderCreatMenu(bool mapSelected, bool nameSelected, bool playersSelected, std::string nameGame, int players){
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();
    TextTexture text(this->renderer, PATH_FONT, SIZE_FONT);

    if (!mapSelected) {
        int i = 1;
        for (auto it = this->maps.begin(); it != this->maps.end(); it++) {
            Coordinate pos = {this->size.w/3, MARGIN - i*50};
            it->second->setCoordinate(pos);
            it->second->render();
        }
    } else if (!nameSelected && mapSelected) {
        text.setText("Write the game's name:", WHITE);
        text.render({this->size.w/2, 50});

        text.setText(nameGame.c_str(), WHITE);
        text.render({this->size.w/2, 100});
    } else if (nameSelected && mapSelected && !playersSelected) {
        text.setText("Arrow up to increase the quantity of players, arrow down to decrease:", WHITE);
        text.render({this->size.w/2, 50});

        char playersText[10];
        sprintf(playersText, "%d", players);
        text.setText(playersText, WHITE);
        text.render({this->size.w/2, 100});
    }

    renderer.updateScreen();
}


void Menu::creatGame(bool& joined_game){
    TextTexture buttonConfirm(this->renderer, PATH_FONT, SIZE_FONT);
    TextTexture buttonBack(this->renderer, PATH_FONT, SIZE_FONT);

    SDL_Event e;
    bool quit = false;
    bool mapSelected = false;
    bool nameSelected = false;
    bool playersSelected = false;
    std::string mapName;
    std::string nameGame = " ";
    int maxPlayers = 2;
    while (SDL_PollEvent(&e) != 0 && !joined_game && !quit) {
        if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {
            if (!mapSelected) {
                for (auto it = this->maps.begin(); it != this->maps.end(); it++) {
                    if (it->second->isMouseTouching()) {
                        mapSelected = true;
                        mapName = it->first;
                        SDL_StartTextInput();
                    }
                }
            }
            if (buttonBack.isMouseTouching()) {
                quit = false;
            }
        } else if (e.type == SDL_KEYDOWN && mapSelected && !nameSelected) {
            if( e.key.keysym.sym == SDLK_BACKSPACE && nameGame.length() > 0 && e.key.repeat == 0){
                nameGame.pop_back();
            } else if ( e.key.keysym.sym == SDLK_KP_ENTER && e.key.repeat == 0) {
                nameSelected = true;
            }
        } else if (e.type == SDL_TEXTINPUT && mapSelected && !nameSelected) {
            if (nameGame.length() < 29) {
                nameGame += e.text.text;
            }
        } else if (e.type == SDL_KEYDOWN && mapSelected && nameSelected) {
            if (e.key.keysym.sym == SDLK_UP && e.key.repeat == 0) {
                if (maxPlayers < 10) {
                    maxPlayers++;
                }
            } else if (e.key.keysym.sym == SDLK_DOWN && e.key.repeat == 0) {
                if (maxPlayers > 2) {
                    maxPlayers--;
                }
            } else if (e.key.keysym.sym == SDLK_KP_ENTER && e.key.repeat == 0) {
                playersSelected = true;
            }
        }
        if (nameSelected && playersSelected && mapSelected) joined_game = true;
        renderCreatMenu(mapSelected, nameSelected, playersSelected, nameGame, maxPlayers);
    }

    if (joined_game) {
        Event event;
        event.type = CREATE_GAME;
        event.info.gameInfo.max_players = maxPlayers;
        strncpy(event.info.gameInfo.map, mapName.c_str(), 29);
        strncpy(event.info.gameInfo.name, nameGame.c_str(), 29);
        server.send_event(event);
    }
}

void Menu::renderJoinMenu(TextTexture& title, TextTexture& buttonBack, std::map<std::string, TextTexture*>& options){
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    Coordinate pos = {this->size.w/3, MARGIN};
    title.render(pos);

    pos = {MARGIN, this->size.h - MARGIN};
    buttonBack.setCoordinate(pos);
    buttonBack.render();

    int i = 1;
    for (auto it = options.begin(); it != options.end(); it++) {
        pos = {this->size.w/3, MARGIN - i*50};
        it->second->setCoordinate(pos);
        it->second->render();
    }

    renderer.updateScreen();
}


void Menu::joinGame(bool& joined_game){
    
    Event event;
    event.type = LIST_GAMES;
    server.send_event(event);
    std::list<GameInfo> gameList;
    server.recv_game_list(gameList);


    TextTexture title(this->renderer, PATH_FONT, SIZE_FONT);
    title.setText("PARTIDAS: ", WHITE);

    TextTexture buttonBack(this->renderer, PATH_FONT, SIZE_FONT);
    buttonBack.setText("Back", WHITE);

    std::map<std::string, TextTexture*> options; // mapa con el nombre de la partida como key, la textura como value
    char text[200];
    for (const GameInfo &game: gameList) {

        sprintf(text, "Nombre: %s - Mapa: %s - Players: %i/%i", game.name, game.map, game.players, game.max_players);
        options[game.name] = new TextTexture(this->renderer, PATH_FONT, SIZE_FONT);
        options[game.name]->setText(text, WHITE);
    }

    SDL_Event e;
    bool quit = false;
    while (SDL_PollEvent(&e) != 0 && !joined_game && !quit) {
        if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {

            for (auto it = options.begin(); it != options.end(); it++) {
                if (it->second->isMouseTouching()) {
                    event.type = JOIN_GAME;
                    strncpy(event.info.gameInfo.name, it->first.c_str(), 29);
                    joined_game = true;
                }
            } 
            if (buttonBack.isMouseTouching()) {
                quit = true;
            }
        }
        renderJoinMenu(title, buttonBack, options);
    }

    this->server.send_event(event);
    for (auto it = options.begin(); it != options.end(); it++) {
        TextTexture* aux = it->second;
        it++;
        delete aux;
    }
}

void Menu::run(){
    SDL_Event e;
    bool quit = false;
    bool joined_game = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0 && !joined_game && !quit) {
            
            if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {
                if (this->buttons[QUIT]->isMouseTouching()) {
                    printf("entro al if\n");
                    quit = true;
                } else if (this->buttons[NEW_GAME]->isMouseTouching()) {
                    this->creatGame(joined_game);
                    quit = joined_game;
                } else  if (this->buttons[JOIN]->isMouseTouching()) {
                    this->joinGame(joined_game);
                    quit = joined_game;
                }
            }
        }
        this->renderInitMenu();
    }
}

