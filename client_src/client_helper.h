#ifndef CLIENTT
#define CLIENTT
#include "../common_src/common_socket.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#define MAX_BUFFER_SIZE 256

class Client {
private:
    Socket client;
public:
    Client(std::string & service,std::string & hostname);
    void client_send(std::string line);
    void client_receive();
    std::string client_receive_string();

    ~Client();
    /*
    Crea una conexion al socket y envia cada linea del stdin al server.
    Luego imprime la respuesta.
    */
    void run();
};
#endif
