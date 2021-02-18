#include "Serializer.h"

#include "ProtectedQueueAction.h"

Serializer::Serializer(){}

Serializer::~Serializer(){}


/***SERIALIZADORES***/
void Serializer::append_variable(std::vector<char> &message, char *variable, size_t size){
    for(int i = 0; i < (int)size; i++){
        message.push_back(variable[i]);
    }
}
std::vector<char> Serializer::serialize_action(Snapshot & snapshot) {
    std::vector<char> message;
    append_actions(message, snapshot.actions);
    return message;
}
std::vector<char> Serializer::serialize_snapshot(Snapshot & snapshot){
    std::vector<char> message;

    append_player_info(message, snapshot.players);
    append_object_info(message, snapshot.objects);
    //append_actions(message, snapshot.actions);
    return message;
}
void Serializer::append_actions(std::vector<char> & message, std::vector<Action> & actions){
    uint32_t actions_amount = htonl(actions.size());
    append_variable(message, (char*) &(actions_amount), sizeof(uint32_t));

    for (auto &action : actions){
        append_variable(message, (char*) &(action.player_id), sizeof(int));
        append_variable(message, (char*) &(action.impact_x), sizeof(double));
        append_variable(message, (char*) &(action.impact_y), sizeof(double));
        append_variable(message, (char*) &(action.weapon_id), sizeof(char));
        append_variable(message, (char*) &(action.state), sizeof(bool));
    }
}
void Serializer::append_object_info(std::vector<char> & message, std::vector<object_t> & objects){
    char snap_id = 'o';
    append_variable(message, (char*) &(snap_id), sizeof(char));
    uint32_t objects_amount = htonl(objects.size());
    append_variable(message, (char*) &(objects_amount), sizeof(uint32_t));

    for (auto &object_info : objects){
        append_variable(message, (char*) &(object_info.id), sizeof(int));
        append_variable(message, (char*) &(object_info.pos_x), sizeof(double));
        append_variable(message, (char*) &(object_info.pos_y), sizeof(double));
        append_variable(message, (char*) &(object_info.state), sizeof(bool));
    }
}
void Serializer::append_player_info(std::vector<char> & message, std::vector<player_t> & players){
    char snap_id = 'p';
    append_variable(message, (char*) &(snap_id), sizeof(char));
    uint32_t players_amount = htonl(players.size());
    append_variable(message, (char*) &(players_amount), sizeof(uint32_t));

    for (auto &player_info : players){
        append_variable(message, (char*) &(player_info.player_id), sizeof(int));
        append_variable(message, (char*) &(player_info.pos_x), sizeof(float));
        append_variable(message, (char*) &(player_info.pos_y), sizeof(float));
        append_variable(message, (char*) &(player_info.direction), sizeof(float));
        append_variable(message, (char*) &(player_info.ammo), sizeof(int));
        append_variable(message, (char*) &(player_info.current_weapon), sizeof(char));
        append_variable(message, (char*) &(player_info.health), sizeof(double));
        append_variable(message, (char*) &(player_info.lives), sizeof(int));
        append_variable(message, (char*) &(player_info.score), sizeof(int));
    }
}



/***DESERIALIZADORES***/
void Serializer::deserialize_players(std::vector <char> & msg, Snapshot & snapshot, int & offset){

    char snap_id = 'p';
    int amount = 0;
    int size_int = sizeof(int);
    int size_float = sizeof(float);
    memcpy(&snap_id, msg.data(), sizeof(char));
    offset += sizeof(char);

    if (snap_id == 'p'){
        memcpy(&amount, msg.data()+offset, sizeof(int));
        offset += size_int;
        amount = ntohl(amount);
        for(int i = 0; i < amount;i++){
            player_t player_aux;
            memcpy(&player_aux.player_id, msg.data()+offset, size_int);
            offset += size_int;
            memcpy(&player_aux.pos_x, msg.data() + offset, size_float);
            offset += size_float;
            memcpy(&player_aux.pos_y, msg.data() + offset, size_float);
            offset += size_float;
            memcpy(&player_aux.direction, msg.data() + offset, size_float);
            offset += size_float;
            memcpy(&player_aux.ammo, msg.data() + offset,size_int);
            offset += size_int;
            memcpy(&player_aux.current_weapon, msg.data() + offset, sizeof(char));
            offset += sizeof(char);
            memcpy(&player_aux.health, msg.data() + offset, sizeof(double));
            offset += sizeof(double);
            memcpy(&player_aux.lives, msg.data() + offset, size_int);
            offset += size_int;
            memcpy(&player_aux.score, msg.data() + offset, size_int);
            offset += size_int;
            snapshot.add_player(player_aux);
        }
    }
}
void Serializer::deserialize_objects(std::vector <char> & msg, Snapshot & snapshot, int & offset){
    char snap_id = 'o';
    int size_int = sizeof(int);
    int size_bool = sizeof(bool);
    int amount = 0;
    int size_double = sizeof(double);
    object_t* object_aux;

    memcpy(&snap_id, msg.data()+offset, sizeof(char));
    offset += sizeof(char);

    if (snap_id == 'o'){
        memcpy(&amount, msg.data()+offset, size_int);
        offset += sizeof(int);
        amount = ntohl(amount);

        for(int i = 0; i<amount; i++){
            object_t object_aux;
            memcpy(&object_aux.id, msg.data()+offset, size_int);
            offset += size_int;
            memcpy(&object_aux.pos_x, msg.data() + offset, size_double);
            offset += size_double;
            memcpy(&object_aux.pos_y, msg.data() + offset, size_double);
            offset += size_double;
            memcpy(&object_aux.state, msg.data() + offset, size_bool);
            offset += size_bool;
            snapshot.add_object(object_aux);
        }
    }
}
void Serializer::deserializer(std::vector <char> & msg, Snapshot & snapshot){
    int offset = 0;
    if (msg.size() > 0){
        deserialize_players(msg, snapshot, offset);
        deserialize_objects(msg, snapshot, offset);
    }
   

    // std::cout << "/********PLAYER*********/"<<std::endl;
    // std::cout << player_info.player_id <<std::endl;
    // std::cout << player_info.pos_x <<std::endl;
    // std::cout << player_info.pos_y <<std::endl;
    // std::cout << player_info.direction <<std::endl;
    // std::cout << player_info.ammo <<std::endl;
    // std::cout << player_info.current_weapon <<std::endl;
    // std::cout << "/**********************/"<<std::endl;

}
void Serializer::deserialize_action(std::vector <char> & msg, ProtectedQueueAction & actions){
    int offset = 0;
    int action_id = -1;
    int size_int = sizeof(int);
    int size_double = sizeof(double);
    int amount = 0;

    memcpy(&amount, msg.data()+offset, size_int);
    offset += size_int;
    amount = ntohl(amount);

    for(int i = 0; i < amount ; i++){
        memcpy(&action_id, msg.data() + offset, size_int);
        offset += size_int;
        Action action(action_id);
        memcpy(&action.impact_x, msg.data() + offset, size_double);
        offset += size_double;
        memcpy(&action.impact_y, msg.data() + offset, size_double);
        offset += size_double;
        memcpy(&action.weapon_id, msg.data() + offset, sizeof(char));
        offset += sizeof(char);
        memcpy(&action.state, msg.data() + offset, sizeof(bool));
        offset += sizeof(bool);
        actions.add_element(action);
        // snapshot.add_action(action);
    }
    // std::cout << "/*******intention*******/"<<std::endl;
    // std::cout << action->player_id <<std::endl;
    // std::cout << action->impact_x <<std::endl;
    // std::cout << action->impact_y <<std::endl;
    // std::cout << action->weapon_id <<std::endl;
    // std::cout << "/**********************/"<<std::endl;
}
