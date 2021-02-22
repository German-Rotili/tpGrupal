#include "GamePlay.h"
#include <vector>
#include "../common_src/common_thread.h"
#include "../common_src/Serializer.h"
#include "../common_src/BlockingQueueSnapshot.h"
#include "../common_src/EmptyQueueException.h"
#include "../common_src/Snapshot.h"
#include <iostream>
#include <utility>
#include <chrono>
#include "ThClient.h"
#include "Map.h"
#include "weapons/Rocket.h"
#include "Constants.h"
#include "IdMaker.h"

/*Static*/

static const void remove_dead(std::vector<ThClientSender*> & list){
    std::vector<ThClientSender*> temp;
    std::vector<ThClientSender*> ::iterator it = list.begin();
    for (; it != list.end(); ++it){
        if ((*it)->is_dead()){
            (*it)->join();
            delete (*it);
        } else{
            temp.push_back((*it));
        }
    }
    list.swap(temp);
}

/********/

/*INIT*/
GamePlay::GamePlay(ThClient *player, Map&& map, int id):map(map),state(false), id(id),blocked(false){
    this->add_client(player);
    this->host_id = player->client_id;
    this->intentions = new ProtectedQueueIntention();
}

GamePlay::~GamePlay(){
    for(ThClientSender *sender : this->client_senders){
        sender->stop();
        sender->join();
        delete sender;
    }
    for(Enemy *enemy : this->enemys){
        enemy->stop();
        enemy->join();
        delete enemy;
    }
    delete this->intentions;
}

std::vector<std::vector<char>> & GamePlay::get_usernames(){
    return this->usernames;
}

void GamePlay::add_client(ThClient* client){
    this->clients.push_back(client);
    this->usernames.push_back(client->username);
}

std::vector<char> GamePlay::get_raw_map(){
    return this->map.get_raw_map();
}
/******/


/*Snapshot Handlers*/
Snapshot GamePlay::get_snapshot(){
    Snapshot snapshot;
    this->append_players(snapshot);
    this->append_objects(snapshot);
    this->append_doors(snapshot);
    this->append_actions(snapshot);
    this->append_rockets(snapshot);
    return snapshot;
}

void GamePlay::append_players(Snapshot & snapshot){
    for(Player *player : this->map.players){
        player_t player_aux;
        player_aux.player_id = player->get_id();
        player_aux.pos_x = player->get_pos_x();
        player_aux.pos_y = player->get_pos_y();
        player_aux.direction = player->get_direction();
        player_aux.current_weapon = player->get_current_weapon_id();
        player_aux.ammo = player->get_ammo();
        player_aux.health = player->get_hitpoints();
        player_aux.lives = player->get_lives();
        player_aux.score = player->get_score();
        snapshot.add_player(player_aux);
    }
}

void GamePlay::append_objects(Snapshot &snapshot){
   for(auto &x : this->map.items){
        object_t object_aux;
        for(auto &y : x.second){
            object_aux.id = y.second;
            object_aux.pos_x = x.first;
            object_aux.pos_y = y.first;
            object_aux.state = false;
            snapshot.add_object(object_aux);
        }
    }
}

void GamePlay::append_doors(Snapshot &snapshot){
    for(auto &x : this->map.doors){
       object_t object_aux;
        for(auto &y : x.second){
         object_aux.id = 34;
         object_aux.pos_x = x.first;
         object_aux.pos_y = y.first;
         object_aux.state = y.second.is_open();
         snapshot.add_object(object_aux);
       }
    }
}

void GamePlay::append_actions(Snapshot &snapshot){
    for(Action action : this->map.actions){
       Action action_aux(action.player_id);
       action_aux.update_values(action.impact_x, action.impact_y, action.weapon_id);
       snapshot.add_action(action_aux);
    }
    this->map.actions.clear();
}

void GamePlay::append_rockets(Snapshot &snapshot){
    for(Rocket *rocket : this->map.rockets){
         object_t object_aux;
         object_aux.id = 35;
         object_aux.pos_x = rocket->get_pos_x();
         object_aux.pos_y = rocket->get_pos_y();
         object_aux.state = false;
         snapshot.add_object(object_aux);
    }
}
/******************/


/*GAME LOOP*/
void GamePlay::run(){
        this->map.start();
        this->blocked = true;
        this->state = true;
        while (this->state && !this->map.is_game_over()){
            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

            int index = 0;
            this->map.tick();
            while (!this->intentions->is_empty() || index == MAX_INTENTION_PER_FRAME){//analizar poner una cantidad fija para que no se llene mientras loopea EJ hacer un FOR
                try{
                    Intention intention_aux = this->intentions->get_element();
                    this->map.execute_intentions(intention_aux.get_intention(), intention_aux.get_id());
                    index+=1;
                }
                catch(const EmptyQueueException& e){}
            }

            Snapshot snapshot = this->get_snapshot();
            remove_dead(this->client_senders);
            for(ThClientSender *client_s : this->client_senders){
                if (!client_s->snapshots.is_closed()){
                    client_s->snapshots.add_element(snapshot);
                }
            }
            for(Enemy *enemy : this->enemys){
                if (!enemy->snapshots.is_closed()){
                    enemy->snapshots.add_element(snapshot);
                }
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

        this->send_scores();
}
/**********/


/*Auxiliares*/

void GamePlay::send_scores(){
    std::vector<char> username;
    for(ThClientSender *sender : this->client_senders){
        sender->send_scores(this->map.players.size());
        for(Player *player : this->map.players){
            sender->send_score(player->get_username(), player->get_score(), player.get_kills(), player.get_shots() );
        }
    }
}


void GamePlay::notify_players(int & current_id){
    for(ThClient *client : this->clients){
        if(client->client_id != current_id && client->client_id != this->host_id){
            client->notify_players(this->usernames);
        }
    }
}

int GamePlay::get_id(){
    return this->id;
}

void GamePlay::start_game(){
    std::vector<int> players_id = load_players();
    load_enemys(players_id);
}

std::vector<int> GamePlay::load_players(){
    std::vector<int> players_id;
    for(ThClient *client : this->clients){
        client->start_game();
        client->attach_queue(this->intentions);
        players_id.push_back(client->client_id);
        this->map.add_player(client->client_id, client->username);
        this->client_senders.push_back(new ThClientSender(client->protocol));
        this->client_senders.back()->start();
    }
    return players_id;
}

void GamePlay::stop(){
    this->state = false;
    this->blocked = true;
}

bool GamePlay::is_blocked(){
    return this->blocked;
}
/**********/


/*Enemys*/
void GamePlay::load_enemys(std::vector<int> &players_id){
    IdMaker* id_maker = IdMaker::GetInstance();

    for (int i = 0; i < PLAYERS - this->clients.size(); i++){
        int enemy_id = id_maker->generate_id();
        std::string bot_name = "BOT ";
        bot_name.append(std::to_string(enemy_id));
        std::vector<char> data(bot_name.begin(), bot_name.end());
        Enemy *new_enemy = new Enemy(enemy_id, this->intentions, players_id, this->map.map);
        this->enemys.push_back(new_enemy);
        this->map.add_player(enemy_id, data);
        this->enemys.back()->start();
    }
}
/********/