#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__


//esta clase lee del config file y desde aca se cargan los parametros. 

class Config
{
private:
    /* data */
public:
    Config(/* args */);
    ~Config();

    float get_angular_velocity();
    float get_linear_velocity();
    int get_max_damage(int);
    float get_max_spread(int);
};


#endif // __SERVER_CONFIG_H__