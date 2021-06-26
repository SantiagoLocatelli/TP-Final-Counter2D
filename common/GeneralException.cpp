#include "GeneralException.h"

GeneralException::GeneralException(const std::string &msg) noexcept 
:msg_error(msg){}

const char* GeneralException::what() const noexcept{
    return msg_error.c_str();
}
