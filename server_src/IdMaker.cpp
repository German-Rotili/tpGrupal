#include "IdMaker.h"

IdMaker::~IdMaker(){}

IdMaker* IdMaker::instance{nullptr};
std::mutex IdMaker::m;

IdMaker *IdMaker::GetInstance()
{
    std::lock_guard<std::mutex> lock(m);
    if (instance == nullptr){
        instance = new IdMaker();
    }
    return instance;
}

int IdMaker::generate_id(){
  std::unique_lock<std::mutex> lock(this->m);
  this->current +=1;
  return this->current;
}


IdMaker::IdMaker(){
    this->current = 0;
}
