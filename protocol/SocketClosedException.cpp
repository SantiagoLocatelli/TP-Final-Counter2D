#include "SocketClosedException.h"
#include <string>

SocketClosedException::SocketClosedException()
:GeneralException(std::string("El socket está cerrado.\n")){}
