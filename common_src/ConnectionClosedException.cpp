#include "ConnectionClosedException.h"

const char* ConnectionClosedException::what(){
  return "Connection Closed";
}
