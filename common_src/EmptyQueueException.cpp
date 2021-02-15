#include "EmptyQueueException.h"

const char* EmptyQueueException::what(){
  return "Queue empty";
}
