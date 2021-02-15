#ifndef Protected_QUEUE_ACTION
#define Protected_QUEUE_ACTION
#include <mutex>
#include <queue>
#include <iostream>
#include <string>
#include "ProtectedQueueException.h"
#include "Action.h"

class ProtectedQueueAction : public std::exception {
  private:
    std::queue<Action> queue;
    bool isBlocked;
    std::mutex m;

  public:
    ProtectedQueueAction();

    ~ProtectedQueueAction();

    Action get_element();

    void add_element(Action action);

    bool is_closed();

    bool is_empty();

    void close_queue();
};

#endif
