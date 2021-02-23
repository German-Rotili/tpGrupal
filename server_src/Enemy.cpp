#include "Enemy.h"
#include <algorithm>
#include <cassert>
#include <vector>
#include <chrono>
#include <utility>


bool CheckLua(lua_State *L, int r)
    {
        if (r != LUA_OK)
        {
            std::string errormsg = lua_tostring(L, -1);
            std::cout << errormsg << std::endl;
            return false;
        }
        return true;
    }

Enemy::Enemy(int id, ProtectedQueueIntention *intention, std::vector<int> players_id, std::vector<std::vector<int>> & map):
    enemy_id(id), intentions(intention), players_id(players_id), map(map){
    this->L = luaL_newstate();
    luaL_openlibs(this->L);
}

Enemy::~Enemy(){
    lua_close(this->L);
    this->dead = true;
    this->snapshots.close_queue();
}

void Enemy::stop(){
    this->dead = true;
    this->snapshots.close_queue();
}



void Enemy::attack_players(std::vector<char> & intention){
   try{
    Snapshot snapshot = this->snapshots.get_element();
    size_t one =1;
    lua_getglobal(this->L, "ProcessSnapshot");
        if (lua_isfunction(this->L, -1)){
            lua_createtable(L, 2, 0); //Creo la tabla que va a tener players y enemigo.

                lua_pushnumber(L, 1); //Creo la tabla de players y lleno de datos.
                lua_createtable(L, players_id.size() , 0);
                int index = 1;

            for (player_t &player : snapshot.players){
                if(std::find(players_id.begin(), players_id.end(), player.player_id) != players_id.end() ){
                    lua_pushnumber(L, index); // tabla para un player.
                    lua_createtable(L, 4, 0);

                        lua_pushnumber(L,  player.pos_x);
                        lua_setfield(L, -2, "pos_x");

                        lua_pushnumber(L,  player.pos_y);
                        lua_setfield(L, -2, "pos_y");

                        lua_pushnumber(L,  player.player_id);
                        lua_setfield(L, -2, "id");

                        lua_pushnumber(L,  player.health);
                        lua_setfield(L, -2, "health");

                    lua_settable(this->L, -3);
                    index +=1;
                }
            }

            lua_settable(this->L, -3);

            //Enemigo Actual
            player_t enemy_aux = snapshot.get_player(this->enemy_id);
            lua_pushnumber(L, 2);
            lua_createtable(L, 5, 0);

                lua_pushnumber(L,  enemy_aux.pos_x);
                lua_setfield(L, -2, "pos_x");

                lua_pushnumber(L,  enemy_aux.pos_y);
                lua_setfield(L, -2, "pos_y");

                lua_pushnumber(L,  enemy_aux.direction);
                lua_setfield(L, -2, "direction");

                if(enemy_aux.current_weapon == KNFIE){
                    lua_pushnumber(L,  1);
                }else{
                    lua_pushnumber(L,  3);
                }
                lua_setfield(L, -2, "range");

                lua_pushnumber(L,  enemy_aux.ammo);
                lua_setfield(L, -2, "ammo");

            lua_settable(this->L, -3);

            if (CheckLua(L, lua_pcall(L, 1, 1, 0))){
                intention.push_back((const char)*lua_tolstring(L, -1, &(one)) );
            }
        }
         } catch (std::exception const& e) {
            std::cout << "Enemy Closed:" << std::endl;
            this->dead = true;
        }
        catch (...) {
            std::cout << "Error inesperado en conexion" << std::endl;
        }
}

void Enemy::run(){
        // if(!CheckLua(L, luaL_dofile(L, "EnemyLogic.lua"))){
        if(!CheckLua(L, luaL_dofile(L, "../server_src/EnemyLogic.lua"))){
            std::cout << "Enemys not available" <<std::endl;
        }

        while (!this->is_dead()){

            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
            lua_settop(this->L, 0);
            std::vector<char> intention;
            this->attack_players(intention);
            Intention intention_aux(this->enemy_id, intention);
            this->intentions->add_element(intention_aux);

            std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
            unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
            int sleep_time = 1000000/FPS - elapsed_microseconds;
            if (sleep_time > 0) {
                usleep(1000000/FPS - elapsed_microseconds);
            }else{
                std::cout << "Bajada FPS" << std::endl;
            }
        }
}
