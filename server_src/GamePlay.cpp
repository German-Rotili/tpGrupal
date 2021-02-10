#include "GamePlay.h"
#include <vector>
#include "../common_src/common_thread.h"
#include "../common_src/Serializer.h"
#include "../common_src/Snapshot.h"
#include <iostream>
#include <utility>
#include <chrono>
#include "ThClient.h"
#include "Map.h"
#include "weapons/Rocket.h"
#include "IdMaker.h"

GamePlay::GamePlay(ThClient *player, Map&& map):map(map){
    this->add_client(player);
    IdMaker IdMaker;
    this->id = IdMaker.generate_id()+100;
    std::cout << this->id <<std::endl;
}

GamePlay::~GamePlay(){}


void GamePlay::add_client(ThClient* client){
    this->clients.push_back(client);
}
std::vector<char> GamePlay::get_raw_map(){
    return this->map.get_raw_map();
}


void GamePlay::append_players(Snapshot & snapshot){
    for(Player &player : this->map.players){
        player_t *player_aux = new player_t;
        player_aux->player_id;
        player_aux->pos_x;
        player_aux->pos_y;
        player_aux->direction;
        player_aux->current_weapon;
        player_aux->ammo;
        player_aux->health;
        player_aux->lives;
        player_aux->score;
        snapshot.add_player(player_aux);
    }
}

void GamePlay::append_objects(Snapshot &snapshot){
   for(auto &x : this->map.items){
       object_t *object_aux = new object_t;
     for(auto &y : x.second){
         object_aux->id = y.second;
         object_aux->pos_x = x.first;
         object_aux->pos_y = y.first;
         object_aux->state = false;
        snapshot.add_object(object_aux);
       }
     }
}
void GamePlay::append_doors(Snapshot &snapshot){
    for(auto &x : this->map.doors){
       object_t *object_aux = new object_t;
        for(auto &y : x.second){
         object_aux->id = 34;
         object_aux->pos_x = x.first;
         object_aux->pos_y = y.first;
         object_aux->state = y.second.is_open();
         snapshot.add_object(object_aux);
       }
    }
}
void GamePlay::append_actions(Snapshot &snapshot){
    for(Action *action : this->map.actions){
       Action *action_aux = new Action(action->player_id);
       action_aux->update_values(action->impact_x, action->impact_y, action->weapon_id);
       snapshot.add_action(action_aux);
       //deberia borrar la lista de acciones.
    }
}
void GamePlay::append_rockets(Snapshot &snapshot){
    for(Rocket &rocket : this->map.rockets){
         object_t *object_aux = new object_t;
         object_aux->id = 35;
         object_aux->pos_x = rocket.get_pos_x();
         object_aux->pos_y = rocket.get_pos_y();
         object_aux->state = false;
         snapshot.add_object(object_aux);
    }
}


Snapshot GamePlay::get_snapshot(){
    Snapshot snapshot;
    this->append_players(snapshot);
    this->append_objects(snapshot);
    this->append_doors(snapshot);
    this->append_actions(snapshot);
    this->append_rockets(snapshot);
    return snapshot;
}


/*GAME LOOP*/
void GamePlay::run(){
                std::cout << "partida run" << std::endl;

        while (this->state){
                std::cout << "game loop" << std::endl;

            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
            for(auto &client : this->clients){
                this->map.execute_intentions(client->intention_queue, client->client_id);
            }
            Snapshot snapshot = this->get_snapshot();
            for(auto &client : this->clients){
                client->send_snapshot(snapshot);
            }
            std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
            unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
            int sleep_time = 1000000/FPS - elapsed_microseconds;
            if (sleep_time > 0) {
                usleep(1000000/FPS - elapsed_microseconds);
            }else{
                std::cout << "Bajada FPS" << std::endl;
            }
        }
}


int GamePlay::get_id(){
    return this->id;
}

void GamePlay::notify_players(int & current_id){
    std::vector<std::string> usernames;
    for(ThClient *client : this->clients){
        usernames.push_back(client->username);
        std::cout << " username name: "<<client->username<< std::endl;
    }
    std::cout << " cantidad de usernames: "<<usernames.size()<< std::endl;


    for(ThClient *client : this->clients){
        if(client->client_id ==current_id){
            continue;
        }
        client->notify_players(usernames);
        std::cout << "Envio usernames a cliente"<< std::endl;

    } 
}


void GamePlay::start(int & current_id){
    this->state = true;
    for(ThClient *client : this->clients){
         if(client->client_id !=current_id){
            client->start_game();
        }
    }
    this->run();
}
