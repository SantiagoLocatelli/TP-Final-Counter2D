#include "ClientManager.h"
#include "../../common_src/SocketClosedException.h"
#include <utility>
#include <iostream>
#include <memory>

ClientManager::ClientManager(Protocol protocol, EventQueue &eventQueue, ModelQueue &modelQueue, MapInfo map, int id):protocol(std::move(protocol)), id(id), receiver(this->protocol, eventQueue, id), keep_sending(true), modelQueue(modelQueue), map(map){}

void ClientManager::run(){
    try{
        protocol.send_map_info(map);

        receiver.start();
        while (keep_sending){
            std::shared_ptr<CompleteModelInfo> model = modelQueue.pop();
            ModelInfo modelInfo = model->getModelInfo(id);
            protocol.send_model_info(modelInfo);

            keep_sending = !model->ended();
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
