#ifndef GAMEHANDLER
#define GAMEHANDLER
#include "../common_src/MapHandler.h"
#include "GamePlay.h"
#include "ThClient.h"
class GamePlay;
class ThClient;
//incluir locks
class GameHandler{
private:
    MapHandler map_handler;
    std::vector<GamePlay*> games;
public:
    GamePlay & select_match(ThClient & player, int id);
    GamePlay & new_match(ThClient & player, std::string & map);
    std::vector<int> get_matches_id();
    GameHandler();
    ~GameHandler();
};
#endif