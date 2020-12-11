#ifndef BLOCKING_QUEUE_Events_H
#define BLOCKING_QUEUE_Events_H
#include <condition_variable>
#include <mutex>
#include <queue>
#include <iostream>
#include <string>
#include "common_thread.h"
#include "blocking_queue_exception.h"


class BlockingQueueEvents : public std::exception {
  private:
    std::queue<std::string> queue;
    std::condition_variable cond_var;
    bool isBlocked;
    std::mutex m;

  public:
    BlockingQueueEvents();

    ~BlockingQueueEvents();

    std::string get_element();

    void add_element(std::string element);

    bool is_closed();

    void close_queue();
};

#endif
