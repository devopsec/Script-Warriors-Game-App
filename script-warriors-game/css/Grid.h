
#ifndef rpg_grid_h
#define rpg_grid_h

#include <vector>
#include "Entity.h"

using namespace std;

class Grid
{
private:
    bool map[20][20];
    int numrooms;
    vector<Entity> inventory[20][20];
    int inv_size[20][20];
public:
    Grid()
    {
        for(int i = 0; i < 20; i++)
            for(int j = 0; j < 20; j++)
            {
                map[i][j] = false;
                inv_size[i][j] = 0;
            }
        numrooms = 0;
    }
    bool Get(int x, int y)
    {
        return map[x][y];
    }

    void Set(int x, int y)
    {
        map[x][y] = true;
    }
    void AddRoom()
    {
        numrooms++;
    }
    int GetNum()
    {
        return numrooms;
    }
    void Describe_inv(int x, int y)
    {
        if (inv_size == 0)
            cout << "The room is empty" << endl;
        else
            for(int i = 0; i < inv_size[x][y]; i++)
            {
                inventory[x][y][i].Describe();
            }
    }
    void Add_Inv(Entity obj, int x, int y)
    {
        inventory[x][y].push_back(obj);
        inv_size[x][y]++;
    }
    void Remove(string name, int x, int y)
    {
        for(int i = 0; i < inv_size[x][y]; i++)
        {
            if(inventory[x][y][i].Getname() == name)
            {
                inventory[x][y].erase(inventory[x][y].begin()+(i));
                inv_size[x][y]--;
            }
        }
    }
    bool Search_Inv(string name, int x, int y)
    {
        for(int i = 0; i < inv_size[x][y]; i++)
        {
            if(inventory[x][y][i].Getname() == name)
            {
                return true;
            }
        }
        return false;
    }
};

#endif
