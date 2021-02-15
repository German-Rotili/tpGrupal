#ifndef Empty_QUEUE_EXCEPTION_H
#define Empty_QUEUE_EXCEPTION_H
#include <iostream>

class EmptyQueueException : public std::exception{
  public:
  const char *what();
};

#endif
