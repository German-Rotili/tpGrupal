#include "ThRequester.h"
#include "client_helper.h"
#include "../common_src/ConnectionClosedException.h"

ThRequester::ThRequester(Client & client, ProtectedQueueAction & actions):
client(client),
state(true),
actions(actions),
obtainedId(INVALID_ID) {}

ThRequester::~ThRequester() {}

void ThRequester::stop(){
    this->state = false;
}

Snapshot ThRequester::get_snapshot() {
    if (this->is_dead()) {
      throw ConnectionClosedException();
    }
    std::unique_lock<std::mutex> lock(m);
    Snapshot new_snapshot = this->snapshot;
    return new_snapshot;
}

int ThRequester::getObtainedId() {
  return this->obtainedId;
}

void ThRequester::run(){
  try{
    obtainedId = client.await_game_start();

    while (this->state) {
        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

        Snapshot snap_aux;
        client.receive_update(snap_aux, this->actions);
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
  } catch (std::exception const& e) {
    std::cout << "Hubo una excepción:" << std::endl;
    std::cout << e.what() << std::endl;
    this->dead = true;
  }
  catch (...) {
    this->dead = true;
    std::cout << "Error inesperado en conexion" << std::endl;
  }

}
