#include "ThreadWait.h"

ThreadWait::ThreadWait(Protocol& protocol, bool& loading, MapInfo& map, ModelInfo& model)
    :protocol(protocol), loading(loading), map(map), model(model){}

void ThreadWait::run(){
    protocol.recv_map_info(map);
    protocol.recv_model_info(model);
    loading = false;
}