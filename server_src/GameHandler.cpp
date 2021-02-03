#include "GameHandler.h"

GameHandler::GameHandler(){}

GameHandler::~GameHandler(){}

GamePlay & GameHandler::select_match(std::string id){
    GamePlay* gp = new GamePlay();
    return *gp;
    // for (auto & game : this->games) {
    //     //this->games.push_back(game.get_id());
    // }
    
}

GamePlay & GameHandler::new_match(){
    GamePlay *gp = new GamePlay();//new?
    // games.push_back(gp);//move?
    return *gp;
}

std::vector<int> GameHandler::get_matches_id(){
    std::vector<int> games_id;
    for (auto & game : this->games) {
        games_id.push_back(game.get_id());
    }
    return games_id;
}