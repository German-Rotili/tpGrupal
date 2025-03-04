#include "helper.h"
#include <iostream>
#include <string>
#include "Constants.h"

int main(int argc, char const *argv[]){

    if (argc > 3) {
        return 1;
    }
    try {
        Server serv;
        std::string port = argv[PORT];
        std::string line = "";
        serv.run(port);
    }
    catch(const std::exception& e){
        perror(e.what());
        return 1;
    } catch(...){
        return 1;
    }
    return 0;

}
