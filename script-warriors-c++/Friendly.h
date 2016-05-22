//
//  Friendly.h
//  rpg
//
//  Created by Laria R on 5/21/16.
//  Copyright (c) 2016 Laria R. All rights reserved.
//

#ifndef rpg_Friendly_h
#define rpg_Friendly_h
#include "Entity.h"
#include "Player.h"
#include <vector>


class Friendly : public Player
{
private:
public:
    Friendly(string n="defaultfriendly", int x = 5, int y = 5):Player(n, x, y)
    {
    }


};



#endif
