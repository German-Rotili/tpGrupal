#ifndef SUPEREXCEPTION
#define SUPEREXCEPTION
#include <exception>
#include <errno.h>
#include <string>

class SuperException: public std::exception{
private:
    const char* msg;
public:
    const char *what() const noexcept;
    explicit SuperException(const char* msg) noexcept;
    ~SuperException() noexcept {}
};
#endif
