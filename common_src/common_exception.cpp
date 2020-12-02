#include "common_exception.h"
#include <string>

SuperException::SuperException(const char* msg) noexcept: 
    msg(msg){}

const char* SuperException::what() const noexcept{
    return msg;
}

