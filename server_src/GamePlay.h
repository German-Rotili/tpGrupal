#ifndef GAMEPLAY
#define GAMEPLAY
#include <vector>
#include "../common_src/common_thread.h"
#include "../common_src/Serializer.h"
#include "../common_src/Snapshot.h"
#include <iostream>
#include <utility>
#include <chrono>
#include "ThClient.h"
#include "Map.h"


#define FPS 30

class GamePlay : public Thread{
private:
    int id;
    bool state;
    std::vector <ThClient&> clients;
    Map map;
public:
    GamePlay(ThClient & player, Map&& map);
    ~GamePlay();
    void add_client(ThClient & client);
    void start();
    int get_id();
    void run() override;
    GamePlay& operator=(const GamePlay&) = delete;
    GamePlay(const GamePlay&) = delete;
    Snapshot get_snapshot();


};
#endif