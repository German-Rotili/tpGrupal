#ifndef SDLEXCEPTION_H
#define SDLEXCEPTION_H

#define BUF_SIZE 100
#include <exception>
class SdlException : public std::exception{
  char msg[BUF_SIZE];
  public:
    explicit SdlException(const char* msg)
    {
      snprintf(this->msg, sizeof(this->msg), "%s", msg);
    }
    SdlException() {
      snprintf(this->msg, sizeof(this->msg), "%s", "Error en SDL");
    }
    const char* what() const noexcept{
      return msg;
    }
};
#endif  // SDLEXCEPTION_H
