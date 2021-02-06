#ifndef GAMEPLAY
#define GAMEPLAY
#include <vector>
// #include "Map.h"

class GamePlay{
private:
    int id;
    // Map & map;
public:
    GamePlay();
    // GamePlay(Map & map);
    ~GamePlay();
    int get_id();
    std::vector <char> get_snapshot();

    //tiene una cola bloqueante de eventos, un mapa, una lista de jugadores y el game loop.
};
#endif