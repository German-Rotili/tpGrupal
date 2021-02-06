#ifndef CLIENTT
#define CLIENTT
#include "../common_src/common_socket.h"
#include "yaml-cpp/yaml.h"
#include "../editor_src/ConfigManager/MapHandler.h"
#include "../common_src/Serializer.h"
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

    void  client_send_intention(intention_t & intention);

    void update_player(player_t & player, std::vector <Action*> & actions);

    ~Client();
    /*
    Crea una conexion al socket y envia cada linea del stdin al server.
    Luego imprime la respuesta.
    */
    void run();
};
#endif
