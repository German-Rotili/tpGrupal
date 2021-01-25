#include <vector>
#include "../server_src/Map.h"

class Serializer
{
private:

    Map map;
    void serialize_players(std::vector<char> &message);
    void append_variable(std::vector<char> &message, char *variable, size_t size);
    void append_float(std::vector<char> &message, float number);
public:
    Serializer();
    ~Serializer();
    std::vector<char> serialize();
    
};

