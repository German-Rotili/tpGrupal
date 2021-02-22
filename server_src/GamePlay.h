#ifndef GAMEPLAY
#define GAMEPLAY

#include <vector>
#include "../common_src/common_thread.h"
#include "../common_src/Serializer.h"
#include "IdMaker.h"
#include "../common_src/ProtectedQueueIntention.h"
#include "../common_src/BlockingQueueSnapshot.h"
#include "../common_src/Snapshot.h"
#include <iostream>
#include <utility>
#include <chrono>
#include "ThClient.h"
#include "ThClientSender.h"
#include "Map.h"
#include "Door.h"
#include "Constants.h"
#include "Enemy.h"

class ThClient; 
class ThClientSender; 
class GameHandler;


class GamePlay : public Thread{
private:
    int id;
    int host_id;
    bool state;
    bool blocked;
    std::vector<std::vector<char>> usernames;
    ProtectedQueueIntention *intentions;
    std::vector <ThClient*> clients;
    std::vector <Enemy*> enemys;
    std::vector <ThClientSender*> client_senders;
    Map map; 
    void append_players(Snapshot &snapshot);
    void append_objects(Snapshot &snapshot);
    void append_doors(Snapshot &snapshot);
    void append_actions(Snapshot &snapshot);
    void append_rockets(Snapshot &snapshot);
    std::vector<int> load_players();
    void send_scores();
    void load_enemys(std::vector<int> &players_id);
public:
    GamePlay(ThClient *player, Map&& map, int id);
    ~GamePlay();
    std::vector<std::vector<char>>  &get_usernames();
    void stop();
    bool is_blocked();
    void add_client(ThClient* client);
    void start_game();
    int get_id();
    void run() override;
    GamePlay& operator=(const GamePlay&) = delete;
    GamePlay(const GamePlay&) = delete;
    Snapshot get_snapshot();
    void notify_players(int & current_id);
    std::vector<char> get_raw_map();
};
#endif