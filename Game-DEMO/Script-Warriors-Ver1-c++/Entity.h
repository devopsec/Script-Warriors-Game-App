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
        alive = 1;
    }
    int HP;
    bool alive;

    string Getname()
    {
        return name;
    }
    void Describe()
    {
        if(type == 'o')
            cout << "There is a " << name <<" in the room." << endl;
        else if (type == 'f')
        {
            cout << name << "(friend) is in the room." << endl;
        }
        
        else if (type == 'e')
            cout << name << "(enemy) is in the room." << endl;

    }
    Entity Set_type(char t)
    {
        type = t;
        return *this;
    }
    char Get_type()
    {
        return type;
    }
    void kill()
    {
        alive = 0;
    }
};

#endif
