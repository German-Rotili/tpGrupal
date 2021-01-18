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
    client.socket_send(line);
}

void Client::client_receive(){

    std::string s;
    client.socket_receive(s);
    MapHandler maphandler;
    std::vector<std::vector<int>> map = maphandler.readMapFromString(s);

    for (auto & element : map) {
        for (auto & value : element) {
            std::cout << value << std::endl;
        }
    }
    
}

void Client::run(){
    //client_send();
    //client_receive();
}
