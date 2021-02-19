#include "ThServer.h"
#include <atomic>
#include <vector>
#include <string>
#include <utility>
#include "ThClient.h"
#include "GameHandler.h"
#include "../common_src/common_thread.h"
#include "../common_src/common_socket.h"
#include "../common_src/common_exception.h"
#include "../common_src/Protocol.h"
#include "../common_src/common_socket_exception.h"

ThServer::ThServer(std::string & port):
        state(true){
    server.socket_reuse();
    server.socket_bind(port.c_str());
    server.socket_listen(THREADS_NUM);
}
static const void remove_dead(std::vector<ThClient*> & list){
    std::vector<ThClient*> temp;
    std::vector<ThClient*> ::iterator it = list.begin();
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

void ThServer::run(){
    try {
        while (this->state){
            Socket peer;
            server.socket_accept(peer);
            Protocol protocol(std::move(peer));
            this->threads.push_back(new 
                ThClient(std::move(protocol), this->game_handler));

            (this->threads.back())->start();
            remove_dead(this->threads);
        }
    }catch(std::exception& e){
        perror(e.what());
    }catch(...){}
}

void ThServer::stop(){
    this->state = false;
    this->server.socket_shutdown(SHUT_RDWR);
}

void ThServer::clean_clients(std::vector<ThClient*> threads){
    for (int i = 0; i < (int)threads.size(); ++i) {
        threads[i]->stop();
        threads[i]->join();
        delete threads[i];
    }
}

ThServer::~ThServer(){
    this->game_handler.end_games();
    clean_clients(threads);
}
