#ifndef TH_SENDER
#define TH_SENDER
#include "../common_src/common_thread.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_exception.h"
#include "../common_src/BlockingQueueIntention.h"
#include <atomic>
#include "client_helper.h"
#define FPS 30

class ThSender: public Thread{
    std::atomic<bool> state;
    Client & client;
    BlockingQueueIntention & intentions;

public:
    void send_intention(std::vector<char> & intention);
    ThSender(Client & client,BlockingQueueIntention & intentions);
    void run() override;
    void stop();
    ThSender(const ThSender&) = delete;
    ThSender& operator=(const ThSender&) = delete;
    ~ThSender();
    // void clean_intention();

};
#endif
