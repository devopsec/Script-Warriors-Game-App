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
public:
    Player(string n="defaultplayer"):Entity(n)
    {
        name = n;
        type = 's';
    }
    
};

#endif
