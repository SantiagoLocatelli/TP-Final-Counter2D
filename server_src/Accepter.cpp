#include "Accepter.h"
#include "../common/SocketClosedException.h"
#include <iostream>
#include <utility>

Accepter::Accepter(char const *port, EventQueue &queue, Emitter &emitter)
:skt(NULL, port, true), queue(queue), emitter(emitter){}


void Accepter::run(){
    int id = 0;
    bool keep_accepting = true;
    while (keep_accepting){
        try{
            Socket cli_skt = skt.accept_one();
            ClientManager *client = new ClientManager(std::move(cli_skt)
            , queue, emitter, id);

            id++;

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
            keep_accepting = false;
        } catch (const std::exception &e){
            keep_accepting = false;
            std::cerr << "ERROR: " << e.what();
        } catch(...){
            std::cerr << "Error desconocido.\n";
            keep_accepting = false;
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
