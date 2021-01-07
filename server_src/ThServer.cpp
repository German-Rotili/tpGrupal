#include "ThServer.h"
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
    try {
        GameHandler game_handler;//tiene todas las partidas creadas
        while (state){
            Socket peer;
            server.socket_accept(peer);

            //acepto un nuevo cliente, tiene que elegir la partida o crear nueva

            this->threads.push_back(new 
                ThClient(std::move(peer), game_handler));
                
            (this->threads.back())->start();
            remove_dead(this->threads);
        }
       
    }catch(CloseSocketException& e){
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

ThServer::~ThServer(){
    clean_clients(threads);
}
