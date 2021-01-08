#include "client_helper.h"
#include <vector>
#include <string>

Client::Client(std::string & service,std::string & hostname){
    this->client.socket_connect(service.c_str(), hostname.c_str());
}

Client::~Client(){}

void Client::client_send(std::string line){
    client.socket_send(line.c_str(), line.length());
}

void Client::client_receive(){
    std::vector<char> buff(MAX_BUFFER_SIZE, 0);
    size_t read = 0;
    while ((read = client.socket_receive(buff.data(), MAX_BUFFER_SIZE)) > 0){
        std::string result(buff.begin(), buff.begin()+read);
        std::cout << result;
    }
}

void Client::run(){
    //client_send();
    //client_receive();
}
