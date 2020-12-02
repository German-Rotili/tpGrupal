#ifndef SOCKET_EX
#define SOCKET_EX
#include <exception>

class CloseSocketException : public std::exception{
public:
    CloseSocketException();
    ~CloseSocketException();
    const char *what();
};
#endif
