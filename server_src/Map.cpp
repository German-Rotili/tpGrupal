#include "Map.h"
#include "../common_src/Action.h"
#include "../common_src/MapHandler.h"
#include "./weapons/Rocket.h"
#include "ServerConfigHandler.h"
#include "Constants.h"
#include "Door.h"
#include "GamePlay.h"
#include "Player.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>

void Map::add_player(int id, std::vector<char> username){
  this->players.push_back(new Player(this, &(this->config), id, username));
}

std::vector<Player *> &Map::get_players() { return this->players; }

std::map<int, std::map<int, Door>> &Map::get_doors() { return this->doors; }

void Map::start() { this->populate_variables(); }

void Map::add_rocket(float posx, float posy, float direction, Player *player) {

  this->rockets.push_back(new Rocket(this, &this->config, player, posx, posy, direction));
}

void Map::tick() {
  for (Player *player : this->players) {
    player->tick();
  }
  for (Rocket *rocket : this->rockets) {
    auto i = std::begin(this->rockets);
    while (i != this->rockets.end()) {
      if ((*i)->tick()) {
        delete *i;
        i = this->rockets.erase(i);
      } else {
        i++;
      }
    }
  }
  for(auto &x : this->doors){
        for(auto &y : x.second){
          y.second.tick();
       }
    }
}

std::vector<char> Map::get_raw_map() { return this->raw_map; }

void Map::add_action(int player_id, float weapon_id, float posx, float posy) {
  Action action(player_id);
  action.update_values(posx, posy, weapon_id);
  this->actions.push_back(action);
}

void Map::add_item(int id, int x, int y) // use goto para facilitar la lectura de este codigo horrendo
{ if(id >= 2 && id <= 4) id +=48;
  for(int i = 0; i < 4 ; i++){
    for(int j = 0; i < 4; i++){
      if(this->get_id(x + i, y + j) == 57) {
        x += i;
        y += j;
        goto end;
      }
      if(this->get_id(x - i, y + j) == 57) {
        x -= i;
        y += j;
        goto end;

      }
      if(this->get_id(x + i, y - j) == 57) {
        x += i;
        y -= j;
        goto end;

      }
      if(this->get_id(x - i, y - j) == 57) {
        x -= i;
        y -= j;
        goto end;

      }
      if(this->get_id(x + j, y + i) == 57) {
        x += i;
        y += j;
        goto end;
      }
      if(this->get_id(x - j, y + i) == 57) {
        x -= i;
        y += j;
        goto end;
      }
      if(this->get_id(x + j, y - i) == 57) {
        x += i;
        y -= j;
        goto end;
      }
      if(this->get_id(x - j, y - i) == 57) {
        x -= i;
        y -= j;
        goto end;
      }
    }
  }

  end:  //checkkeo que no haya llegado porque termino de loopear. 
  if(this->get_id(x, y) == 57) {
    this->items[x][y] = id;
    this->map[x][y] = id;
  }
  //horrible pero legible.
}

bool Map::is_game_over() 
{
  int not_finished = 0;
   for (Player *player : this->players) {
     if(!player->is_finished()){
       not_finished +=1;
     }
  }
  return (not_finished <= 1 || this->game_timer.elapsed_time() > this->game_time_limit);
}

void Map::remove_item(int x, int y) {
  this->map[x][y] = EMPTY;
  this->items[x].erase(y);
}

bool Map::is_item(char id) { return (id <= 56 && id >= 44); }

bool Map::valid_position(int x, int y) {
  if (x < 0 || x >= this->map.size() || y < 0 || y >= this->map[x].size()) {
    // std::cout << "en x: " << x << " y: " << y << "fuera de rango" << std::endl;
    return false;
  }
  int squareId = this->get_id(x, y);
  if (this->is_solid(squareId)) {

    return false;
  }
  if (this->is_door(squareId)) {
    // std::cout << "en x: " << x << " y: " << y << "door id: " << squareId
              // << std::endl;

    return this->doors.find(x)->second.find(y)->second.is_walkable();
  }
  return true;
}

bool Map::is_impactable(int x, int y) {
  if (x < 0 || x >= this->map.size() || y < 0 || y >= this->map[x].size()) {
    return true;
  }
  char squareId = this->get_id(x, y);
  return (this->is_solid(squareId));
}

Map::~Map() {
   for (Player *player : this->players) {
    delete player;
  }
  for (Rocket *rocket : this->rockets) {
    delete rocket;
  }
}

int Map::get_id(int x, int y) { 
    if (x < 0 || x >= this->map.size() || y < 0 || y >= this->map[x].size()) {
      return 0;
      }

  return this->map[x][y]; 
  }

bool Map::is_solid(int id) {
  if (id >= 0 && id <= 33) {
    return true;
  }
  if (id >= 36 && id <= 39) {
    return true;
  }
  return false;
}

bool Map::is_door(int id) {
  return (id == 34 || id == 35 || (id >= 59 && id <= 64));
}

bool Map::is_spawn(int id) { return id == 58; }



Map::Map(std::vector<char> raw_map) : raw_map{raw_map} {
  std::string map_aux(raw_map.data());
  MapHandler handler;
  try {
    std::vector<std::vector<int>> vector_al_revez =
        handler.readMapFromString(map_aux);
    //    this->map = handler.readMap("../resources/config/map1.yaml");
    for (int x = 0; x < vector_al_revez[0].size(); x++) {
      this->map.push_back(std::vector<int>());
      for (int y = 0; y < vector_al_revez.size(); y++) {
        this->map[x].push_back(vector_al_revez[y][x]);
      }
    }
  } catch (std::exception const &e) {
    printf("Hubo una excepción: ");
    std::cout << e.what() << "\n";
  }
}



void Map::populate_variables() {

  for (int x = 0; x < this->map.size(); x++) {
    for (int y = 0; y < this->map[y].size(); y++) {
      // std::cout << "populating x: " << x << " y: " << y << std::endl;
      int id = this->get_id(x,y);

      if (this->is_door(id)) {
        this->doors[x].insert(std::pair<int, Door>(y, Door(id)));
      }
      if (this->is_spawn(id)) {
        // std::cout << "is spawn" << std::endl;
        for (Player *player : this->players) {
          if (!player->is_placed()) {
            // std::cout << "placing" << std::endl;
            player->set_spawn(x, y);
            break;
          }
        }
      }
      if (this->is_item(id)) {
        this->items[x][y] = id;
      }
    }
  }
  this->game_timer.start();
}

void Map::execute_intentions(std::vector<char> intentions, int client_id) {

  for (Player *player : this->players) {

    if (player->get_id() == client_id) {

      for (char &i : intentions) {
        if (i != 0) {
          char aux = intentions.front();
          intentions.erase(intentions.begin());
          player->execute_intention(aux);
          // std::cout << "caracter procesado: " <<aux << " del id: "<<client_id <<std::endl;

        }
      }
      break;
    }
  }
  // std::cout << "salimos de exe int" << std::endl;
}
