#include "server_ThServer.h"
#include "../common_src/common_socket_exception.h"
#include <string>
#include <vector>

ThServer::ThServer(std::string & port, std::string & root):
        state(true),root(root){
    server.socket_reuse();
    server.socket_bind(port.c_str());
    server.socket_listen(THREADS_NUM);
}
static const void remove_dead(std::vector<Thread*> & list){
    std::vector<Thread*> temp;
    std::vector<Thread*> ::iterator it = list.begin();
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
    int a = 500;
    std::string dir = "u";
    std::vector<Thread*> threads;
    try {
        while (state){
            Socket peer;
            Player player(a, a, dir);
            map->add_player(player);
            peer.socket_accept(server);
            threads.push_back(new 
                ThClient(std::move(peer), player, *map));
            (threads.back())->start();
            remove_dead(threads);
        }


        
    }catch(CloseSocketException& e){
        clean_clients(threads);
    }catch(std::exception& e){
        perror(e.what());
    }catch(...){}
}

void ThServer::stop(){
    this->state = false;
    this->server.socket_shutdown(SHUT_RDWR);
}

void ThServer::clean_clients(std::vector<Thread*> threads){
    for (int i = 0; i < (int)threads.size(); ++i) {
        threads[i]->join();
        delete threads[i];
    }
}

ThServer::~ThServer(){}
