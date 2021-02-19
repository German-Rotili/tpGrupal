#ifndef CLIENTT
#define CLIENTT
#include "../common_src/common_socket.h"
#include "yaml-cpp/yaml.h"
#include "../common_src/MapHandler.h"
#include "../common_src/Serializer.h"
#include "../common_src/Snapshot.h"
#include "../common_src/Protocol.h"
#include "../common_src/ProtectedQueueAction.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#define MAX_BUFFER_SIZE 256

class Client {
private:
    Protocol protocol;
    Serializer serializer;
public:
    Client(std::string & service,std::string & hostname);
    std::string client_receive_string();
    std::vector<char>  client_receive_vector();
    std::vector<std::vector<int>> join_game(std::string & game_id);
    void start_match();
    char receive_flag();
    void new_game(std::vector<char> & map);
    int await_game_start();
    void receive_update(Snapshot & snapshot, ProtectedQueueAction & actions);
    void  client_send_intention(std::vector<char> intention);
    std::vector<std::string> get_players_username();
    void recieve_snapshot(Snapshot & snapshot);
    std::vector<int> refresh_game();
    std::vector<int> get_matches_id();
    void send_refresh_flag();
    ~Client();
    void send_username(std::string & username);
    void join_game();
};
#endif
