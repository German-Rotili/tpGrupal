#ifndef __HITSCANRAYCAST_H__
#define __HITSCANRAYCAST_H__

#include <tuple>
#include "Map.h"

class HitscanRaycast
{
private:
    /* data */
public:
    HitscanRaycast(/* args */);
    ~HitscanRaycast();
    std::tuple<int, int> get_impact(Map &map, Player &player);
};



#endif // __HITSCANRAYCAST_H__