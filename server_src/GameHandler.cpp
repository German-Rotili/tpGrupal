#include "GameHandler.h"

GameHandler::GameHandler(){}

GameHandler::~GameHandler(){
    for (auto & game : this->games) {
        delete game;
    }
}

GamePlay & GameHandler::select_match(std::string id){
    GamePlay* game_selected;
    for (auto & game : this->games) {
        if(game->get_id() == std::stoi(id)){
            game_selected = game;
            break;
        }
    }
    return *game_selected;
}

GamePlay & GameHandler::new_match(ThClient & player, std::string & map_data){
    std::vector<std::vector<int>> map_aux = this->map_handler.readMapFromString(map_data);
    Map map(map_aux);
    GamePlay *gp = new GamePlay(player, std::move(map));
    this->games.push_back(gp);
    return *gp;
}

std::vector<int> GameHandler::get_matches_id(){
    std::vector<int> games_id;
    for (auto & game : this->games) {
        games_id.push_back(game->get_id());
    }
    return games_id;
}