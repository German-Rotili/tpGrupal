#ifndef  __ACTION_H__
#define  __ACTION_H__
#include  <atomic>

class Action{
    private:
        int player_id; //-1 para explociones
        char weapon_id;
        std::atomic <bool> state;
        double impact_y;
        double impact_x;
    public:

        explicit Action(int id);
        ~Action();
        bool active();
        void update_state(bool new_state);
        void update_values(double impact_x, double impact_y, char weapon_id);
        int get_id();
        // Action& operator=(const Action&) = delete;
        // Action(const Action&) = delete;
        // Action(Action&& other);
        // Action& operator=(Action&& other);

    friend class World;
    friend class GamePlay; 
    friend class Serializer; 
};

#endif
