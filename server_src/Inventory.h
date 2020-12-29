#ifndef __SERVER_INVENTORY_H__
#define __SERVER_INVENTORY_H__

class Inventory{

    // aca hardcodeamos todas las armas. despues tiene una lista de armas que si tiene y una que es la actual. me parece mas simple y
    //evitamos pedir memoria. todo el juego puede correr en stack por ahora en el server.

private:
    
public:
    Inventory(/* args */);
    ~Inventory();
    bool pick_up_weapon();
    bool fire_current_weapon();
    bool change_weapon(char);
    
};


#endif // __SERVER_INVENTORY_H__