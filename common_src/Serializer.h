#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include "Snapshot.h"
#include "Action.h"
#include <arpa/inet.h>
#include <inttypes.h>
#include <byteswap.h>
#include "structDefinitions.h"

class Snapshot;

class Serializer{
private:
    void append_variable(std::vector<char> &message, char *variable, size_t size);

public:
    Serializer();
    ~Serializer();

    std::vector<char> serialize_snapshot(Snapshot & snapshot);
    void append_player_info(std::vector<char> & message, std::vector<player_t*> & players);
    void append_object_info(std::vector<char> & message, std::vector<object_t*> & objects);
    void append_actions(std::vector<char> & message, std::vector<Action*> & actions);
    std::vector<char> serialize_action(Snapshot & snapshot);
    void deserializer(std::vector <char> & msg, Snapshot & snapshot); 
    void deserialize_action(std::vector <char> & msg, Snapshot & snapshot);
    void deserialize_players(std::vector <char> & msg, Snapshot & snapshot, int & offset);
    void deserialize_objects(std::vector <char> & msg,  Snapshot & snapshot, int & offset);


};
#endif
