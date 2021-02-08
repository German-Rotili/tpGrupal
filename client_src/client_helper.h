#ifndef CLIENTT
#define CLIENTT
#include "../common_src/common_socket.h"
#include "yaml-cpp/yaml.h"
#include "../common_src/MapHandler.h"
#include "../common_src/Serializer.h"
#include "../common_src/Snapshot.h"
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
    std::string client_receive_string();
    std::vector<char>  client_receive_vector();

    void  client_send_intention(std::vector<char> & intention);
    void recieve_snapshot(Snapshot & snapshot);
    ~Client();
    /*
    Crea una conexion al socket y envia cada linea del stdin al server.
    Luego imprime la respuesta.
    */
    void run();
};
#endif
