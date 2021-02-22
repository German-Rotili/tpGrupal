#ifndef __SERVER_PLAYER_H__
#define __SERVER_PLAYER_H__


// struct player_t {
//     int player_id;
//     float pos_x;
//     float pos_y;
//     float direction;
//     int ammo;
//     char current_weapon;
// };

//Para el manejo de las acciones. agregar una lista de acciones que ocurren en cada iteracion. para esto cuando el server 
//prepare el mensaje al cliente leera desde esta lista las acciones que son relevantes al cliente por ejemplo;
// dispara, abre puerta, recibe daño, etc. 
#include "Position.h"
#include "Inventory.h"
#include "../common_src/Timer.h"

class Config;

class Player{
private:
    int id;
    Position position;
    bool is_alive = true;
    bool finished = false;
    Map *map;
    Inventory inventory;
    Timer death_timer;
    int respawn_time = 5000;
    bool placed = false;
    int spawn_x;
    int spawn_y;
    int hitpoints = 300;
    int lives = 5;
    int score = 0;
    int kills = 0;

    void attack();
    void acction();
    void intersects(float impx, float impy, Player &player);
    void process_near_item();

    //life
public:
    Player(Map *, Config *,Position position);
    Player(Map &,Config &, float, float, float);
    Player(Map *, Config *, int id); 

    bool is_placed();
    float get_pos_x();
    float get_pos_y();
    float get_direction();
    int get_id();
    int get_ammo();
    char get_current_weapon_id();
    void set_spawn(int x, int y);
    int get_hitpoints();
    int get_lives();
    int get_score();
    void add_kill_points();
    void execute_intention(char intention);
    bool get_damaged(int damage);
    void tick();
    float get_hitbox_radius();
    float get_distance(Position *position);
    float get_distance(float x, float y);
    float get_distance(Player *player);
    float get_angle_difference(Position position);
    float get_angle_difference(float x, float y); 
    void heal(char id);
    void collect_treasure(char id);
    bool is_finished();
    bool is_in_hitbox(float x, float y);
};

#endif // __SERVER_PLAYER_H__