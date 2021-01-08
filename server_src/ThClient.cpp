#include "ThClient.h"
#include <string>
#include <vector>
#include <iostream>

void ThClient::run(){
    try {
   std::vector<char> cmd(CHUNK_SZ,0);
        //std::string output = game_handler.show_matches();
        //peer.socket_send(output.c_str(), output.length());
        //Parseo la partida que eligio y la asigno al cliente.
        std::string id;
        //GamePlay *game_play = game_handler.select_match(id);
        while (state){
            std::string petition;
            size_t read = 0;
            


            while ((read = peer.socket_receive(cmd.data(), CHUNK_SZ)) > 0){
                std::string aux(cmd.begin(), cmd.begin()+read);
                petition += aux;
                std::cout << aux << std::endl; 
            }


        

            //creo un hilo para receive y otro para send
            //envio snapshot completa al cliente.
            //peer.socket_send(output.c_str(), output.length());
        }

        dead = true;
        peer.socket_shutdown(SHUT_RDWR);
    }catch(const std::exception& e){
        perror(e.what());
    }catch(...){}  
}

ThClient::ThClient(Socket&& socket, GameHandler & game_handler):game_handler(game_handler){
    this->peer = std::move(socket);
}

ThClient::~ThClient(){
    peer.socket_shutdown(SHUT_RDWR);
}
