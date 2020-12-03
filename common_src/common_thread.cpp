#include "common_thread.h"
#include <utility>

Thread::Thread() : dead(false){}

void Thread::start() {
  thread = std::thread(&Thread::run, this);
}

void Thread::join() {
  thread.join();
}

Thread::~Thread() {}


bool Thread::is_dead(){
  return dead;
}

Thread::Thread(Thread&& other) {
  this->thread = std::move(other.thread);
}

Thread& Thread::operator=(Thread&& other) {
  this->thread = std::move(other.thread);
  return *this;
}
