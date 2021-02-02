#include "client_helper.h"


Client::Client(std::string & service,std::string & hostname){
    this->client.socket_connect(service.c_str(), hostname.c_str());
}

Client::~Client(){}

void Client::client_send(std::string line){
//    client.socket_send(line);
    client.socket_send(line.c_str(), 4);
}


void Client::update_player(player_t & player){
      std::vector<char> msg = this->client_receive_vector();
      Serializer serializer;
      serializer.deserializer(msg, player);
}



void Client::client_send_intention(intention_t & intention){
        Serializer serializer;
        std::vector <char> msg = serializer.serialize(intention);
        uint32_t snap_size = htonl(msg.size());
        client.socket_send((char*)&snap_size, sizeof(uint32_t));
        client.socket_send(msg.data(), msg.size());
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
    std::string val(msg.data());
    return val;
}

void Client::run(){
    //client_send();
    //client_receive();
}
