#ifndef INTENTION_H
#define INTENTION_H
#include <vector>

class Intention{
private:
    int client_id;
    std::vector<char> intention;
public:
    Intention(int client_id, std::vector<char> intention);
    std::vector<char> & get_intention();
    int & get_id();
    ~Intention();
};

#endif