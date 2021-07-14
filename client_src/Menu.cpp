#include <dirent.h>
#include "Menu.h"
#include <algorithm>
#include <iostream>
#include <cstring>

#define MAPS_PATH "../../common_src/maps/"

#define WINDOW_LABEL "Counter Strike 2D - Main Menu"
#define BACKGROUND_PATH "../../common_src/img/counter.jpeg"
#define SIZE_FONT 30
#define QUIT 0
#define NEW_GAME 1
#define JOIN 2
#define MARGIN 20

Menu::Menu(Size windowSize, Protocol& server):window(WINDOW_LABEL, windowSize.w, windowSize.h),
    renderer(&window), size(windowSize), 
    background(this->renderer, windowSize.w, windowSize.h), server(server){

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
        this->maps.emplace(path, TextTexture(this->renderer, path, SIZE_FONT));
    }
}

void Menu::loadButtons(){

    Coordinate pos = {MARGIN, this->size.h - MARGIN};
    this->buttons[QUIT] = new TextTexture(this->renderer, "Quit", SIZE_FONT);
    this->buttons[QUIT]->setCoordinate(pos);

    pos = {MARGIN, this->size.h - MARGIN - 100};
    this->buttons[NEW_GAME] = new TextTexture(this->renderer, "New Game", SIZE_FONT);
    this->buttons[NEW_GAME]->setCoordinate(pos);
    
    pos = {MARGIN, this->size.h - MARGIN - 200};
    this->buttons[JOIN] = new TextTexture(this->renderer, "Join Game", SIZE_FONT);
    this->buttons[JOIN]->setCoordinate(pos);
}

Menu::~Menu(){
    for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
        TextTexture* aux = it->second;
        it++;
        delete aux;
    }
}

void Menu::renderInitMenu(){
    
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    this->background.render(0, 0);

    this->buttons[QUIT]->render();
    this->buttons[NEW_GAME]->render();
    this->buttons[JOIN]->render();

    renderer.updateScreen();
}


void Menu::creatGame(bool& joined_game){
    TextTexture buttonConfirm(this->renderer, "Confirm", SIZE_FONT);
    TextTexture buttonBack(this->renderer, "Back", SIZE_FONT);

    SDL_Event e;
    bool quit = false;
    while (SDL_PollEvent(&e) != 0 && !joined_game && !quit) {
        if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {

            for (auto it = this->maps.begin(); it != this->maps.end(); it++) {
                if (it->second.isMouseTouching()) {

                }
            }
            if (buttonBack.isMouseTouching()) {
                quit = false;
            }
        }
    }
}

void Menu::renderJoinMenu(TextTexture& title, TextTexture& buttonBack, std::map<std::string, TextTexture>& options){
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
        it->second.setCoordinate(pos);
        it->second.render();
    }

    renderer.updateScreen();
}


void Menu::joinGame(bool& joined_game){
    
    Event event;
    event.type = LIST_GAMES;
    server.send_event(event);
    std::list<GameInfo> gameList;
    server.recv_game_list(gameList);


    TextTexture title(this->renderer, "PARTIDAS:", SIZE_FONT);
    TextTexture buttonBack(this->renderer, "Back", SIZE_FONT);
    std::map<std::string, TextTexture> options; // mapa con el nombre de la partida como key, la textura como value
    char text[200];
    for (const GameInfo &game: gameList) {

        sprintf(text, "Nombre: %s - Mapa: %s - Players: %i/%i", game.name, game.map, game.players, game.max_players);
        options.emplace(game.name, TextTexture(this->renderer, text, SIZE_FONT));
    }

    SDL_Event e;
    bool quit = false;
    while (SDL_PollEvent(&e) != 0 && !joined_game && !quit) {
        if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {

            for (auto it = options.begin(); it != options.end(); it++) {
                if (it->second.isMouseTouching()) {
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
}

void Menu::run(){
    SDL_Event e;
    bool quit = false;
    bool joined_game = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0 && !joined_game) {
            
            if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {
                if (this->buttons[QUIT]->isMouseTouching()) {
                    quit = true;
                } else if (this->buttons[NEW_GAME]->isMouseTouching()) {
                    this->creatGame(joined_game);
                    quit = joined_game;
                } else  if (this->buttons[JOIN]->isMouseTouching()) {
                    this->joinGame(joined_game);
                    quit = joined_game;
                }
            }

            // //Puse esto para probar el servidor. Esto seria lo que hace el menu de inicio en el cliente
            // while (!joined_game && std::cin >> command){
            //     if (command == "crear"){
            //         Event event;
            //         event.type = CREATE_GAME;
            //         std::cin >> event.info.gameInfo.name;
            //         std::cin >> event.info.gameInfo.map;
            //         std::cin >> event.info.gameInfo.max_players;
            //         server.send_event(event);
            //         joined_game = true;
            //     } else if (command == "unirse"){
            //         Event event;
            //         event.type = JOIN_GAME;
            //         std::cin >> event.info.gameInfo.name;
            //         server.send_event(event);
            //         joined_game = true;
            //     } else if (command == "listar"){
            //         Event event;
            //         event.type = LIST_GAMES;
            //         server.send_event(event);
            //         std::list<GameInfo> gameList;
            //         server.recv_game_list(gameList);
            //         std::cout << "PARTIDAS:\n";
            //         for (const GameInfo &game: gameList){
            //             std::cout << game.name << std::endl;
            //         }
            //     } else {
            //         std::cout << "Comando inválido\n";
            //     }
            // }
        }


    }
}

