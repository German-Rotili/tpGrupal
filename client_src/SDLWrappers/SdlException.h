#ifndef SDLEXCEPTION_H
#define SDLEXCEPTION_H

#include <exception>
class SdlException : public std::exception{
  const char* _msg;
  public:
    explicit SdlException(const char* msg):
    _msg(msg)
    {}
    SdlException() {
      _msg = "Error en SDL";
    }
    const char* what() const throw(){
      return _msg;
    }
};
#endif  // SDLEXCEPTION_H
