#include "Map.h"
#include "player.h"
#include "helper.h"
#include <iostream>
#include <string>
#define PORT 1
#define ROOT 2
#define QUIT "q"

int main(int argc, char const *argv[]){

    if (argc > 3) {
        return 1;
    }
    try {
        Server serv;
        std::string port = argv[PORT];
        std::string rootname = argv[ROOT];
        std::string line = "";
        serv.run(port, rootname);
    }
    catch(const std::exception& e){
        perror(e.what());
        return 1;
    } catch(...){
        return 1;
    }
    return 0;

}
