#include "blocking_queue_exception.h"

const char* BlockingQueueGetException::what(){
  return "No elements in queue.";
}
