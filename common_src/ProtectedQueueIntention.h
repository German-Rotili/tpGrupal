#ifndef Protected_QUEUE_INTENTION_H
#define Protected_QUEUE_INTENTION_H
#include <mutex>
#include <queue>
#include <iostream>
#include <string>
#include "ProtectedQueueException.h"
#include "Intention.h"

class ProtectedQueueIntention : public std::exception {
  private:
    std::queue<Intention> queue;
    bool isBlocked;
    std::mutex m;

  public:
    ProtectedQueueIntention();

    ~ProtectedQueueIntention();

    Intention get_element();

    void add_element(Intention intention);

    bool is_closed();

    bool is_empty();

    void close_queue();
};

#endif
