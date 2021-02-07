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
#include "Action.h"

struct intention_t{
  bool up;
  bool angle_right;
  bool angle_left;
  bool down;
  bool attack;
  bool interact;
  int weapon;
  bool active;
};

struct action_t {
    int player_id; 
    double impact_x;
    double impact_y;
    char weapon_id;
};

struct player_t {
    int player_id;
    float pos_x;
    float pos_y;
    float direction;
    int ammo;
    char current_weapon;
};


class Serializer{
private:

   // Map map;
    void serialize_players(std::vector<char> &message);
    void append_variable(std::vector<char> &message, char *variable, size_t size);
    void append_float(std::vector<char> &message, float number);
public:
    Serializer();
    ~Serializer();
    std::vector<char> serialize();
    //void deserialize(std::vector<char> &);
    int extract_int(std::stringstream &);
    float extract_float(std::stringstream &);
    void deserializer(std::vector <char> & msg);    
    void deserializer(std::vector <char> & msg, player_t & player_info);    
    void append_player_info(std::vector<char> & , player_t & );
    std::vector<char> serialize(player_t & player);
    std::vector<char> serialize(Action & player);
    std::vector<char> serialize(intention_t & snapshot);
    void append_snapshot(std::vector<char> & message, intention_t & snapshot);
    void append_action(std::vector<char> & message, Action & action);
    void deserializer(std::vector <char> & msg, intention_t & snapshot);
    void deserializer(std::vector <char> & msg, Action & action);

};
#endif
