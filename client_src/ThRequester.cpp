#include "ThRequester.h"
#include "client_helper.h"
#include "../common_src/ConnectionClosedException.h"

ThRequester::ThRequester(Client & client, ProtectedQueueAction & actions):
client(client),
state(true),
actions(actions),
obtainedId(INVALID_ID) {}

ThRequester::~ThRequester() {
  std::cout<< "Destructor del requester" << std::endl;

}

void ThRequester::stop(){
    this->state = false;
}

Snapshot ThRequester::get_snapshot() {
    if (this->is_dead()) {
      throw ConnectionClosedException();
    }
    std::unique_lock<std::mutex> lock(m);
  std::cout<< "ME pidieron snapshot" << std::endl;

    Snapshot new_snapshot = this->snapshot;
    return new_snapshot;
}

int ThRequester::getObtainedId() {
  return this->obtainedId;
}

bool ThRequester::is_active(){
  return this->client.is_active();
}

void ThRequester::run() {
  try {
    obtainedId = client.await_game_start();
    while (this->state && this->client.is_active()) {
        Snapshot snap_aux;
        client.receive_update(snap_aux, this->actions);   
        std::unique_lock<std::mutex> lock(this->m);
        this->snapshot = snap_aux;
    }
  } catch (std::exception const& e) {
    std::cerr << "Exception on ThRequester:" << std::endl;
    std::cerr << e.what() << std::endl;
    this->dead = true;
  }
  catch (...) {
    this->dead = true;
    std::cerr << "Error inesperado en ThRequester" << std::endl;
  }
  std::cout<< "Sali del while" << std::endl;
  
}
