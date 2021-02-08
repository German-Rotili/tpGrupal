#ifndef __SERVER_PLAYER_H__
#define __SERVER_PLAYER_H__
#include <string>
#include "Position.h"
#include "Map.h"
#include "weapons/Weapon.h"
#include "Inventory.h"

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

class Player{
private:
    char id;
    Position position;
    bool is_alive;
    Map &map;
    Inventory inventory;
    bool placed;
    int spawn_x;
    int spawn_y;
    char hitpoints;

    void attack();
    void acction();
    void intersects(float impx, float impy, Player &player);
    void process_near_item();

    //life
public:
    Player(Map &, Config &,Position position);
    Player(Map &,Config &, float, float, float);
    Player(Map &, Config &, char id);
    ~Player();

    bool is_placed();
    float get_pos_x();
    float get_pos_y();
    float get_direction();
    int get_id();
    int get_ammo();
    char get_current_weapon_id();
    void set_spawn(int x, int y);
    
   
    void execute_intention(char intention);
    void get_damaged(int damage);
    void tick();
    float get_hitbox_radius();
    float get_distance(Position position);
    float get_distance(float x, float y);
    float get_angle_difference(Position position);
    float get_angle_difference(float x, float y); 
    void check_if_item();
    void heal(char id);
    void collect_treasure(char id);

    bool is_in_hitbox(float x, float y);
};

#endif // __SERVER_PLAYER_H__