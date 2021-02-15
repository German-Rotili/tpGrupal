#ifndef BLOCKING_QUEUE_SNAPSHOT
#define BLOCKING_QUEUE_SNAPSHOT
#include <condition_variable>
#include <mutex>
#include <queue>
#include <iostream>
#include <string>
#include "common_thread.h"
#include "Snapshot.h"
#include "ProtectedQueueException.h"


class BlockingQueueSnapshot : public std::exception {
  private:
    std::queue<Snapshot> queue;
    std::condition_variable cond_var;
    bool isBlocked;
    std::mutex m;

  public:
    BlockingQueueSnapshot();

    ~BlockingQueueSnapshot();

    Snapshot get_element();

    void add_element(Snapshot element);

    bool is_closed();

    void close_queue();
};

#endif
