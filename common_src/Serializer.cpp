#include "Serializer.h"
#include "../server_src/Player.h"
#include <sstream>

/*

    Player: 0
        int id
        float pos_x
        float pos_y
        float Direction;
        bool inventory[true true false]
        int munition
        char current_weapon
        char hp;

    Rocket: 1
        float pos_x
        float pos_y

    Item: 2
        int id
        int pos_x
        int pos_y

    Doors: 3
        int pos_x
        int pos_y
        bool status
*/

std::vector<char> Serializer::serialize() {
  // iterar sobre los jugadores
  std::vector<char> message;
  // this->serialize_players(message);
  int int1 = 18;
  float float1 = 5.8;
  char char1 = 5;
  this->append_variable(message, (char *)&int1, sizeof(int));
  this->append_variable(message, (char *)&float1, sizeof(float));
  message.push_back(char1);
}

void Serializer::deserialize(std::vector<char> &input) {
  std::stringstream input_buff(std::string(input.begin(), input.end()));
  int int1;
  float float1;
  char char1;
  int1 = extract_int(input_buff);
  float1 = extract_float(input_buff);
  char1 = input_buff.get();
  std::cout << int1;
}

int Serializer::extract_int(std::stringstream &buff) {
  int final_int;
  buff.get((char *)&final_int, sizeof(int));
  return final_int;
}

float Serializer::extract_float(std::stringstream &buff) {
  float final_float;
  buff.get((char *)&final_float, sizeof(float));
  return final_float;
}

/*
    [id][struct de la clase]

*/

void Serializer::serialize_players(std::vector<char> &message) {

  for (Player &player : this->map.get_players()) {
    int player_id = player.get_id();
    float pos_x = player.get_pos_x();
    float pos_y = player.get_pos_y();
    float direction = player.get_direction();
    int ammo = player.get_ammo();
    // bool inventory[] = ; implementar para que inventory devuelva este array.
    append_variable(message, (char *)&player_id, sizeof(int));
    append_variable(message, (char *)&pos_x, sizeof(float));
    append_variable(message, (char *)&pos_y, sizeof(float));
    append_variable(message, (char *)&direction, sizeof(float));
    // bool inventory[true true false]
    append_variable(message, (char *)&ammo, sizeof(int));
    message.push_back(player.get_current_weapon_id());
    char hp;
  }
}

void Serializer::append_variable(std::vector<char> &message, char *variable,
                                 size_t size) {
  for (int i = 0; i < size; i++) {
    message.push_back(variable[i]);
  }
}

void Serializer::append_float(std::vector<char> &message, float number) {
  char *number_ptr = (char *)&number;
  for (int i = 0; i < sizeof(float); i++) {
    message.push_back(number_ptr[i]);
  }
}
