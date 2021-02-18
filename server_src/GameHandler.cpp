#include "GameHandler.h"
#include <string>
#include <vector>
#include "ThClient.h"
#include "../common_src/MapHandler.h"
#include "GamePlay.h"

GameHandler::GameHandler(){
    id_maker = IdMaker::GetInstance();
}

GameHandler::~GameHandler(){}

void GameHandler::end_games(){
    for (GamePlay *game : this->games) {
        game->stop();
        game->join();
        delete game;
    }
}

GamePlay & GameHandler::select_match(ThClient & player, int id){
    GamePlay* game_selected = nullptr;
    for (auto & game : this->games) {
        if(game->get_id() == id){
            game_selected = game;
            player.client_id = id_maker->generate_id();
            game_selected->add_client(&player);
            game_selected->notify_players(player.get_id());
            break;
        }
    }
    return *game_selected;
}

GamePlay & GameHandler::new_match(ThClient & player, std::vector<char> & map_data){
    Map map(map_data);
    GamePlay *gp = new GamePlay(&player, std::move(map),id_maker->generate_id());
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