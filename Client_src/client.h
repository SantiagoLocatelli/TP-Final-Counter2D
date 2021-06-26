#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "../protocol/Protocol.h"

class Client{
private:
    Protocol com;

public:
    Client(const char* host, const char* service);
    void recvWindowSize(int& w, int& h);
    void recvPosition(int& x, int& y);
};

#endif