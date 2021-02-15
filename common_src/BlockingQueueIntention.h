#ifndef BLOCKING_QUEUE_INTENTIONS_H
#define BLOCKING_QUEUE_INTENTIONS_H
#include <condition_variable>
#include <mutex>
#include <queue>
#include <iostream>
#include <string>
#include "common_thread.h"
#include "Intention.h"
#include "ProtectedQueueException.h"


class BlockingQueueIntention : public std::exception {
  private:
    std::queue<Intention> queue;
    std::condition_variable cond_var;
    bool isBlocked;
    std::mutex m;

  public:
    BlockingQueueIntention();

    ~BlockingQueueIntention();

    Intention get_element();

    void add_element(Intention element);

    bool is_closed();

    void close_queue();
};

#endif
