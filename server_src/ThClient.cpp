#include "ThClient.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <fstream>
#include <streambuf>
#include <iterator>
#include "ThClientSender.h"
#include "../common_src/Action.h"
#include "../common_src/Serializer.h"
#include "IdMaker.h"
#include <chrono>
#include "GamePlay.h"
#include "GameHandler.h"

#define FPS 30
#define NEW_GAME 'n'
#define REFRESH 'r'
#define JOIN_GAME 'j'
#define START 's'

void Client::start_game(){
    char start_game = 's';
    peer.socket_send(&start_game, sizeof(char));
}

void Client::notify_players(std::vector<std::string>> &usernames){

    /*cantidad de usernames*/
    uint32_t value = htonl(usernames.size());
    peer.socket_send((char*)&value, sizeof(uint32_t));

    for(std::string &user : usernames){
        /*tamanio de usernames*/
        value = htonl(user.length());
        peer.socket_send((char*)&value, sizeof(uint32_t));
        peer.socket_send((char*)user.c_str(), user.length());
    }
}

void ThClient::run(){
    
    try {

        /***********Recibo Username*******************/
        uint32_t size = 0;
        peer.socket_receive((char*)&size, sizeof(uint32_t));
        size = ntohl(size);
        std::vector<char> username(size);
        peer.socket_receive(username.data(), size);
        std::string aux(username.data());
        std::cout << "Username: "<<  aux << std::endl;
        /*********************************************/

        bool start = false;
        while(!start){
            /***********Recibo Decision de Partida********/
            //new -join - refresh
            char decision = '0';
            peer.socket_receive((char*)&decision, sizeof(char));
            /*********************************************/

            switch (decision){
            case NEW_GAME:
                {
                /***************** NEW GAME *******************/
                uint32_t size = 0;
                peer.socket_receive((char*)&size, sizeof(uint32_t));
                size = ntohl(size);
                std::vector<char> map(size);
                peer.socket_receive(map.data(), size);
                std::string map_data(map.data());
                GamePlay & game = this->game_handler.new_match(*this, map_data);
                char start = '0';
                    if(0 < peer.socket_receive((char*)&start, sizeof(char))){
                        std::cout <<"Llego mensaje de comienzo" << std::endl;
                        if(start == START){
                            game.start();
                        }else{
                            std::cout <<"Pero estaba mal" << std::endl;
                        }
                    }
                
                /*********************************************/
                }
                start = true;
                break;
            case JOIN_GAME:
                {
                /***************** JOIN GAME -IMPLEMENTAR-*******************/
                std::vector<int> matches_id = this->game_handler.get_matches_id();
                //Mando la cantidad de ids
                uint32_t value = htonl(matches_id.size());
                peer.socket_send((char*)&value, sizeof(uint32_t));
                for(int &id : matches_id){
                    value = htonl(id);
                    peer.socket_send((char*)&value, sizeof(int));

                }
                uint32_t game_id = 0;
                peer.socket_receive((char*)&game_id, sizeof(uint32_t));
                game_id = ntohl(game_id);
                GamePlay & game = this->game_handler.select_match(*this, (int)game_id);
                char start = '0';
                    if(0 < peer.socket_receive((char*)&start, sizeof(char))){
                        std::cout <<"Llego mensaje de comienzo" << std::endl;
                        if(start == START){
                            game.start();
                        }else{
                            std::cout <<"Pero estaba mal" << std::endl;
                        }
                    }
                
                /*********************************************/
                }
                start = true;
                break;
            case REFRESH:
                {
                //Cliente nueva partida -> lobby
                //Cliente join -> recien ahi mando los id
                //Cliente join-> Lobby
                //server envia lista de jugadores(username)
                //Cliente manda nueva partida/join/refresh - join a un lobby
                //ID maker
                //isOpen para las puertas y enviar al cliente.

                std::vector<int> matches_id = this->game_handler.get_matches_id();
                //Mando la cantidad de ids
                uint32_t value = htonl(matches_id.size());
                peer.socket_send((char*)&value, sizeof(uint32_t));
                for(int &id : matches_id){
                    value = htonl(id);
                    peer.socket_send((char*)&value, sizeof(int));
                }
                }
                break;
            }   
        }
        /***********Creo ID, Username y mando ID******/
            IdMaker id_maker;
            int new_player_id = id_maker.generate_id();
            char player_id_flag = 'i';
            peer.socket_send(&player_id_flag, sizeof(char));
            uint32_t player_id = htonl(new_player_id);
            peer.socket_send((char*)&player_id, sizeof(uint32_t));
        /*********************************************/



        this->sender = new ThClientSender(this->peer);
        this->sender->start();


        while (this->state){
            uint32_t size = 0;
            peer.socket_receive((char*)&size, sizeof(uint32_t));
            size = ntohl(size);
            std::vector<char> intention(size);
            peer.socket_receive(intention.data(), size);
            for(char value : intention){
                this->intention_queue.push_back(value);
            }            
        }
    }catch(const std::exception& e){
        perror(e.what());
    }catch(...){}
}

ThClient::ThClient(Socket&& socket, GameHandler & game_handler):game_handler(game_handler){
    this->peer = std::move(socket);
    this-> client_id = 0;//obtener del singleton
}

ThClient::~ThClient(){
    peer.socket_shutdown(SHUT_RDWR);
    delete this->sender;//revisar seg fault
}

void ThClient::send_snapshot(Snapshot snapshot){
    this->sender->send_snapshot(snapshot);
    //NOTIFY ALL, podria hacerlo en gameplay?
}