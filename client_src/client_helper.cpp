#include "client_helper.h"
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include "yaml-cpp/yaml.h"
#include "../editor_src/ConfigManager/MapHandler.h"


Client::Client(std::string & service,std::string & hostname){
    this->client.socket_connect(service.c_str(), hostname.c_str());
}

Client::~Client(){}

void Client::client_send(std::string line){
//    client.socket_send(line);
    client.socket_send(line.c_str(), 4);
}


std::string Client::client_receive_string(){
    uint32_t size = 0;
    client.socket_receive((char*)&size, sizeof(uint32_t));
    size = ntohl(size);
    std::vector<char> buff(size);
    client.socket_receive(buff.data(), size);
    std::string msg(buff.data(), size);   
    return msg;
}



void Client::client_receive(){
    uint32_t size = 0;
    client.socket_receive((char*)&size, sizeof(uint32_t));
    size = ntohl(size);
    std::vector<char> buff(size);
    client.socket_receive(buff.data(), size);
    std::string msg(buff.data(), size);
    struct movies_t {
        int year;
    } movies;


    movies_t *movie = (movies_t*)(msg.c_str());

    std::cout << (*movie).year << std::endl;

    //MapHandler maphandler;
    //std::vector<std::vector<int>> map = maphandler.readMapFromString(s);

    // for (auto & element : map) {
    //     for (auto & value : element) {
    //         std::cout << value << std::endl;
    //     }
    // }
    
}

void Client::run(){
    //client_send();
    //client_receive();
}
