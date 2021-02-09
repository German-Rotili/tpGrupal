#ifndef IDMAKER
#define IDMAKER
#include <mutex>
class IdMaker{

private:
    std::mutex m;
    int current = 0;

public:
    IdMaker();
    ~IdMaker();
    int generate_id();

};


#endif