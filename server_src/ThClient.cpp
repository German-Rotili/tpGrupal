#include "ThClient.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include "../editor_src/ConfigManager/MapHandler.h"
#include <string>
#include <fstream>
#include <streambuf>
//#include "Player.h"
#include <iterator>
#include "../common_src/Serializer.h"


void ThClient::run(){
    try {

        //std::vector<char> cmd(CHUNK_SZ,0);
        //std::string output = game_handler.show_matches();
        
        //peer.socket_send(output.c_str(), output.length());
       
        //peer.socket_recieve(output.c_str(), output.length());
       
        //Parseo la partida que eligio y la asigno al cliente.

        std::string id;

        GamePlay game_play = game_handler.select_match(id);


        //Instanciar un thread para recibir y otro para mandar

        //Player main_player; new

        // std::ifstream t("../editor_src/config/map1.yaml");
        // std::string str((std::istreambuf_iterator<char>(t)),
        //          std::istreambuf_iterator<char>());

        // uint32_t size_1 = htonl(str.length());
        // peer.socket_send((char*)&size_1, sizeof(uint32_t));
        // peer.socket_send(str.c_str(), size_1);



        Serializer serializer;
        std::vector <char> msg = serializer.serialize();
        serializer.deserializer(msg);

        uint32_t size = htonl(msg.size());
        peer.socket_send((char*)&size, sizeof(uint32_t));
        peer.socket_send(msg.data(), size);



        // struct players_t {
        //     int id;
        //     int x;
        //     int y;
        //     int d;
        //     int w;
        //     int life;
        // };

        // struct players_t {
        //     int id;
        //     int x;
        //     int y;
        //     int d;
        //     int w;
        //     int life;
        // };

        //rocket
        //door
        //items del piso id - pos



        // players_t player;
        // player.id = 01;

        // uint32_t size = htonl(sizeof(players_t));
        // peer.socket_send((char*)&size, sizeof(uint32_t));
        // peer.socket_send((char*)&player, sizeof(player));



        // while (state){
        //     std::string petition;
        //     size_t read = 0;
        //     while ((read = peer.socket_receive(cmd.data(), CHUNK_SZ)) > 0){
        //         std::string aux(cmd.begin(), cmd.begin()+read);
        //         petition += aux;
        //         std::cout << aux << std::endl; 
        //         std::cout << "Leido" << std::endl; 
        //     }
        //     //creo un hilo para receive y otro para send
        //     //envio snapshot completa al cliente.
        //     //peer.socket_send(output.c_str(), output.length());
        // }

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
