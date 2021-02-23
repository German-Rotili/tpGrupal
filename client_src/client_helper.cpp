#include "client_helper.h"
#define SNAPSHOT_ID '0'
#define ACTION_ID '1'
#define ENDGAME_ID 'f'
#define START 's'
#define NEW_GAME 'n'
#define JOIN_MATCH 'j'
#define REFRESH 'r'

Client::Client(std::string & service,std::string & hostname):active(true){
    Socket client;
    client.socket_connect(service.c_str(), hostname.c_str());
    this->protocol = Protocol(std::move(client));
}

Client::~Client(){
    this->active = false;
}

bool Client::is_active(){
    return this->active;
}

void Client::receive_update(Snapshot & snapshot, ProtectedQueueAction & actions){
    /*Recibo ID Tipo msg*/
    char input_id = this->protocol.receive_char();
    /*Recibimos vector de chars-msg */
    switch (input_id){
        case SNAPSHOT_ID:{
            std::vector<char> msg = this->protocol.receive_standar_msg();
            this->serializer.deserializer(msg, snapshot);}
            break;
        case ACTION_ID:{
            std::vector<char> msg = this->protocol.receive_standar_msg();
            this->serializer.deserialize_action(msg, actions);}
            break;
        case ENDGAME_ID:
            std::cout << "GAME ENDED" << std::endl;
            this->active = false;
            break;
        default:
            std::cout << "Error id detection" <<std::endl;
    }
}
std::vector<int> Client::refresh_game(){
    char aux = REFRESH;
    this->protocol.send_char(aux);
    return this->get_matches_id();
}


int Client::recieve_players_size(){
    return this->protocol.receive_int();
}

std::string Client::receive_username(){
    int aux = this->protocol.receive_int();
    std::vector<char> aux_msg = this->protocol.receive_standar_msg();
    std::string username(aux_msg.data());//ojo '\0'
}

int Client::receive_score(){
    return this->protocol.receive_int();
}

int Client::receive_kills(){
    return this->protocol.receive_int();
}

int Client::receive_shots(){
    return this->protocol.receive_int();
}



std::vector<int> Client::get_matches_id(){
    return this->protocol.receive_vector_int();
}

void Client::send_refresh_flag(){
    char aux = REFRESH;
    this->protocol.send_char(aux);
}

std::vector<std::string> Client::get_players_username(){
    return this->protocol.receive_usernames();
}

char Client::receive_flag(){
    return this->protocol.receive_char();
}


int Client::await_game_start(){
    int client_id =  this->protocol.receive_int();//ID CLIENT/PLAYER
    // char aux = START;
    // this->protocol.send_char(aux);
    return client_id;
}



void Client::new_game(std::vector<char> & map){
    char new_game = NEW_GAME;
    this->protocol.send_char(new_game);
    this->protocol.send_standard_msg(map);
}

void Client::client_send_intention(std::vector<char> intention){
    this->protocol.send_standard_msg(intention);
}

void Client::start_match(){
    char start = START;
    this->protocol.send_char(start);
}

void Client::send_username(std::string & username){
    this->protocol.send_string_msg(username);
}



void Client::join_game(){
    char join_flag = JOIN_MATCH;
    this->protocol.send_char(join_flag);
}


std::vector<std::vector<int>> Client::join_game(std::string & game_id){
    this->join_game();
    int aux = std::stoi(game_id);
    this->protocol.send_integer(aux);
    std::string map = this->client_receive_string();
    MapHandler maphandler;
    return maphandler.readMapFromString(map);
}

std::vector<char> Client::client_receive_vector(){
    return this->protocol.receive_standar_msg();
}

std::string Client::client_receive_string(){
    std::vector<char> aux = this->protocol.receive_standar_msg();
    std::string val(aux.data());
    return val;
}
