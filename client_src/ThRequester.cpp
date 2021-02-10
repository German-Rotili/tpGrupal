#include "ThRequester.h"
#include "client_helper.h"

ThRequester::ThRequester(Client & client):client(client),state(true){}

ThRequester::~ThRequester(){}

void ThRequester::stop(){
    this->state = false;
}

Snapshot ThRequester::get_snapshot(){

    /*Hacer un metodo en Snapshot que devuelva una copia de si mismo, aplicando locks*/

    /*mutex*/
    Snapshot new_snapshot = this->snapshot;
    /*******/
    
    
    return new_snapshot;

    // player.ammo = this->player_client.ammo;
    // player.pos_x = this->player_client.pos_x;
    // player.pos_y = this->player_client.pos_y;
    // player.direction = this->player_client.direction;
    // player.current_weapon= this->player_client.current_weapon;
    // player.player_id = this->player_client.player_id;
    //en el cliente tenemos un vector con las acciones para que no se pierdan, antes del snapshot ejecuto todas las acciones
    //
}

void ThRequester::run(){

    while (this->state) {
        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        
        Snapshot snap_aux;
        std::cout << "intento recibir snapshot" << std::endl;

        client.recieve_snapshot(snap_aux);
        
        std::cout << "logro recibir snapshot" << std::endl;

        /*mutex*/
        this->snapshot = snap_aux;
        /*******/
        
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        int sleep_time = 1000000/60 - elapsed_microseconds;
        if (sleep_time > 0) {
            usleep(1000000/60 - elapsed_microseconds);
        } else {
            printf("Server tarda en responder");
        }
    }
}
