#ifndef ENEMY_H
#define ENEMY_H
#include "../common_src/Intention.h"
#include "../common_src/common_thread.h"
#include "../common_src/common_thread.h"
#include "../common_src/ProtectedQueueIntention.h"
#include "../common_src/BlockingQueueSnapshot.h"
#include "Constants.h"
#include "../common_src/Snapshot.h"
#include <vector>
#include <chrono>
#include <utility>
#include <unistd.h>  // Para usleep
#include <sstream>
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

class Enemy : public Thread{
private:
    lua_State *L;
    int enemy_id;
    std::vector<std::vector<int>> & map;
    ProtectedQueueIntention *intentions;
    BlockingQueueSnapshot snapshots;
    std::vector<int> players_id;
    void attack_players(std::vector<char> & intention);

public:
    void run() override;
    void stop();
    explicit Enemy(int id, ProtectedQueueIntention * intention, 
        std::vector<int> players_id, std::vector<std::vector<int>> & map);
    ~Enemy();
friend class GamePlay;
};
#endif
