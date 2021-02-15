#include "ProtectedQueueException.h"

const char* ProtectedQueueException::what(){
  return "Queue closed.";
}
