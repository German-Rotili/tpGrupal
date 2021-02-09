#ifndef GAMEHANDLER
#define GAMEHANDLER


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