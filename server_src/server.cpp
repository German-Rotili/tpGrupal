#include "Map.h"
#include "player.h"
#include "helper.h"
#include <iostream>
#include <string>
#define PORT 1
#define ROOT 2

int main(int argc, char const *argv[]){

    if (argc > 3) {
        return 1;
    }
    try {
        Server serv;
        std::string port = argv[PORT];
        std::string rootname = argv[ROOT];
        serv.run(port, rootname);
    }
    catch(const std::exception& e){
        perror(e.what());
        return 1;
    } catch(...){
        return 1;
    }
    return 0;


    // int width = 500;
    // int height = 500;
    // Map map(width, height);
    // std::string direction = "r";
   

    // Player player_1(width, height, direction);
    // Player player_2(width, height,direction);
    // Player player_3(width, height,direction);

    // map.add_player(player_1);
    // map.add_player(player_2);
    // map.add_player(player_3);

    // map.move_player(player_1, direction);

    // direction = "l";
    // map.move_player(player_2, direction);

    // direction = "r";
    // map.move_player(player_3, direction);


    // std::cout << "Player 1 AFTER position: " << player_1.get_pos_x() << " " <<  player_1.get_pos_y() <<std::endl;
    // std::cout << "Player 2 AFTER position: " << player_2.get_pos_x() << " " <<  player_2.get_pos_y() <<std::endl;
    // std::cout << "Player 3 AFTER position: " << player_3.get_pos_x() << " " <<  player_3.get_pos_y() <<std::endl;


    //read from config.yaml

    //create GameMap

    //Map Initializer(config)


    // return 0;
}
