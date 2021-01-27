#include "Serializer.h"


Serializer::Serializer(){}

Serializer::~Serializer(){}

void Serializer::append_variable(std::vector<char> &message, char *variable, size_t size){
    for(int i = 0; i < (int)size; i++){
        message.push_back(variable[i]);
        //printf("%02X", (unsigned)(unsigned char)variable[i]);
    }
        //printf(" ");
}

std::vector<char> Serializer::serialize() {
    std::vector<char> message;
    this->serialize_players(message);
    return message;
}

void Serializer::serialize_players(std::vector<char> &message){
    for(Player &player : this->map.get_players()){
        player_t player_info = player.get_info();
        append_player_info(message, player_info);
    }
}

void Serializer::append_player_info(std::vector<char> & message, player_t & player_info){
    append_variable(message, (char*) &(player_info.player_id), sizeof(int));
    append_variable(message, (char*) &(player_info.pos_x), sizeof(float));
    append_variable(message, (char*) &(player_info.pos_y), sizeof(float));
    append_variable(message, (char*) &(player_info.direction), sizeof(float));
    append_variable(message, (char*) &(player_info.ammo), sizeof(int));
    append_variable(message, (char*) &(player_info.current_weapon), sizeof(char));
}

void Serializer::deserializer(std::vector <char> & msg){
    //Posibilidad de que haya un deserializer para cada "tipo" de objeto
    player_t player_info;
    int offset = 0;
    int size_int = sizeof(int);
    int size_float = sizeof(float);
    memcpy(&player_info.player_id, msg.data(), size_int);
    offset += size_int;
    memcpy(&player_info.pos_x, msg.data() + offset, size_float);
    offset += size_float;
    memcpy(&player_info.pos_y, msg.data() + offset, size_float);
    offset += size_float;
    memcpy(&player_info.direction, msg.data() + offset, size_float);
    offset += size_float;
    memcpy(&player_info.ammo, msg.data() + offset,size_int);
    offset += size_int;
    memcpy(&player_info.current_weapon, msg.data() + offset, sizeof(char));
    offset += sizeof(char);

    std::cout << player_info.player_id <<std::endl;
    std::cout << player_info.pos_x <<std::endl;
    std::cout << player_info.pos_y <<std::endl;
    std::cout << player_info.direction <<std::endl;
    std::cout << player_info.ammo <<std::endl;
    std::cout << player_info.current_weapon <<std::endl;
}






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


// void Serializer::deserialize(std::vector<char> &input) {
   
//     for(auto i : input){
//         printf("%02X ", (unsigned)(unsigned char)i);

//     }
//   std::cout << std::endl;
//   std::stringstream input_buff(std::string(input.begin(), input.end()));
//   int int1 = extract_int(input_buff);
//   float float1 = extract_float(input_buff);
//   char char1 = input_buff.get();
//   std::cout << int1 << std::endl;
//   std::cout << float1 << std::endl;
//   std::cout << char1 << std::endl;
// }

// int Serializer::extract_int(std::stringstream &buff) {
//   int final_int;
//   buff.get((char *)&final_int, sizeof(int));
//   return final_int;
// }


// float Serializer::extract_float(std::stringstream &buff) {
//   float final_float;
//   buff.get((char *)&final_float, sizeof(float));
//   return final_float;
// }

/*
    [id][struct de la clase]

*/




