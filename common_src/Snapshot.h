#ifndef __SNAPSHOT__
#define __SNAPSHOT__
#include <vector>
#include "Serializer.h"
#include "Action.h"

class World;
struct player_t;
struct intention_t;
struct object_t;

class Snapshot{
private:

    std::vector<player_t> players;
    std::vector<object_t> objects;
    std::vector <Action> actions;

public:
    Snapshot();
    ~Snapshot();
    player_t get_player(int & id);
    object_t get_object(int & id);
    Action get_action(int & id);
    void add_player(player_t player);
    void add_object(object_t object);
    void add_action(Action action);

    void print();


friend class Serializer;
friend class World;
friend class Enemy;

};


#endif