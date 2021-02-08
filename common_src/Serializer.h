#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <vector>
// #include "../server_src/Map.h"
#include <iostream>
#include <sstream>
#include <string>
#include "utils.h"
// #include "../server_src/Player.h"
#include <cstring>
#include "Snapshot.h"
#include "Action.h"

struct object_t{
    int id;
    double pos_x;
    double pos_y;
    bool state;
};


struct intention_t{
  char up;
  char angle_right;
  char angle_left;
  char down;
  char attack;
  char interact;
  char weapon;
};

class Snapshot;

struct player_t {
    int player_id;
    float pos_x;
    float pos_y;
    float direction;
    int ammo;
    char current_weapon;
    double health;
    int lives;
    int score;
};


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
