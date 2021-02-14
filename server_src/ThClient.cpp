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


void ThClient::start_game(){
    char start_flag = START;
    this->protocol.send_char(start_flag);
}

void ThClient::notify_players(std::vector<std::vector<char>> &usernames){
    this->protocol.send_usernames(usernames);
}

void ThClient::receive_username(){
    try{
    /***********Recibo Username*******************/
        this->username = this->protocol.receive_standar_msg();
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
        char start = '0';
        this->protocol.send_char(start);//Aviso que empezo la partida
        this->protocol.send_vector_char(this->username);//Envio mi username
        while(true){
            char msg_char = this->protocol.receive_char();
            if(msg_char == START){
                    game.start();//Lanzo hilo de la partida
                    game.start_game();// le aviso a todos que comenzo la partida.
                    break;
            }else if (msg_char == REFRESH){
                this->refresh_matches();
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
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Join Game Error" << '\n';
    }
}

void ThClient::refresh_matches(){
    try{
        std::vector <int> aux = this->game_handler.get_matches_id();
        this->protocol.send_vector_int(aux);
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Refresh Error" << '\n';
    }
}

void ThClient::send_client_id(){
    try{
        IdMaker id_maker;
        int new_player_id = id_maker.generate_id();
        this->protocol.send_integer(new_player_id);
    }catch(std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "ID Sending Error" << '\n';
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

std::vector<char> ThClient::get_intention(){
    std::unique_lock<std::mutex> lock(this->m);//implementar recontra cola protegida.
    std::vector<char> aux = this->intention_queue;
    this->intention_queue.clear();
    return aux;
}


void ThClient::receiver_loop(){
    try{
        while (this->state){
            std::vector<char> intention = this->protocol.receive_standar_msg();
           /*GUARDAR EN COLA PROTEGIDA REY*/
            for(char value : intention){
                std::unique_lock<std::mutex> lock(this->m);
                this->intention_queue.push_back(value);
            }    
           /*******************************/
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Receiver Loop Error" << '\n';
    }
}

ThClient::ThClient(Protocol&& protocol, GameHandler & game_handler):game_handler(game_handler){
    this->protocol = std::move(protocol);
}

ThClient::~ThClient(){
    delete this->sender;//revisar seg fault
}

void ThClient::send_snapshot(Snapshot snapshot){//Cuando llamo este metodo desde otro hilo
    this->sender->send_snapshot(snapshot);      //se esta ejecutando el reciever_loop en este hilo.
}