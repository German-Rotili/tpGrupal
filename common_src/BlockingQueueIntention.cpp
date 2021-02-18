#include "BlockingQueueIntention.h"
#include <string>

BlockingQueueIntention::BlockingQueueIntention() : isBlocked(false) {}

BlockingQueueIntention::~BlockingQueueIntention(){
  isBlocked = true;
}

Intention BlockingQueueIntention::get_element(){
  while (true) {
    std::unique_lock<std::mutex> lock(m);
    if (isBlocked && queue.empty()) {
      throw ProtectedQueueException();
    }
    if (queue.empty() == 0) {
      Intention element = queue.front();
      queue.pop();
      return element;
    } else{
      cond_var.wait(lock);
    }
  }
}

void BlockingQueueIntention::add_element(Intention element){
  std::unique_lock<std::mutex> lock(m);
  queue.push(element);
  cond_var.notify_all();
}

bool BlockingQueueIntention::is_closed(){
  std::unique_lock<std::mutex> lock(m);
  return isBlocked;
}

void BlockingQueueIntention::close_queue(){
  std::unique_lock<std::mutex> lock(m);
  isBlocked = true;
  cond_var.notify_all();
}
