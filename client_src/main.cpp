#include "Events/eventManager.h"
#include "../common_src/Stopwatch.h"
#include "GameManager.h"
#include <iostream>


int main(int argc, char* argv[]){
    try{
        Protocol server(Socket("localhost", argv[1], false));

        //Puse esto para probar el servidor. Esto seria lo que hace el menu de inicio en el cliente
        std::string command;
        bool joined_game = false;
        while (!joined_game && std::cin >> command){
            if (command == "crear"){
                Event event;
                event.type = CREATE_GAME;
                std::cin >> event.info.gameInfo.name;
                std::cin >> event.info.gameInfo.map;
                std::cin >> event.info.gameInfo.max_players;
                server.send_event(event);
                joined_game = true;
            } else if (command == "unirse"){
                Event event;
                event.type = JOIN_GAME;
                std::cin >> event.info.gameInfo.name;
                server.send_event(event);
                joined_game = true;
            } else if (command == "listar"){
                Event event;
                event.type = LIST_GAMES;
                server.send_event(event);
                std::list<GameInfo> gameList;
                server.recv_game_list(gameList);
                std::cout << "PARTIDAS:\n";
                for (const GameInfo &game: gameList){
                    std::cout << game.name << std::endl;
                }
            } else {
                std::cout << "Comando inválido\n";
            }
        }


        int window_w = 500, window_h = 500;

        MapInfo map;
        server.recv_map_info(map);

        ModelInfo model;
        server.recv_model_info(model);

        LevelInfo level;
        GameManager gameManager;
        
        level = gameManager.initializeLevel(map, model);
        GameViewer gameViewer(window_w, window_h, level); 

        bool quit = false;
        EventManager eventManager(server, quit, gameViewer);
        eventManager.start();
        Stopwatch stopwatch;

        while (!quit && !model.game_ended) {
            stopwatch.start();
            server.recv_model_info(model);

            level = gameManager.updatedLevel(model);
            gameViewer.update(level);
            gameViewer.render();
            while (stopwatch.msPassed() < 33) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        eventManager.stop();
        eventManager.join();
    } catch (const std::exception &e){
        std::cerr << "ERROR:" << e.what() << std::endl;
    }
    return 0;
}
