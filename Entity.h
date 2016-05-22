//
//  Entity.h
//  rpg
//
//  Created by Laria R on 5/21/16.
//  Copyright (c) 2016 Laria R. All rights reserved.
//

#ifndef rpg_Entity_h
#define rpg_Entity_h

using namespace std;

class Entity
{
protected:
    string name;
    char type; //  o = object, s = self, e = enemy, f = friend
    
public:
    Entity(string n)
    {
        name = n;
        type = 'o';
    }
    string Getname()
    {
        return name;
    }
    void Describe()
    {
        if(type == 'o')
            cout << "There is a " << name <<" in the room." << endl;
    }
};

#endif
