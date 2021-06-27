#include "ClientManager.h"
#include <utility>

ClientManager::ClientManager(Socket skt, EventQueue &queue, Emitter &emitter
, int id)
:protocol(std::move(skt)), emitter(emitter), receiver(protocol, queue), id(id){}

void ClientManager::run(){
    bool keep_sending = true;
    protocol.send_map_info(emitter.recvMap());

    receiver.start();
    while (keep_sending){
        CompleteModelInfo model = emitter.recvModel();
        protocol.send_model_info(model.getModelInfo(id));
        keep_sending = model.ended();
    }

    receiver.stop();
    receiver.join();
}

