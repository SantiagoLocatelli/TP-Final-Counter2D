#ifndef _SOCKET_CLOSED_EXCEPTION_H_
#define _SOCKET_CLOSED_EXCEPTION_H_

#include "GeneralException.h"

class SocketClosedException: public GeneralException{
    public:
        SocketClosedException();  
};

#endif
