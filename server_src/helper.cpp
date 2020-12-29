#include "helper.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <utility>
#include "helper.h"
#include "../common_src/common_socket.h"
#include "ThServer.h"
#define CMD_END "q"

Server::Server(){}

Server::~Server(){}

void Server::run(std::string & port, std::string & root){
    ThServer th(port, root);
    th.start();
    std::string command = "";
    while (true){
        std::cin >> command;
        if (command.compare(CMD_END) == 0){
            break;
        }
    }
    th.stop();
    th.join();
}
