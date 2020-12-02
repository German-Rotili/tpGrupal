#include "server_helper.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <utility>
#include "server_helper.h"
#include "../common_src/common_socket.h"
#include "server_ThServer.h"
#define CMD_END "q"

Server::Server(){}

Server::~Server(){}

void Server::run(std::string & port, std::string & root){
    ThServer server_th(port, root);
    server_th.start();
    std::string command = "";
    while (true){
        std::cin >> command;
        if (command.compare(CMD_END) == 0){
            break;
        }
    }
    server_th.stop();
    server_th.join();
}
