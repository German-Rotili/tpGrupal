#ifndef GAMEPLAY
#define GAMEPLAY
#include <vector>
#include "../common_src/common_thread.h"
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
    std::vector <ThClient*> clients;
    Map map;
public:
    GamePlay();
    ~GamePlay();
    void add_client(ThClient* client);
    int get_id();
    void run() override;
    GamePlay& operator=(const GamePlay&) = delete;
    GamePlay(const GamePlay&) = delete;

    //tiene una cola bloqueante de eventos, un mapa, una lista de jugadores y el game loop.
};
#endif