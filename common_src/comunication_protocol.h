#ifndef DBUS_PROTOCOL_H
#define DBUS_PROTOCOL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string>

class Snapshot{
private:
    std::string players;
    std::string object;
    std::string player;
    
public:
    Snapshot();
    ~Snapshot();
    void add_object();
    void add_player();
    void update_player();
    const char* get_snapshot();
    Snapshot(std::string buffer);

};
#endif