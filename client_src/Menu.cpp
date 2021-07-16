#include <dirent.h>
#include "Menu.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <memory>

#define MAPS_PATH "../../common_src/maps/"

#define WINDOW_LABEL "Counter Strike 2D - Main Menu"
#define BACKGROUND_PATH "../../common_src/img/counter.jpeg"
#define SIZE_FONT 30
#define QUIT 0
#define NEW_GAME 1
#define JOIN 2
#define MARGIN 20
#define PATH_FONT "../../common_src/img/digital-7.ttf"

const struct Color HUD_COLOR = {0xAD, 0x86, 0x33};
const struct Color WHITE = {0xff, 0xff, 0xff};

Menu::Menu(Size windowSize, Protocol& server):window(WINDOW_LABEL, windowSize.w, windowSize.h),
    renderer(&window), size(windowSize), 
    background(this->renderer, BACKGROUND_PATH), server(server){}


void Menu::loadMaps(std::map<std::string, std::unique_ptr<TextTexture>>& maps){
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
    int nextHeight = MARGIN + 50;
    for (auto &path : mapsPaths){
        std::string::iterator prot_i = std::search(path.begin(),
                path.end(), prot_end.begin(), prot_end.end());

        int start_position = prot_i - path.begin();

        path.erase(start_position, path.length());
        maps[path] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
        maps[path]->setText(path, WHITE);
        
        Size size = maps[path]->getSize();
        Coordinate pos = {this->size.w/2 - size.w/2, nextHeight};
        maps[path]->setCoordinate(pos);

        nextHeight += size.h + MARGIN;
    }
}


Menu::~Menu(){}



void Menu::renderCreateMenu(std::map<std::string, std::unique_ptr<TextTexture>>& maps,
     bool mapSelected, bool nameSelected, std::string nameGame, 
    int players, TextTexture& buttonBack, TextTexture& buttonConfirm, TextTexture& title){

    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    TextTexture text(this->renderer, PATH_FONT, SIZE_FONT);
    this->background.render(0, 0, this->size.w, this->size.h);

    if (!mapSelected) {
        title.render();
        for (auto it = maps.begin(); it != maps.end(); it++) {
            it->second->render();
        }
    } else if (!nameSelected && mapSelected) {
        text.setText("Write the game's name:", HUD_COLOR);
        Size size = text.getSize();
        text.render({this->size.w/2 - size.w/2, MARGIN});

        text.setText(nameGame.c_str(), WHITE);
        size = text.getSize();
        text.render({this->size.w/2 - size.w/2, 200});
        buttonConfirm.render();
    } else if (nameSelected && mapSelected) {

        text.setText("Quantity of players.", HUD_COLOR);
        Size size = text.getSize();
        text.render({this->size.w/2 - size.w/2, 50});

        text.setText("Arrow up to increase.", HUD_COLOR);
        size = text.getSize();
        text.render({this->size.w/2 - size.w/2, 100});

        text.setText("Arrow down to decrease.", HUD_COLOR);
        size = text.getSize();
        text.render({this->size.w/2 - size.w/2, 150});

        char playersText[10];
        sprintf(playersText, "%d", players);
        text.setText(playersText, WHITE);
        size = text.getSize();
        text.render({this->size.w/2 - size.w/2, 200});
        buttonConfirm.render();
    }
    buttonBack.render();
    
    renderer.updateScreen();
}


void Menu::createGame(bool& joined_game){
    TextTexture buttonBack(this->renderer, PATH_FONT, SIZE_FONT);
    buttonBack.setText("Back", WHITE);
    Size size = buttonBack.getSize();
    Coordinate pos = {MARGIN, this->size.h - MARGIN - size.h};
    buttonBack.setCoordinate(pos);

    TextTexture buttonConfirm(this->renderer, PATH_FONT, SIZE_FONT);
    buttonConfirm.setText("Confirm", WHITE);
    size = buttonConfirm.getSize();
    pos = {this->size.w - size.w - MARGIN, this->size.h - MARGIN - size.h};
    buttonConfirm.setCoordinate(pos);

    TextTexture title(this->renderer, PATH_FONT, SIZE_FONT);
    title.setText("Choose a map:", HUD_COLOR);
    size = title.getSize();
    pos = {this->size.w/2 - size.w/2, MARGIN};
    title.setCoordinate(pos);

    std::map<std::string, std::unique_ptr<TextTexture>> maps;
    loadMaps(maps);

    SDL_Event e;
    bool quit = false;
    bool mapSelected = false;
    bool nameSelected = false;
    bool playersSelected = false;
    std::string mapName;
    std::string nameGame = " ";
    int maxPlayers = 2;

    SDL_PumpEvents();
    while (!joined_game && !quit) {
        while (SDL_PollEvent(&e) != 0 && !quit) {
            if (e.type == SDL_QUIT) {
                quit = true;  
            } else if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {
                if (!mapSelected) {
                    for (auto it = maps.begin(); it != maps.end(); it++) {
                        if (it->second->isMouseTouching()) {
                            mapSelected = true;
                            mapName = it->first;
                            SDL_StartTextInput();
                        }
                    }
                }
                if (buttonBack.isMouseTouching()) {
                    quit = true;
                }
            } else if (e.type == SDL_KEYDOWN && mapSelected && !nameSelected) {
                if( e.key.keysym.sym == SDLK_BACKSPACE && nameGame.length() > 0 && e.key.repeat == 0){
                    if (nameGame.length() == 1) {
                        nameGame = " ";
                    } else {
                        nameGame.pop_back();
                    }
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
                }
            } 
            if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT && buttonConfirm.isMouseTouching()) {
                if (!nameSelected) {
                    nameSelected = true;
                } else if (!playersSelected) {
                    playersSelected = true;
                }
            }
            if (nameSelected && playersSelected && mapSelected) joined_game = true;
            renderCreateMenu(maps, mapSelected, nameSelected, nameGame, maxPlayers, buttonBack , buttonConfirm, title);
        }
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

void Menu::renderJoinMenu(TextTexture& title, TextTexture& buttonBack, std::map<std::string, std::unique_ptr<TextTexture>>& options){
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    this->background.render(0, 0, this->size.w, this->size.h);

    title.render();
    buttonBack.render();

    for (auto it = options.begin(); it != options.end(); it++) {
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
    Size size = title.getSize();
    Coordinate pos = {this->size.w/2 - size.w/2, MARGIN};
    title.setCoordinate(pos);

    TextTexture buttonBack(this->renderer, PATH_FONT, SIZE_FONT);
    buttonBack.setText("Back", WHITE);
    size = buttonBack.getSize();
    pos = {MARGIN, this->size.h - MARGIN - size.h};
    buttonBack.setCoordinate(pos);

    std::map<std::string, std::unique_ptr<TextTexture>> options; // mapa con el nombre de la partida como key, la textura como value
    char text[200];
    int nextHeight = 60;
    for (const GameInfo &game: gameList) {

        sprintf(text, "Nombre: %s - Mapa: %s - Players: %i/%i", game.name, game.map, game.players, game.max_players);
         
        options[game.name] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
        options[game.name]->setText(text, WHITE);
        Size size = options[game.name]->getSize();
        Coordinate pos = {this->size.w/2 - size.w/2, nextHeight};
        options[game.name]->setCoordinate(pos);
        nextHeight += size.h + MARGIN;
    }

    SDL_Event e;
    bool quit = false;
    while (!joined_game && !quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;  
            } else if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {

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
    }

    this->server.send_event(event);
}

void Menu::renderInitMenu(TextTexture& quitButton, TextTexture& createButton, TextTexture& joinButton){
    
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    this->background.render(0, 0, this->size.w, this->size.h);
    quitButton.render();
    createButton.render();
    joinButton.render();

    renderer.updateScreen();
}

void Menu::run(bool& joined_game){

    TextTexture quitButton(this->renderer, PATH_FONT, SIZE_FONT);
    quitButton.setText("Quit Game", WHITE);
    Size size = quitButton.getSize();
    Coordinate pos = {MARGIN, this->size.h - MARGIN - size.h}; 
    quitButton.setCoordinate(pos);
   
    TextTexture createButton(this->renderer, PATH_FONT, SIZE_FONT);
    createButton.setText("Create Game", WHITE);
    size = createButton.getSize();
    pos.y = pos.y - size.h - MARGIN;
    createButton.setCoordinate(pos);
    
    TextTexture joinButton(this->renderer, PATH_FONT, SIZE_FONT);
    joinButton.setText("Join Game", WHITE);
    size = joinButton.getSize();
    pos.y = pos.y - size.h - MARGIN;
    joinButton.setCoordinate(pos);


    SDL_Event e;
    SDL_PumpEvents();
    bool quit = false;
    while (!joined_game && !quit) {
        while (SDL_PollEvent(&e) != 0 && !joined_game) {
            if (e.type == SDL_QUIT) {
                quit = true;  
            } else if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {
                if (quitButton.isMouseTouching()) {
                    quit = true;
                } else if (createButton.isMouseTouching()) {
                    this->createGame(joined_game);
                } else  if (joinButton.isMouseTouching()) {
                    this->joinGame(joined_game);
                }
            }
        }
        this->renderInitMenu(quitButton, createButton, joinButton);
    }
}

