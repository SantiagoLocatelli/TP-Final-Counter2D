#include "client.h"
#include "../protocol/Socket.h"
#include <utility>

Client::Client(const char* host, const char* service):
    com(std::move(Socket(host, service, false))){

}

void Client::recvWindowSize(int& w, int& h){
    this->com.recv_window_size(w, h);
}
