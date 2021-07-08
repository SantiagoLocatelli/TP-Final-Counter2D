#include "Accepter.h"
#include "../common_src/SocketClosedException.h"
#include <iostream>
#include <utility>

Accepter::Accepter(char const *port, GameList &gameList):skt(NULL, port, true),gameList(gameList){}


void Accepter::run(){
    bool keepAccepting = true;
    while (keepAccepting){
        try{
            Socket cli_skt = skt.accept_one();
            LobbyManager *client = new LobbyManager(std::move(cli_skt), gameList);

            clientList.push_back(client);
            client->start();


            //Elimino los clientes que terminaron
            auto i = clientList.begin();
            while (i != clientList.end()){
                if ((*i)->finished()){
                    (*i)->join();
                    delete (*i);
                    i = clientList.erase(i);
                } else {
                    ++i;
                }
            }
        } catch (const SocketClosedException &e){
            keepAccepting = false;
        } catch (const std::exception &e){
            keepAccepting = false;
            std::cerr << "ERROR: " << e.what();
        } catch(...){
            std::cerr << "Error desconocido.\n";
            keepAccepting = false;
        }
    }

    for (auto cli : clientList){
        cli->join();
        delete cli;
    }
}

void Accepter::stop(){
    skt.close_socket();
}
