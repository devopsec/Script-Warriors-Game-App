//
//  playerslist.h
//  rpg
//
//  Created by Laria R on 5/22/16.
//  Copyright (c) 2016 Laria R. All rights reserved.
//

#ifndef rpg_playerslist_h
#define rpg_playerslist_h
#include "Player.h"
#include <vector>

using namespace std;


class Playerslist
{
private:
    vector<Player> players;
    int listsize;
public:
    Playerslist()
    {
        listsize = 0;
    }
    void add(Player p1)
    {
        players.push_back(p1);
        listsize++;
    }
    Player Get(string n)
    {
        for(int i = 0; i < listsize; i++)
        {
            if(players[i].Getname() == n)
            {
                return players[i];
            }
        }
    }
};

#endif
