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
#include "../common_src/Intention.h"
#include "IdMaker.h"
#include <chrono>
#include "GamePlay.h"
#include "GameHandler.h"

void ThClient::attach_queue(ProtectedQueueIntention *intentions){
    this->intentions = intentions; 
}


void ThClient::start_game(){
    char start_flag = START;
    this->protocol.send_char(start_flag);
    this->protocol.send_integer(this->client_id);
}

void ThClient::notify_players(std::vector<std::vector<char>> &usernames){
    this->protocol.send_usernames(usernames);
}

void ThClient::receive_username(){
    try{
    /***********Recibo Username*******************/
        this->username = this->protocol.receive_standar_msg();
        std::string aux(this->username.data());
    /*********************************************/
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Username Error." << '\n';
    }
}

void ThClient::new_game(){
    try{

        std::vector<char> map = this->protocol.receive_standar_msg();//recibo el mapa
        GamePlay & game = this->game_handler.new_match(*this, map);//nueva partida con ese mapa
        this->protocol.send_username(this->username);
        while(true){
            char msg_char = this->protocol.receive_char();

            if(msg_char == START){

                    game.start();//Lanzo hilo de la partida
                    game.start_game();// le aviso a todos que comenzo la partida.
                    break;
            }else if (msg_char == REFRESH){
                std::cout  << "REFRESH" <<  msg_char << std::endl;
                this->refresh_players(game.get_usernames());
            }else{
                std::cout  << "Llego cualquier cosa." <<  msg_char << std::endl;
            }
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "New Game Error" << '\n';
    }
}

void ThClient::join_game(){
    try{
        std::vector<int> matches_id = this->game_handler.get_matches_id();
        this->protocol.send_vector_int(matches_id);//mando ids de partidas
        int game_id = this->protocol.receive_int();//recibo id elegido y me uno
        GamePlay & game = this->game_handler.select_match(*this, game_id);
        std::vector <char> map = game.get_raw_map();//cambiar al archivo yaml entero.
        this->protocol.send_vector_char(map);//mando mapa al cliente para que dibuje
        this->protocol.send_usernames(game.get_usernames());
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Join Game Error" << '\n';
    }
}


void ThClient::refresh_players(std::vector<std::vector<char>> & usernames){
    try{
        this->protocol.send_usernames(usernames);
        std::cout  << "Sendig player usernames" << std::endl;

    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Refresh Error" << '\n';
    }
}

void ThClient::refresh_matches(){
    try{
        std::vector <int> aux = this->game_handler.get_matches_id();
        this->protocol.send_vector_int(aux);
        std::cout  << "Sendig matches id" << std::endl;

    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Refresh Error" << '\n';
    }
}


void ThClient::run(){
        this->receive_username();
        
        bool start = false;
        while(!start){
        
            /***********Recibo Decision sobre Partida********/
            char decision = this->protocol.receive_char();
            /*********************************************/
            switch (decision){
                case NEW_GAME:{
                    this->new_game();
                }
                    start = true;
                    break;
                case JOIN_GAME:{
                    this->join_game();
                }
                    break;
                case REFRESH:{
                    this->refresh_matches();
                }
                case START:{
                    break;
                    start = true;
                }
            }   
        }
        this->receiver_loop();
        
}

void ThClient::receiver_loop(){
    try{
        while (this->state){
            std::vector<char> intention = this->protocol.receive_standar_msg();
            Intention intention_aux(this->client_id, intention); 
            this->intentions->add_element(intention_aux);//std::move a la intencion
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Receiver Loop Error" << '\n';
    }
}

ThClient::ThClient(Protocol&& protocol, GameHandler & game_handler):game_handler(game_handler){
    this->protocol = std::move(protocol);
}

ThClient::~ThClient(){}
