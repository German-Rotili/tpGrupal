#include "IdMaker.h"

IdMaker::~IdMaker(){}

int IdMaker::generate_id(){
  std::unique_lock<std::mutex> lock(this->m);
  this->current +=1;
  return this->current;
}


IdMaker::IdMaker(){
    this->current == 0;
}
