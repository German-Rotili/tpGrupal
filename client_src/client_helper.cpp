#include "client_helper.h"
#define SNAPSHOT_ID '0'
#define ACTION_ID '1'

Client::Client(std::string & service,std::string & hostname){
    this->client.socket_connect(service.c_str(), hostname.c_str());
}

Client::~Client(){}

void Client::client_send(std::string line){
//    client.socket_send(line);
    client.socket_send(line.c_str(), 4);
}


void Client::recieve_snapshot(Snapshot & snapshot){
    
    /*Recibo ID*/
    char input_id;
    std::vector<char> buff(1);
    client.socket_receive(buff.data(), sizeof(char));
    memcpy(&input_id, buff.data(), sizeof(char));
    /**********/


    /*Recibimos vector de chars*/
    std::vector<char> msg = this->client_receive_vector(); //aca adentro primero recibe largo y despues lee todo.
    /**********/
    

    /********/
    Serializer serializer;
    /**********/

    switch (input_id){

        case SNAPSHOT_ID:
            serializer.deserializer(msg, snapshot);
            break;
        
        case ACTION_ID:
            serializer.deserialize_action(msg, snapshot);
            break;

        default:
            std::cout << "Error id detection" <<std::endl;
    } 
}

std::vector<std::string> Client::get_matches_id(){
    std::vector<std::string> matches_id;

    /*Cantidad de ids*/
    uint32_t size = 0;
    client.socket_receive((char*)&size, sizeof(uint32_t));
    size = ntohl(size);

    for(int i = 0; i < (int)size ; i++){
        /*Largo de cada id*/
        uint32_t size_id = 0;
        client.socket_receive((char*)&size_id , sizeof(uint32_t));
        size_id = ntohl(size_id);

        /*id*/
        std::vector<char> buff(size);
        client.socket_receive(buff.data(), size);
        std::string id(buff.data());
        matches_id.push_back(id);
    }

    return matches_id;
}

std::vector<std::string> Client::get_players_username(){

    std::vector<std::string> usernames;
    /*Cantidad de jugadores*/
    uint32_t size = 0;
    client.socket_receive((char*)&size, sizeof(uint32_t));
    size = ntohl(size);
    std::cout << " recibi cantidad de usernames: "<< size << std::endl;

    for(int i = 0; i < (int)size ; i++){
        /*Largo de cada jugador*/

        uint32_t size_player = 0;
        client.socket_receive((char*)&size_player , sizeof(uint32_t));

        /*Username*/
        std::vector<char> buff(size);
        client.socket_receive(buff.data(), size);
        std::string username(buff.data());
        std::cout << " recibi un username: "<< username << std::endl;

        usernames.push_back(username);
    }
        std::cout << " devuelvo lista de usernames de tamanio:  "<<usernames.size() << std::endl;

    return usernames;

}


int Client::await_game_start(){
    char start = 'x';
    while (start != 's'){
        client.socket_receive((char*)&start, sizeof(char));   
    }
    int client_id= -1;
    client.socket_receive((char*)&client_id, sizeof(int));   
    return (int)ntohl(client_id);
}



void Client::new_game(std::vector<char> & map){
    char new_game = 'n';
    client.socket_send((char*)&new_game, sizeof(char));
    uint32_t size_1 = htonl(map.size());
    client.socket_send((char*)&size_1, sizeof(uint32_t));
    client.socket_send(map.data(), map.size());
}

void Client::client_send_intention(std::vector<char> & intention){
        Serializer serializer;
        uint32_t snap_size = htonl(intention.size());
        client.socket_send((char*)&snap_size, sizeof(uint32_t));
        client.socket_send(intention.data(), intention.size());
}

void Client::start_match(){
    char join_flag = 's';
    client.socket_send((char*)&join_flag, sizeof(char));
}


void Client::send_username(std::string & username){
    uint32_t snap_size = htonl(username.length());
    client.socket_send((char*)&snap_size, sizeof(uint32_t));
    client.socket_send(username.c_str(), username.length());
}


void Client::join_game(){
    char join_flag = 'j';
    client.socket_send((char*)&join_flag, sizeof(char));
}


std::vector<std::vector<int>> Client::join_game(std::string & game_id){
    uint32_t g_id = htonl(std::stoi(game_id));
    client.socket_send((char*)&g_id, sizeof(uint32_t));
    std::string map = this->client_receive_string();
    MapHandler maphandler;
    return maphandler.readMapFromString(map);
}

std::vector<char> Client::client_receive_vector(){

  
    uint32_t size = 0;
    client.socket_receive((char*)&size, sizeof(uint32_t));
    size = ntohl(size);
    std::vector<char> buff(size);
    client.socket_receive(buff.data(), size);

   
    // std::cout << "vector size after filled: " << buff.size() <<std::endl;
    // for(int i=0 ; i < buff.size(); i ++){
    //     printf("%02X ", (unsigned)(unsigned char)buff.data()[i]);
    // }
    // printf("\n");
    return buff;
}

std::string Client::client_receive_string(){
    uint32_t size = 0;
    client.socket_receive((char*)&size, sizeof(uint32_t));
    size = ntohl(size);
    // std::cout << "recibi el tamanio a leer: " << size <<std::endl;
    std::vector <char> msg(size);
    client.socket_receive(msg.data(), size);
    // std::cout << "recibi el vector "<<std::endl;

            // printf("****************MAP CLIENT*************\n");
            // for (int i = 0; i < msg.size(); i++) {
            //     printf("%02X ", (unsigned)(unsigned char)msg.data()[i]);
            // }
            // printf("*****************************\n");



    std::string val(msg.data());
    return val;
}

void Client::run(){

}
