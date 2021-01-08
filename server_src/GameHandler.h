#ifndef GAMEHANDLER
#define GAMEHANDLER
#include "GamePlay.h"
#include <string>
//incluir locks
class GameHandler{
private:
    /* data */
    //lista de partidas
public:
    GamePlay & select_match(std::string id);
    GamePlay new_match();//crea una cola bloqueante de eventos
    std::string show_matches();
    GameHandler(/* args */);
    ~GameHandler();
};
#endif