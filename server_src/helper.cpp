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
#include "Constants.h"

Server::Server(){}

Server::~Server(){}

void Server::run(std::string & port){
    ThServer th(port);
    th.start();
    std::string command = "";
    while (true){
        std::cin >> command;
        if (command.compare(QUIT) == 0){
            break;
        }
    }
    th.stop();
    th.join();
}
