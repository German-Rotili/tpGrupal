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
    /* data */
    std::atomic<bool> state;
    Client & client;
    player_t player_thread;
    std::vector <Action*> & actions;
    intention_t & intention;
    player_t  player_client;// = {0,0,0,0,0,'0'};

public:
    void send_intention(intention_t & intention);
    ThRequester(Client & client, intention_t & intention, std::vector <Action*> & actions);
    ~ThRequester();
    void get_snapshot(player_t & player);
    void run() override;
    /*Cierra el socket de forma violenta*/
    void stop();
    ThRequester(const ThRequester&) = delete;
    ThRequester& operator=(const ThRequester&) = delete;
};
#endif