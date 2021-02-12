#ifndef TH_SENDER
#define TH_SENDER
#include "../common_src/common_thread.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_exception.h"
#include <atomic>
#include "client_helper.h"
#define FPS 30

class ThSender: public Thread{

    /* data */
    std::atomic<bool> state;
    Client & client;
    std::vector<char> & intention;

public:
    void send_intention(std::vector<char> & intention);
    ThSender(Client & client, std::vector<char> & intention);
    void run() override;
    void stop();
    ThSender(const ThSender&) = delete;
    ThSender& operator=(const ThSender&) = delete;
    ~ThSender();
    void clean_intention();

};
#endif
