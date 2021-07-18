#include <dirent.h>
#include "Menu.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <memory>
#include "yaml-cpp/yaml.h"

#define MAPS_PATH "../../common_src/maps/"

#define WINDOW_LABEL "Counter Strike 2D - Main Menu"
#define BACKGROUND_PATH "../../common_src/img/counter.jpeg"
#define SIZE_FONT 30
#define QUIT 0
#define NEW_GAME 1
#define JOIN 2
#define BACK 3
#define CONFIRM 4
#define TITLE 5

#define MAX_PLAYERS 10
#define MIN_PLAYERS 2 

#define MAX_STRING 29
#define MARGIN 20
#define PATH_FONT "../../common_src/img/digital-7.ttf"
#define PATH "../../client_src/yaml/"

const struct Color NEGRO = {0x00, 0x00, 0x00};
const struct Color HUD_COLOR = {0xAD, 0x86, 0x33};
const struct Color WHITE = {0xff, 0xff, 0xff};
const struct SDL_Rect FRAME_TO_SHOW = {32, 32, 32, 32};

const struct Size RESOLUTION_STANDARD = {600, 600};
const struct Size RESOLUTION_SEMI_HIGH = {800, 800};
const struct Size RESOLUTION_HIGH = {1000, 1000};


Menu::Menu(Size windowSize, Protocol& server):window(WINDOW_LABEL, windowSize.w, windowSize.h),
    renderer(&window), size(windowSize), 
    background(this->renderer, BACKGROUND_PATH), server(server){
    loadButtons();
    loadSkins(renderer);
}

void Menu::loadSkins(SdlRenderer& renderer){
    std::stringstream path;
    path << PATH;
    path << "playerSkins.yaml";
    YAML::Node yaml_map = YAML::LoadFile(path.str());
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        std::pair<std::string, int> texture = it->as<std::pair<std::string, int>>();
        SkinType skin = (SkinType) texture.second;
        this->skins[skin] = std::unique_ptr<SdlTexture> (new SdlTexture(renderer, texture.first, NEGRO.r, NEGRO.g, NEGRO.b));
    }
}


void Menu::loadButtons(){
    this->buttons[QUIT] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
    this->buttons[QUIT]->setText("Quit Game", WHITE);
    Size sizeTexture = this->buttons[QUIT]->getSize();
    Coordinate pos = {MARGIN, this->size.h - MARGIN - sizeTexture.h}; 
    this->buttons[QUIT]->setCoordinate(pos);
   
    this->buttons[NEW_GAME] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
    this->buttons[NEW_GAME]->setText("Create Game", WHITE);
    sizeTexture = this->buttons[NEW_GAME]->getSize();
    pos.y = pos.y - sizeTexture.h - MARGIN;
    this->buttons[NEW_GAME]->setCoordinate(pos);

    this->buttons[JOIN] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
    this->buttons[JOIN]->setText("Join Game", WHITE);
    sizeTexture = this->buttons[JOIN]->getSize();
    pos.y = pos.y - sizeTexture.h - MARGIN;
    this->buttons[JOIN]->setCoordinate(pos);

    this->buttons[BACK] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
    this->buttons[BACK]->setText("Back", WHITE);
    sizeTexture = this->buttons[BACK]->getSize();
    pos = {MARGIN, this->size.h - MARGIN - sizeTexture.h};
    this->buttons[BACK]->setCoordinate(pos);


    this->buttons[CONFIRM] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
    this->buttons[CONFIRM]->setText("Confirm", WHITE);
    sizeTexture = this->buttons[CONFIRM]->getSize();
    pos = {this->size.w - MARGIN - sizeTexture.w, this->size.h - MARGIN - sizeTexture.h};
    this->buttons[CONFIRM]->setCoordinate(pos);

    this->buttons[TITLE] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
}


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
        
        Size sizeTexture = maps[path]->getSize();
        Coordinate pos = {this->size.w/2 - sizeTexture.w/2, nextHeight};
        maps[path]->setCoordinate(pos);

        nextHeight += sizeTexture.h + MARGIN;
    }
}

void Menu::renderCreateMenu(std::map<std::string, std::unique_ptr<TextTexture>>& maps,
    bool mapSelected, bool nameSelected, std::string nameGame, int players){
    Size sizeTexture;
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    this->background.render(0, 0, this->size.w, this->size.h);

    if (!mapSelected) {
        this->buttons[TITLE]->setText("Choose a map:", HUD_COLOR);
        sizeTexture = this->buttons[TITLE]->getSize();
        Coordinate pos = {this->size.w/2 - sizeTexture.w/2, MARGIN};
        this->buttons[TITLE]->render(pos);

        for (auto it = maps.begin(); it != maps.end(); it++) {
            it->second->render();
        }
    } else if (!nameSelected && mapSelected) {
        this->buttons[TITLE]->setText("Write the game's name:", HUD_COLOR);
        sizeTexture = this->buttons[TITLE]->getSize();
        this->buttons[TITLE]->render({this->size.w/2 - sizeTexture.w/2, MARGIN});

        this->buttons[TITLE]->setText(nameGame.c_str(), WHITE);
        sizeTexture = this->buttons[TITLE]->getSize();
        this->buttons[TITLE]->render({this->size.w/2 - sizeTexture.w/2, 200});
        
        this->buttons[CONFIRM]->render();
    } else if (nameSelected && mapSelected) {

        this->buttons[TITLE]->setText("Quantity of players.", HUD_COLOR);
        sizeTexture = this->buttons[TITLE]->getSize();
        this->buttons[TITLE]->render({this->size.w/2 - sizeTexture.w/2, 50});

        this->buttons[TITLE]->setText("Arrow up to increase.", HUD_COLOR);
        sizeTexture = this->buttons[TITLE]->getSize();
        this->buttons[TITLE]->render({this->size.w/2 - sizeTexture.w/2, 100});

        this->buttons[TITLE]->setText("Arrow down to decrease.", HUD_COLOR);
        sizeTexture = this->buttons[TITLE]->getSize();
        this->buttons[TITLE]->render({this->size.w/2 - sizeTexture.w/2, 150});

        char playersText[10];
        sprintf(playersText, "%d", players);
        this->buttons[TITLE]->setText(playersText, WHITE);
        sizeTexture = this->buttons[TITLE]->getSize();
        this->buttons[TITLE]->render({this->size.w/2 - sizeTexture.w/2, 200});
        
        this->buttons[CONFIRM]->render();
    }
    this->buttons[BACK]->render();
    
    renderer.updateScreen();
}


void Menu::createGame(bool& joined_game, bool& quit, Event& event){

    std::map<std::string, std::unique_ptr<TextTexture>> maps;
    loadMaps(maps);

    SDL_Event e;
    bool mapSelected = false;
    bool nameSelected = false;
    bool playersSelected = false;
    std::string mapName;
    std::string nameGame = " ";
    int quanPlayers = MIN_PLAYERS;

    bool back = false;
    while (!joined_game && !quit && !back) {
        while (SDL_PollEvent(&e) != 0 && !quit) {
            if (e.type == SDL_MOUSEMOTION)
                continue;
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
                if (this->buttons[BACK]->isMouseTouching()) {
                    back = true;
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
                if (nameGame.length() < MAX_STRING) {
                    nameGame += e.text.text;
                }
            } else if (e.type == SDL_KEYDOWN && mapSelected && nameSelected) {
                if (e.key.keysym.sym == SDLK_UP && e.key.repeat == 0) {
                    if (quanPlayers < MAX_PLAYERS) {
                        quanPlayers++;
                    }
                } else if (e.key.keysym.sym == SDLK_DOWN && e.key.repeat == 0) {
                    if (quanPlayers > MIN_PLAYERS) {
                        quanPlayers--;
                    }
                }
            } 
            if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT && this->buttons[CONFIRM]->isMouseTouching()) {
                if (!nameSelected) {
                    nameSelected = true;
                    SDL_StopTextInput();
                } else if (!playersSelected) {
                    playersSelected = true;
                }
            }
            if (nameSelected && playersSelected && mapSelected) joined_game = true;
            renderCreateMenu(maps, mapSelected, nameSelected, nameGame, quanPlayers);
        }
    }
    if (joined_game) {
        event.type = CREATE_GAME;
        event.info.gameInfo.max_players = quanPlayers;
        strncpy(event.info.gameInfo.map, mapName.c_str(), MAX_STRING);
        strncpy(event.info.gameInfo.name, nameGame.c_str(), MAX_STRING);
    }
}

void Menu::renderJoinMenu(std::map<std::string, std::unique_ptr<TextTexture>>& options){
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    this->background.render(0, 0, this->size.w, this->size.h);

    this->buttons[TITLE]->setText("PARTIDAS: ", WHITE);
    Size sizeTexture = this->buttons[TITLE]->getSize();
    Coordinate pos = {this->size.w/2 - sizeTexture.w/2, MARGIN};
    this->buttons[TITLE]->render(pos);
    this->buttons[BACK]->render();

    for (auto it = options.begin(); it != options.end(); it++) {
        it->second->render();
    }

    renderer.updateScreen();
}


void Menu::joinGame(bool& joined_game, bool& quit, Event& event){
    
    event.type = LIST_GAMES;
    server.send_event(event);
    std::list<GameInfo> gameList;
    server.recv_game_list(gameList);


    std::map<std::string, std::unique_ptr<TextTexture>> options; // mapa con el nombre de la partida como key, la textura como value
    char text[200];
    int nextHeight = 60;
    for (const GameInfo &game: gameList) {

        sprintf(text, "Nombre: %s - Mapa: %s - Players: %i/%i", game.name, game.map, game.players, game.max_players);
         
        options[game.name] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
        options[game.name]->setText(text, WHITE);
        Size sizeTexture = options[game.name]->getSize();
        Coordinate pos = {this->size.w/2 - sizeTexture.w/2, nextHeight};
        options[game.name]->setCoordinate(pos);
        nextHeight += sizeTexture.h + MARGIN;
    }

    SDL_Event e;
    bool back = false;
    while (!joined_game && !quit && !back) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_MOUSEMOTION)
                continue;
            if (e.type == SDL_QUIT) {
                quit = true;  
            } else if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {

                for (auto it = options.begin(); it != options.end(); it++) {
                    if (it->second->isMouseTouching()) {
                        event.type = JOIN_GAME;
                        strncpy(event.info.gameInfo.name, it->first.c_str(), MAX_STRING);
                        joined_game = true;
                    }
                } 
                if (this->buttons[BACK]->isMouseTouching()) {
                    back = true;
                }
            }
            renderJoinMenu(options);
        }
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


void Menu::renderOptionsResolutions(std::map<Resolution, std::unique_ptr<TextTexture>>& options){
    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    this->background.render(0, 0, this->size.w, this->size.h);
    this->buttons[TITLE]->render();
    for (auto it = options.begin(); it != options.end(); it++) {
        it->second->render();
    }

    renderer.updateScreen();
}

void Menu::loadResolutions(std::map<Resolution, std::unique_ptr<TextTexture>>& options) {
    // enum Resolution : int {STANDARD, SEMI_HIGH, HIGH, ALTERNATIVE};
    options[STANDARD] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
    char text[100];
    sprintf(text, "%d x %d",RESOLUTION_STANDARD.w, RESOLUTION_STANDARD.h);
    options[STANDARD]->setText(text, WHITE);
    Size sizeText = options[STANDARD]->getSize();
    Coordinate pos = {this->size.w/2 - sizeText.w/2, 100};
    options[STANDARD]->setCoordinate(pos);

    options[SEMI_HIGH] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
    sprintf(text, "%d x %d", RESOLUTION_SEMI_HIGH.w, RESOLUTION_SEMI_HIGH.h);
    options[SEMI_HIGH]->setText(text, WHITE);
    sizeText = options[SEMI_HIGH]->getSize();
    pos = {this->size.w/2 - sizeText.w/2, 150};
    options[SEMI_HIGH]->setCoordinate(pos);

    options[HIGH] = std::unique_ptr<TextTexture> (new TextTexture(this->renderer, PATH_FONT, SIZE_FONT));
    sprintf(text, "%d x %d", RESOLUTION_HIGH.w, RESOLUTION_HIGH.h);
    options[HIGH]->setText(text, WHITE);
    sizeText = options[HIGH]->getSize();
    pos = {this->size.w/2 - sizeText.w/2, 200};
    options[HIGH]->setCoordinate(pos);
}

void setResolution(Size& resolution, Resolution resolutionType) {
    if (resolutionType == STANDARD) {
        resolution = RESOLUTION_STANDARD;
    } else if (resolutionType == HIGH) {
        resolution = RESOLUTION_HIGH;
    } else {
        resolution = RESOLUTION_SEMI_HIGH;
    }
}

void Menu::makeChooseResolution(bool& quit, Size& resolution){
    std::map<Resolution, std::unique_ptr<TextTexture>> options;
    
    this->buttons[TITLE]->setText("Choose a resolution:", HUD_COLOR);
    Size sizeText = this->buttons[TITLE]->getSize();
    Coordinate pos = {this->size.w/2 - sizeText.w/2, MARGIN};
    this->buttons[TITLE]->setCoordinate(pos);

    loadResolutions(options);
    Resolution resolutionType;
    

    SDL_Event e;
    bool selected = false;
    while (!quit && !selected) {
        while (SDL_PollEvent(&e) != 0 && !quit && !selected) {
            if (e.type == SDL_MOUSEMOTION)
                continue;
            if (e.type == SDL_QUIT) {
                quit = true;  
            } else if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {
                for (auto it = options.begin(); it != options.end(); it++) {
                    if (it->second->isMouseTouching()) {
                        resolutionType = it->first;
                        selected = true;
                    }
                }

            } 
        }
        renderOptionsResolutions(options);
    }

    setResolution(resolution, resolutionType);
}

void Menu::run(bool& joined_game, Size& windowSize){

    Event event;
    SDL_Event e;
    bool quit = false;
    while (!joined_game && !quit) {
        while (SDL_PollEvent(&e) != 0 && !joined_game) {
            if (e.type == SDL_MOUSEMOTION)
                continue;
            if (e.type == SDL_QUIT) {
                quit = true;  
            } else if ((e.type == SDL_MOUSEBUTTONDOWN) && e.button.button == SDL_BUTTON_LEFT) {
                if (this->buttons[QUIT]->isMouseTouching()) {
                    quit = true;
                } else if (this->buttons[NEW_GAME]->isMouseTouching()) {
                    this->createGame(joined_game, quit, event);
                } else  if (this->buttons[JOIN]->isMouseTouching()) {
                    this->joinGame(joined_game, quit, event);
                }
            }
        }
        this->renderInitMenu();
    }
    if (joined_game) {
        makeChooseResolution(quit, windowSize);
        this->server.send_event(event);
    }
}

