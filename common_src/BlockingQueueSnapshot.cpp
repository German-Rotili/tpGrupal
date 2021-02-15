#include "BlockingQueueSnapshot.h"

BlockingQueueSnapshot::BlockingQueueSnapshot() : isBlocked(false) {}

BlockingQueueSnapshot::~BlockingQueueSnapshot(){}

Snapshot BlockingQueueSnapshot::get_element(){
  while (true) {
    std::unique_lock<std::mutex> lock(m);
    if (isBlocked && queue.empty()) {
      throw ProtectedQueueException();
    }
    if (queue.empty() == 0) {
      Snapshot element = queue.front();
      queue.pop();
      return element;
    } else{
      cond_var.wait(lock);
    }
  }
}

void BlockingQueueSnapshot::add_element(Snapshot element){
  std::unique_lock<std::mutex> lock(m);
  queue.push(element);
  cond_var.notify_all();
}

bool BlockingQueueSnapshot::is_closed(){
  std::unique_lock<std::mutex> lock(m);
  return isBlocked;
}

void BlockingQueueSnapshot::close_queue(){
  std::unique_lock<std::mutex> lock(m);
  isBlocked = true;
  cond_var.notify_all();
}
