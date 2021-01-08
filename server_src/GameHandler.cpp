#include "GameHandler.h"

GameHandler::GameHandler(){}

GameHandler::~GameHandler(){}

GamePlay & GameHandler::select_match(std::string id){
    GamePlay* gp = new GamePlay();
    return *gp;
}

GamePlay GameHandler::new_match(){
    GamePlay gp;
    return gp;
}

std::string GameHandler::show_matches(){
    std::string ret = "No hay partidas disponibles";
    return ret;
}