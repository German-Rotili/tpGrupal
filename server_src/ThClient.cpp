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
#include "../common_src/common_exception.h"
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
    this->protocol->send_char(start_flag);
    this->protocol->send_integer(this->client_id);
}

void ThClient::notify_players(std::vector<std::vector<char>> &usernames){
    char refresh_flag = REFRESH;
    this->protocol->send_char(refresh_flag);
    this->protocol->send_usernames(usernames);

}

void ThClient::receive_username(){
    try{
    /***********Recibo Username*******************/
        this->username = this->protocol->receive_standar_msg();
    /*********************************************/
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Username Error." << '\n';
    }
}

void ThClient::stop(){
    this->state = false;
    this->protocol->close();
}


void ThClient::new_game(){
    

        std::vector<char> map = this->protocol->receive_standar_msg();//recibo el mapa
        GamePlay & game = this->game_handler.new_match(*this, map);//nueva partida con ese mapa
    try{
        this->protocol->send_username(this->username);
        while(true){
            char msg_char = this->protocol->receive_char();
            if(msg_char == START){
                    game.start_game();// le aviso a todos que comenzo la partida.
                    game.start();//Lanzo hilo de la partida
                    break;
            }else if (msg_char == REFRESH){
                this->refresh_players(game.get_usernames());

            }else{
                std::cout  << "Llego cualquier cosa." <<  msg_char << std::endl;
            }
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "New Game Error" << '\n';
        game.stop();
    }catch(...){
        game.stop();
    }
}
int &ThClient::get_id(){
    return this->client_id;
}


void ThClient::join_game(){
    try{
        std::vector<int> matches_id = this->game_handler.get_matches_id();
        this->protocol->send_vector_int(matches_id);//mando ids de partidas
        char response = 'x';
        while((response = this->protocol->receive_char()) == REFRESH){
            matches_id = this->game_handler.get_matches_id();
            this->protocol->send_vector_int(matches_id);
        }
        int game_id = this->protocol->receive_int();//recibo id elegido y me uno
        GamePlay & game = this->game_handler.select_match(*this, game_id);
        std::vector <char> map = game.get_raw_map();//cambiar al archivo yaml entero.
        this->protocol->send_vector_char(map);//mando mapa al cliente para que dibuje
        this->refresh_players(game.get_usernames());//mando usernames     

    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Join Game Error" << '\n';
    }
}


void ThClient::refresh_players(std::vector<std::vector<char>> & usernames){
    try{
        this->protocol->send_usernames(usernames);

    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Refresh Error" << '\n';
    }
}

void ThClient::refresh_matches(){
    try{
        std::vector <int> aux = this->game_handler.get_matches_id();
        this->protocol->send_vector_int(aux);

    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Refresh Error" << '\n';
    }
}


void ThClient::run(){
    try{
        this->receive_username();
        
        bool start = false;
        while(!start){
    
            /***********Recibo Decision sobre Partida********/
            char decision = this->protocol->receive_char();
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
                    start = true;
                    break;
                case START:{
                    break;
                    start = true;
                }
            }   
        }
    }catch(ConnectionClosedException& e){
        std::cerr << "Client Closed" << '\n';
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Menu Error" << '\n';
    }
    
        this->receiver_loop();
}

void ThClient::receiver_loop(){
    try{
        this->state =true;
        while (this->state){
            std::vector<char> intention = this->protocol->receive_standar_msg();
            if(intention.size() > 0){
                Intention intention_aux(this->client_id, intention); 
                this->intentions->add_element(intention_aux);//std::move a la intencion
            }

        }
    }catch(ConnectionClosedException& e){
        std::cerr << "Client Closed" << '\n';
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Receiver Loop Error" << '\n';
    }
}

ThClient::ThClient(Protocol *protocol, GameHandler & game_handler):game_handler(game_handler), protocol(protocol){
    // this->protocol = std::move(protocol);
}

ThClient::~ThClient(){
    this->dead = true;
    delete this->protocol;
}
