#ifndef GAMEHANDLER
#define GAMEHANDLER
#include "GamePlay.h"
#include <string>
#include <vector>

//incluir locks
class GameHandler{
private:
    /* data */
    //lista de partidas
    std::vector<GamePlay> games;
public:
    GamePlay & select_match(std::string id);
    GamePlay & new_match();//crea una cola bloqueante de eventos
    std::vector<int> get_matches_id();
    GameHandler(/* args */);
    ~GameHandler();
};
#endif