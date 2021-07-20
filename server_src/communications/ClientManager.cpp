#include "ClientManager.h"
#include "../../common_src/SocketClosedException.h"
#include <utility>
#include <iostream>
#include <memory>

ClientManager::ClientManager(Protocol protocol, EventQueue &eventQueue, ModelQueue &modelQueue, MapInfo map, int id):protocol(std::move(protocol)), id(id), receiver(this->protocol, eventQueue, id), keepSending(true), modelQueue(modelQueue), map(map), ready(false){}

void ClientManager::run(){
    try{
        protocol.send_map_info(map);
        std::shared_ptr<CompleteModelInfo> model = modelQueue.pop();
        ModelInfo modelInfo = model->getModelInfo(id);
        protocol.send_model_info(modelInfo);
        Event e;
        do{
            protocol.recv_event(e);
        }while (e.type != CLIENT_READY);
        ready = true;

        receiver.start();
        while (keepSending){
            model = modelQueue.pop();
            modelInfo = model->getModelInfo(id);
            protocol.send_model_info(modelInfo);

            keepSending = !model->ended();
        }
    } catch (const SocketClosedException &e){
    } catch (const std::exception &e){
        std::cerr << "ERROR en `ClientManager`" << e.what() << std::endl;
    }

    receiver.stop();
    receiver.join();
}

bool ClientManager::finished(){
    return !keepSending;
}

bool ClientManager::isReady(){
    return ready;
}
