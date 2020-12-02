#ifndef THREAD_H
#define THREAD_H
#include <thread>
#include <utility>
#include <atomic>

class Thread {
  private:
    std::thread thread;
    
  public:
    std::atomic<bool> dead;

    Thread();

    bool is_dead();

    void start();

    void join();

    virtual void run() = 0;

    virtual ~Thread();

    Thread(const Thread&) = delete;

    Thread& operator=(const Thread&) = delete;

    Thread(Thread&&);

    Thread& operator=(Thread&&);
};
#endif
