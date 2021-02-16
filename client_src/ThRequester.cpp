#include "ThRequester.h"
#include "client_helper.h"

ThRequester::ThRequester(Client & client, ProtectedQueueAction & actions):client(client),state(true), actions(actions){}

ThRequester::~ThRequester(){}

void ThRequester::stop(){
    this->state = false;
}

Snapshot ThRequester::get_snapshot(){
    std::unique_lock<std::mutex> lock(m);
    Snapshot new_snapshot = this->snapshot;
    return new_snapshot;
}

void ThRequester::run(){

    while (this->state) {
        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

        Snapshot snap_aux;
        client.receive_update(snap_aux, this->actions);
        // client.recieve_snapshot(snap_aux);

        {
            std::unique_lock<std::mutex> lock(this->m);
            this->snapshot = snap_aux;
        }

        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        unsigned int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        int sleep_time = 1000000/60 - elapsed_microseconds;
        if (sleep_time > 0) {
            usleep(1000000/60 - elapsed_microseconds);
        } else {
            std::cout << "Server tarda en responder" << std::endl;
        }
    }
}
