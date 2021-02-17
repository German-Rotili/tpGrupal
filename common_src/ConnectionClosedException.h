#ifndef ConnectionClosedException_H
#define ConnectionClosedException_H
#include <iostream>

class ConnectionClosedException : public std::exception{
  public:
  const char *what();
};

#endif
