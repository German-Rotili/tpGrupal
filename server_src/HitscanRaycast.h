#ifndef __HITSCANRAYCAST_H__
#define __HITSCANRAYCAST_H__

#include <tuple>
class Player;
class Map;

class HitscanRaycast
{
private:
    /* data */
public:
    HitscanRaycast(/* args */);
    ~HitscanRaycast();
    std::pair<float, float> get_impact_point(Map &map, Player &player);
};



#endif // __HITSCANRAYCAST_H__