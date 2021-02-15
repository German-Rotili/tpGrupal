#ifndef IDMAKER
#define IDMAKER
#include <mutex>
class IdMaker{

private:
    static IdMaker *instance;
    static std::mutex m;
protected:
    int current = 0;
    IdMaker();
    ~IdMaker();
public:
    int generate_id();
    IdMaker(IdMaker &other) = delete;
    void operator=(const IdMaker &) = delete;
    static IdMaker *GetInstance();

};

#endif
