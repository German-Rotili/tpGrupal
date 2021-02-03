#include "comunication_protocol.h"

intentions::intentions(){}

intentions::intentions(std::string buffer){

}

intentions::~intentions(){}

void intentions::add_object(){
    this->object += "id:21,type:door,status:true,position:{x:1,y:1}/";
}

void intentions::add_player(){
    this->players += "id:3,position:{x:1,y:1,o:90},weapon:knife,attack:true/";
}

void intentions::update_player(){
    this->player += "position:{x:1,y:1,o:90},weapons:pistol,life:100,attack:false/";
}

const char* intentions::get_intentions(){

    std::string buffer = std::to_string(this->object.size());
    buffer += object;
    
    return buffer.c_str();

}