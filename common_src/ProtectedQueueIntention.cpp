#include "ProtectedQueueIntention.h"
#include <string>

ProtectedQueueIntention::ProtectedQueueIntention() : isBlocked(false) {}

ProtectedQueueIntention::~ProtectedQueueIntention(){}

Intention ProtectedQueueIntention::get_element(){
    std::unique_lock<std::mutex> lock(m);
    if (isBlocked && queue.empty()) {
      throw ProtectedQueueException();
    }else if (!queue.empty()) {
      Intention element = queue.front();
      queue.pop();
      return element;
    }else{
      std::cout << "Temporarily empty" << std::endl;
    }
}

void ProtectedQueueIntention::add_element(Intention element){
  std::unique_lock<std::mutex> lock(m);
  queue.push(element);
}

bool ProtectedQueueIntention::is_empty(){
  std::unique_lock<std::mutex> lock(m);
  return this->queue.empty();
}

bool ProtectedQueueIntention::is_closed(){
  std::unique_lock<std::mutex> lock(m);
  return isBlocked;
}

void ProtectedQueueIntention::close_queue(){
  std::unique_lock<std::mutex> lock(m);
  isBlocked = true;
}
