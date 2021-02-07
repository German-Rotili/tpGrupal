#ifndef TH_REQUESTER
#define TH_REQUESTER
#include "../common_src/common_thread.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_exception.h"
#include "../common_src/Action.h"
#include <atomic>
#include "client_helper.h"
#define FPS 30


class ThRequester : public Thread{
private:
    std::atomic<bool> state;
    Client & client;
    player_t player_thread;
    std::vector <Action*> & actions;
    player_t  player_client;

public:
    ThRequester(Client & client, std::vector <Action*> & actions);
    ~ThRequester();
    void get_snapshot(player_t & player);
    void run() override;
    void stop();
    ThRequester(const ThRequester&) = delete;
    ThRequester& operator=(const ThRequester&) = delete;
};
#endif