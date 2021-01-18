#include "comunication_protocol.h"

Snapshot::Snapshot(){}

Snapshot::Snapshot(std::string buffer){

}

Snapshot::~Snapshot(){}

void Snapshot::add_object(){
    this->object += "id:21,type:door,status:true,position:{x:1,y:1}/";
}

void Snapshot::add_player(){
    this->players += "id:3,position:{x:1,y:1,o:90},weapon:knife,attack:true/";
}

void Snapshot::update_player(){
    this->player += "position:{x:1,y:1,o:90},weapons:pistol,life:100,attack:false/";
}

const char* Snapshot::get_snapshot(){ 

    std::string buffer = std::to_string(this->object.size());
    buffer += object;
    
    return buffer.c_str();

}