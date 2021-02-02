#ifndef GAMEPLAY
#define GAMEPLAY
class GamePlay{
private:
    int id;
public:
    GamePlay(/* args */);
    ~GamePlay();
    int get_id();
    //tiene una cola bloqueante de eventos, un mapa, una lista de jugadores y el game loop.
};
#endif