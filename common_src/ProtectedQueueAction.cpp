#include "ProtectedQueueAction.h"

ProtectedQueueAction::ProtectedQueueAction() : isBlocked(false) {}

ProtectedQueueAction::~ProtectedQueueAction(){
  std::cout << "Destruyendo queueaction" << std::endl;
}

Action ProtectedQueueAction::get_element(){
    std::unique_lock<std::mutex> lock(m);
    if (isBlocked && queue.empty()) {
      throw ProtectedQueueException();
    }else if (!queue.empty()) {
      Action element = queue.front();
      queue.pop();
      return element;
    }
    throw ProtectedQueueException();
}

void ProtectedQueueAction::add_element(Action element){
  std::unique_lock<std::mutex> lock(m);
  queue.push(element);
}

bool ProtectedQueueAction::is_empty(){
  std::unique_lock<std::mutex> lock(m);
  return this->queue.empty();
}

bool ProtectedQueueAction::is_closed(){
  std::unique_lock<std::mutex> lock(m);
  return isBlocked;
}

void ProtectedQueueAction::close_queue(){
  std::unique_lock<std::mutex> lock(m);
  isBlocked = true;
}
