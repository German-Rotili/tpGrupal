#ifndef Protected_QUEUE_EXCEPTION_H
#define Protected_QUEUE_EXCEPTION_H
#include <iostream>

class ProtectedQueueException : public std::exception{
  public:
  const char *what();
};

#endif
