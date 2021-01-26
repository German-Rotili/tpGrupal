#include <vector>
#include "../server_src/Map.h"
#include <sstream>

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
    void deserialize(std::vector<char> &);
    int extract_int(std::stringstream &);
    float extract_float(std::stringstream &);

};

