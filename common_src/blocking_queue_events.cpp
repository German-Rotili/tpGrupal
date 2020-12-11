#include "blocking_queue_events.h"
#include <string>

BlockingQueueEvents::BlockingQueueEvents() : isBlocked(false) {}

BlockingQueueEvents::~BlockingQueueEvents(){}

std::string BlockingQueueEvents::get_element(){
  while (true) {
    std::unique_lock<std::mutex> lock(m);
    if (isBlocked && queue.empty()) {
      throw BlockingQueueGetException();
    }
    if (queue.empty() == 0) {
      std::string element = queue.front();
      queue.pop();
      return element;
    } else{
      cond_var.wait(lock);
    }
  }
}

void BlockingQueueEvents::add_element(std::string element){
  std::unique_lock<std::mutex> lock(m);
  queue.push(element);
  cond_var.notify_all();
}

bool BlockingQueueEvents::is_closed(){
  std::unique_lock<std::mutex> lock(m);
  return isBlocked;
}

void BlockingQueueEvents::close_queue(){
  std::unique_lock<std::mutex> lock(m);
  isBlocked = true;
  cond_var.notify_all();
}
