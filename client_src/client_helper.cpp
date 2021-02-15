#include "client_helper.h"
#define SNAPSHOT_ID '0'
#define ACTION_ID '1'
#define START 's'
#define NEW_GAME 'n'
#define JOIN_MATCH 'j'
Client::Client(std::string & service,std::string & hostname){
    Socket client;
    client.socket_connect(service.c_str(), hostname.c_str());
    this->protocol = Protocol(std::move(client));
}

Client::~Client(){}

void Client::receive_update(Snapshot & snapshot, ProtectedQueueAction & actions){
    /*Recibo ID Tipo msg*/
    char input_id = this->protocol.receive_char();
    /*Recibimos vector de chars-msg */
    std::vector<char> msg = this->protocol.receive_standar_msg();
    
    switch (input_id){
        case SNAPSHOT_ID:
            this->serializer.deserializer(msg, snapshot);
            break;
        case ACTION_ID:
            this->serializer.deserialize_action(msg, actions);
            break;
        default:
            std::cout << "Error id detection" <<std::endl;
    }    
}

// void Client::recieve_snapshot(Snapshot & snapshot){
//     /*Recibo ID Tipo msg*/
//     char input_id = this->protocol.receive_char();
//     /*Recibimos vector de chars-msg */
//     std::vector<char> msg = this->protocol.receive_standar_msg();
    
//     switch (input_id){
//         case SNAPSHOT_ID:
//             this->serializer.deserializer(msg, snapshot);
//             break;
//         case ACTION_ID:
//             this->serializer.deserialize_action(msg, snapshot);
//             break;
//         default:
//             std::cout << "Error id detection" <<std::endl;
//     } 
// }

std::vector<int> Client::get_matches_id(){
  std::cout << "recibo vector de ints." << std::endl;

    return this->protocol.receive_vector_int();
}

std::vector<std::string> Client::get_players_username(){
    return this->protocol.receive_usernames();
}


int Client::await_game_start(){
    std::cout << "Await start"<<std::endl;
    char aux_char =this->protocol.receive_char(); 
    while ( aux_char!= START){  }//START MATCH
    return this->protocol.receive_int();//ID CLIENT/PLAYER
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
    int aux = std::stoi(game_id);
    this->protocol.send_integer(aux);
    std::string map = this->client_receive_string();
    MapHandler maphandler;//CAMMBIAR A RECIBIR EL ARCHIVO YAML COMPLETO
    return maphandler.readMap("map1");//cambiar a envio completo del yaml.
}

std::vector<char> Client::client_receive_vector(){
    return this->protocol.receive_standar_msg();
}

std::string Client::client_receive_string(){
    std::vector<char> aux = this->protocol.receive_standar_msg();
    std::string val(aux.data());//REVISAR EL CARACTER DE FIN DE STRING!!!!!!!!
    return val;
}

