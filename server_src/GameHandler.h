#ifndef GAMEHANDLER
#define GAMEHANDLER
#include "../common_src/MapHandler.h"
#include "GamePlay.h"
#include "ThClient.h"
class GamePlay;
class ThClient;

class GameHandler{
private:
    MapHandler map_handler;
    std::vector<GamePlay*> games;
public:
    GamePlay & select_match(ThClient & player, int id);
    GamePlay & new_match(ThClient & player, std::vector<char> & map);
    std::vector<int> get_matches_id();
    void end_games();
    GameHandler();
    ~GameHandler();
};
#endif