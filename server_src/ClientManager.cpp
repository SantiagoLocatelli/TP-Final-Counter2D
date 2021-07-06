#include "ClientManager.h"
#include "../common_src/SocketClosedException.h"
#include <utility>
#include <iostream>

ClientManager::ClientManager(Socket skt, EventQueue &queue, Emitter &emitter
, int id):protocol(std::move(skt)), emitter(emitter), id(id), receiver(protocol
, queue, id), keep_sending(true){}

void ClientManager::run(){
    try{
        protocol.send_map_info(emitter.recvMap());

        receiver.start();
        while (keep_sending){
            CompleteModelInfo &model = emitter.recvModel();
            ModelInfo modelInfo = model.getModelInfo(id);
            protocol.send_model_info(modelInfo);

            keep_sending = !model.ended();
        }
    } catch (const SocketClosedException &e){
    } catch (const std::exception &e){
        std::cerr << "ERROR en `ClientManager`" << e.what() << std::endl;
    }

    receiver.stop();
    receiver.join();
}

bool ClientManager::finished(){
    return !keep_sending;
}
