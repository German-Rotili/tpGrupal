#ifndef BLOCKING_QUEUE_EXCEPTION_H
#define BLOCKING_QUEUE_EXCEPTION_H
#include <iostream>

class BlockingQueueGetException : public std::exception{
  public:
  const char *what();
};

#endif
