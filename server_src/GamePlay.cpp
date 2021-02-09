#include "GamePlay.h"

GamePlay::GamePlay(ThClient & player, Map&& map):map(map){
    this->add_client(player);
}

GamePlay::~GamePlay(){}


void GamePlay::add_client(ThClient & client){
    this->clients.push_back(client);
}


Snapshot GamePlay::get_snapshot(){
    Snapshot snapshot;
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
  
    for(Rocket &rocket : this->map.rockets){
         object_t *object_aux = new object_t;
         object_aux->id = 35;
         object_aux->pos_x = rocket.get_pos_x();
         object_aux->pos_y = rocket.get_pos_y();
         object_aux->state = false;
         snapshot.add_object(object_aux);
    }
    

    for(Action &action : this->map.actions){
       Action *action_aux = new Action(action.player_id);
       action_aux->update_values(action.impact_x, action.impact_y, action.weapon_id);
       snapshot.add_action(action_aux);
    }
    return snapshot;

}

void GamePlay::run(){

        while (this->state){
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

void GamePlay::notify_players(){
    std::vector<std::string> usernames;
    for(ThClient &client : this->clients){
        usernames.push_back(client.username);
    }

    for(ThClient &client : this->clients){
        client.notify_players(usernames);
    } 
}


void GamePlay::start(){
    this->state = true;
    for(ThClient &client : this->clients){
        client.start_game();
    }
    this->run();
}
