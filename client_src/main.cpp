#include "../common_src/SocketClosedException.h"
#include "../../common_src/Protocol.h"
#include "../common_src/Stopwatch.h"
#include "Managers/EventManager.h"
#include "Managers/GameManager.h"
#include "Managers/GameViewer.h"
#include "Menu/LoadingMenu.h"
#include "Menu/ThreadWait.h"
#include "Menu/IpMenu.h"
#include "Menu/Menu.h"
#include <iostream>

int main(int argc, char* argv[]){
    try{
        IpMenu* ipMenu = new IpMenu();

        ipMenu->start();

        Protocol server(Socket(ipMenu->getIp().c_str(), ipMenu->getPort().c_str(), false));

        delete ipMenu;

        Size menuSize = {640, 480};
        Menu* menu = new Menu(menuSize, server);
        bool joined_game = false; 
        Size windowSize {500, 500};
        menu->run(joined_game, windowSize);
        
        delete menu;
        if (!joined_game) {
            return 0;
        } 

        MapInfo map;
        ModelInfo model;
        bool loading = true;

        LevelInfo level;
        GameManager gameManager(windowSize);

        ThreadWait wait(server, loading, map, model);
        wait.start();

        LoadingMenu* loadingMenu = new LoadingMenu(menuSize);
        loadingMenu->run(loading);
        delete loadingMenu;

        wait.join();

        gameManager.initializeLevel(level, map, model);
        GameViewer gameViewer(windowSize, level); 

        bool gameEnded = model.game_ended;
        EventManager eventManager(server, gameEnded, gameViewer);
        eventManager.start();
        try{
            Stopwatch stopwatch;

            Event ready;
            ready.type = CLIENT_READY;
            server.send_event(ready);

            server.recv_model_info(model);
            while (!model.game_ended) {
                stopwatch.start();
                server.recv_model_info(model);
                gameManager.updatedLevel(level, model);
                gameViewer.update(level);
                gameViewer.render();
                while (stopwatch.msPassed() < FRAME_MS) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
        } catch(const GeneralException &e){
            eventManager.stop();
            eventManager.join();
            return 0;
        }

        // es para mostrar el resultado final de la partida
        SDL_Event e;
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0 && !quit) {
                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        if (e.key.keysym.sym == SDLK_RETURN && e.key.repeat == 0) {
                            quit = true;
                        }
                        break;
                }
            }
            gameViewer.renderGameResult();
        }
    }catch(const SocketClosedException &e){
        std::cerr << "Ocurrió un error y el servidor cerró tu conexión.\n";
    }catch (const std::exception &e){
        std::cerr << "ERROR:" << e.what() << std::endl;
    }
    return 0;
}
