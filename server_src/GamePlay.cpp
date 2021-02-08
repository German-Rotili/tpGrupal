#include "GamePlay.h"

GamePlay::GamePlay(){}

GamePlay::~GamePlay(){}


void GamePlay::add_client(ThClient* client){
    this->clients.push_back(client);
}


void GamePlay::run(){

        while (this->state){
            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
            
            for(auto &client : this->clients){
                this->map.execute_intentions(client->intention_queue);
            }

            Snapshot snapshot = this->map.get_snapshot();
            
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

