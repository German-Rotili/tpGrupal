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
    char start_game = START;
    peer.socket_send(&start_game, sizeof(char));
}

void ThClient::notify_players(std::vector<std::string> &usernames){
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



void ThClient::receive_username(){
    try{
    /***********Recibo Username*******************/
        uint32_t size = 0;
        peer.socket_receive((char*)&size, sizeof(uint32_t));
        size = ntohl(size);
        std::vector<char> username(size);
        peer.socket_receive(username.data(), size);
        std::string aux(username.data());
        this->username = aux;
    /*********************************************/
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Username Error." << '\n';
    }
}

void ThClient::new_game(){
    std::cout << "por mandar un new game"<< std::endl;

    try{
    /***************** NEW GAME *******************/
        uint32_t size = 0;
        peer.socket_receive((char*)&size, sizeof(uint32_t));
        size = ntohl(size);
        std::vector<char> map(size);
        peer.socket_receive(map.data(), size);
        std::cout << map.size() << " = " << size << std::endl;
        GamePlay & game = this->game_handler.new_match(*this, map);
        char start = '0';

        uint32_t value = htonl(1);
        peer.socket_send((char*)&value, sizeof(uint32_t));
        value = htonl(this->username.length());
        peer.socket_send((char*)&value, sizeof(uint32_t));
        peer.socket_send((char*)this->username.c_str(), this->username.length());

        peer.socket_receive((char*)&start, sizeof(char));
        if(start == START){
                game.start();
                game.start_game(this->client_id);
        }
        this->state = true;

    /*********************************************/
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "New Game Error" << '\n';
    }
}

void ThClient::join_game(){
    try{
    /***************** JOIN GAME*******************/
        std::vector<int> matches_id = this->game_handler.get_matches_id();
        uint32_t value = htonl(matches_id.size());
        //le indico la cantidad de matches id que va a tener que leer.
        peer.socket_send((char*)&value, sizeof(uint32_t));
        for(int i = 0; i < matches_id.size() ; i++){
            value = htonl( matches_id[i]);
            peer.socket_send((char*)&value, sizeof(int));
        }


        uint32_t game_id = 0;
        //recibo el id que eligio
        peer.socket_receive((char*)&game_id, sizeof(uint32_t));
        game_id = ntohl(game_id);

        GamePlay & game = this->game_handler.select_match(*this, (int)game_id);
        std::vector <char> map = game.get_raw_map();

        value = htonl(map.size());
        peer.socket_send((char*)&value, sizeof(uint32_t));
        peer.socket_send((char*)map.data(), map.size());
        char start = '0';
       
        //aca no podria recibir refresh solo lee si empieza la partida
        peer.socket_receive((char*)&start, sizeof(char));
        if(start == START){
            game.start_game(this->client_id);
        }

    /*********************************************/
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Join Game Error" << '\n';
    }
}

void ThClient::refresh_matches(){
    try{
        std::vector<int> matches_id = this->game_handler.get_matches_id();
        uint32_t value = htonl(matches_id.size());
        peer.socket_send((char*)&value, sizeof(uint32_t));
        for(int &id : matches_id){
            value = htonl(id);
            peer.socket_send((char*)&value, sizeof(int));
        }
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Refresh Error" << '\n';
    }
}

void ThClient::send_client_id(){
    try{
    /***********Creo y mando ID******/
        IdMaker id_maker;
        int new_player_id = id_maker.generate_id();
        uint32_t player_id = htonl(new_player_id);
        peer.socket_send((char*)&player_id, sizeof(uint32_t));
    /*********************************************/
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
            char decision = '0';
            peer.socket_receive((char*)&decision, sizeof(char));
            /*********************************************/
        std::cout <<"recibe algo" <<std::endl;

            switch (decision){
                case NEW_GAME:{
                    this->new_game();
                    std::cerr << "salio de new game" << '\n';
                    this->state = true;
                }
                    start = true;
                    break;
                case JOIN_GAME:{
                    this->join_game();
                }
                    start = true;
                    break;
                case REFRESH:{
                    this->refresh_matches();
                }
            }   
        }
        
        // this->sender = new ThClientSender(this->peer);
        // this->sender->start();
        this->receiver_loop();
        
}

void ThClient::receiver_loop(){
    try{
        while (this->state){
            std::cout << "entro al reciever loop" << '\n';
            uint32_t size = 0;
            peer.socket_receive((char*)&size, sizeof(uint32_t));
            std::cout << "despues del receive" << '\n';

            size = ntohl(size);
            std::vector<char> intention(size);
            peer.socket_receive(intention.data(), size);
            std::cout << "despues del segundo receive" << '\n';

            for(char value : intention){
                std::cout << "antes del push back" << '\n';
                this->intention_queue.push_back(value);
                std::cout << "despues del push back" << '\n';

            }            
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Receiver Loop Error" << '\n';
    }
}

ThClient::ThClient(Socket&& socket, GameHandler & game_handler):game_handler(game_handler){
    this->peer = std::move(socket);
}

ThClient::~ThClient(){
    peer.socket_shutdown(SHUT_RDWR);
    delete this->sender;//revisar seg fault
}

void ThClient::send_snapshot(Snapshot snapshot){
    this->sender->send_snapshot(snapshot);
}