//
//  Player.h
//  rpg
//
//  Created by Laria R on 5/21/16.
//  Copyright (c) 2016 Laria R. All rights reserved.
//

#ifndef rpg_Player_h
#define rpg_Player_h
#include "Entity.h"
#include <vector>

using namespace std;


class Player : public Entity
{
private:
    int HP;
    int AP;
    vector<Entity> inventory;
    int inv_size;
public:
    Player(string n="defaultplayer"):Entity(n)
    {
        name = n;
        type = 's';
        inv_size = 0;
    }
    void Add_Inv(Entity & obj)
    {
        inventory.push_back(obj);
        inv_size++;
    }
    void Remove(string name)
    {
        for(int i = 0; i < inv_size; i++)
        {
            if(inventory[i].Getname() == name)
            {
                inventory.erase(inventory.begin()+(i));
                inv_size--;
            }
        }
    }
    bool Search_Inv(string name)
    {
        for(int i = 0; i < inv_size; i++)
        {
            if(inventory[i].Getname() == name)
            {
                return true;
            }
        }
        return false;
    }
    void List_Inv()
    {
        cout << "You are carrying:" << endl;
        for(int i = 0; i < inv_size; i++)
        {
            cout << inventory[i].Getname() << endl;
        }
        
    }
    Entity &Get_Inv(string name)
    {
        for(int i = 0; i < inv_size; i++)
        {
            if(inventory[i].Getname() == name)
            {
                return inventory[i];
            }
        }
    }
    int Get_Inv_Size()
    {
        return inv_size;
    }

    
};

#endif
