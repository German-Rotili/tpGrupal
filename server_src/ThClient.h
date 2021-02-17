#ifndef __SERVER_THCLIENT_H__
#define __SERVER_THCLIENT_H__

#include "../common_src/Protocol.h"
#include "GameHandler.h"
#include "GamePlay.h"
#include "../common_src/common_thread.h"
#include "../common_src/ProtectedQueueIntention.h"
#include <vector>
#include <string>
#include <utility>
#include "../common_src/Serializer.h"
#include "ThClientSender.h"
#include "Constants.h"
#include <mutex>
class GameHandler;
class GamePlay;


class ThClient : public Thread{
private:
    int client_id;
    Protocol protocol;
    ProtectedQueueIntention *intentions;
    std::mutex m;
    std::vector<char> username;
    bool state = true;
    GameHandler & game_handler;
    ThClient& operator=(const ThClient&) = delete;
    ThClient(const ThClient&) = delete;
    void receive_username();
    void new_game();
    void join_game();
    void refresh_players(std::vector<std::vector<char>> & usernames);
    void refresh_matches();
    void receiver_loop();

public:
    ThClient(Protocol&& Protocol, GameHandler & game_handler);
    ~ThClient();
    void run() override;
    void start_game();
    void notify_players(std::vector<std::vector<char>> &usernames);
    void attach_queue(ProtectedQueueIntention * intentions);
    int & get_id();
    /*Devuelve el estado del thread*/
    bool is_dead();
friend class GamePlay;
};


#endif // __SERVER_THCLIENT_H__
