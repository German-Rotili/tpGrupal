#include "common_socket_exception.h"
#include <string>

CloseSocketException::CloseSocketException(){}    
CloseSocketException::~CloseSocketException(){}
const char *CloseSocketException::what(){
    return "";
}
