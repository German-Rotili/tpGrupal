#include "GameHandler.h"
#include <string>
#include <vector>
#include "ThClient.h"
#include "../common_src/MapHandler.h"
#include "GamePlay.h"

GameHandler::GameHandler(){}

GameHandler::~GameHandler(){
    for (auto & game : this->games) {
        delete game;
    }
}

GamePlay & GameHandler::select_match(ThClient & player, int id){
    GamePlay* game_selected = nullptr;
    for (auto & game : this->games) {
        if(game->get_id() == id){
            game_selected = game;
            game_selected->add_client(&player);
            //game_selected->notify_players();
            break;
        }
    }
    return *game_selected;
}

GamePlay & GameHandler::new_match(ThClient & player, std::vector<char> & map_data){
    Map map(map_data);
    GamePlay *gp = new GamePlay(&player, std::move(map));
    this->games.push_back(gp);
    return *gp;
}

std::vector<int>  GameHandler::get_matches_id(){
    std::vector<int> games_id;
    for (auto & game : this->games) {
        games_id.push_back(game->get_id());
    }
    return games_id;
}