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

class intentions{
private:
    std::string players;
    std::string object;
    std::string player;
    
public:
    intentions();
    ~intentions();
    void add_object();
    void add_player();
    void update_player();
    const char* get_intentions();
    intentions(std::string buffer);

};
#endif