#include "ClientManager.h"
#include <utility>
#include <iostream>

ClientManager::ClientManager(Socket skt, EventQueue &queue, Emitter &emitter
, int id):protocol(std::move(skt)), emitter(emitter), id(id), receiver(protocol
, queue, id), keep_sending(true){}

void ClientManager::run(){
    protocol.send_map_info(emitter.recvMap());

    receiver.start();
    while (keep_sending){
        CompleteModelInfo &model = emitter.recvModel();
        ModelInfo modelInfo = model.getModelInfo(id);
        protocol.send_model_info(modelInfo);

        keep_sending = !model.ended();
    }

    receiver.stop();
    receiver.join();
}

bool ClientManager::finished(){
    return !keep_sending;
}
