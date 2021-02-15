#include "Intention.h"
Intention::Intention(int client_id, std::vector<char> intention):client_id(client_id), intention(intention){}

int & Intention::get_id(){
    return this->client_id;
}
std::vector<char> & Intention::get_intention(){
    return this->intention;
}

Intention::~Intention(){}
