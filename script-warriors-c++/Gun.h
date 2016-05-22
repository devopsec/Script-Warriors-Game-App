//
//  Gun.h
//  rpg
//
//  Created by Laria R on 5/22/16.
//  Copyright (c) 2016 Laria R. All rights reserved.
//

#ifndef rpg_Gun_h
#define rpg_Gun_h
#include "Entity.h"


using namespace std;

class Gun : public Entity
{
private:
    int ammo;
    int capacity;
    int damage;
    int accuracy_sameroom;
    int accuracy_nextroom;
public:
    Gun(string n, int d = 50, int c = 5, int a_s = 80, int a_n = 40) : Entity(n)
    {
        name = n;
        damage = d;
        capacity = c;
        ammo = capacity;
        accuracy_nextroom = a_n;
        accuracy_sameroom = a_s;
    }
    bool Shoot_Inroom()
    {
        int r = arc4random_uniform(100);
        if(r < accuracy_sameroom)
        {
            return true;
        }
        else
            return false;
    }

bool Shoot_Nextroom()
{
    int r = arc4random_uniform(100);
    if(r < accuracy_nextroom)
    {
        return true;
    }
    else
        return false;
}

};
#endif
