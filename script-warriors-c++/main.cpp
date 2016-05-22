
#include <iostream>
#include "Grid.h"
#include "Room.h"
#include "bitmap_image.h"
#include <time.h>
#include "Entity.h"
#include "Player.h"

using namespace std;

/*void drawLineSegment(int p1x, int p1y,int p2x, int p2y, bitmap_image &map)
{

    
    int xdif = p2x-p1x;
    int ydif = p2y-p1y;
    
    int length = round(sqrt(xdif*xdif+ydif*ydif));
    if (length == 0) //to avoid division by 0
    {
        return;
    }
        double x_comp = xdif/double(length);
    double y_comp = ydif/double(length);
    
    for(int i = 0; i < length; i++)
    {
        map.set_pixel(p1x + i*x_comp + 50, (-1*(p1y + i*y_comp)+950), 255, 255, 255);
    }
    
}*/

void saveImage(bitmap_image &map, string fname)
{
    map.save_image("/Users/laria/Desktop/rpgmap/" + fname + ".bmp");
}

/* 
 verbs:
 
 specific actions:
 
 go

 open
 
 
 universal actions (external):
 shoot
 hit
 take
 
 universal actions (internal):
 reload
 throw
 drop
 eat
 
 
 
 
 */


void PopulateGrid(Grid &newgrid)
{
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 20; j++)
        {
            if(newgrid.Get(i, j) == true)
            {
                int r = arc4random_uniform(5);
                if(r == 0)
                {
                    newgrid.Add_Inv(*new Entity("ammo box"), i, j);
                    
                }
                else if(r == 1)
                {
                    newgrid.Add_Inv(*new Entity("health pack"), i, j);
                }
            }
        }

}

int main()
{
    

    bitmap_image map(1000,1000);

    Grid newgrid; 
    Room start(newgrid, map);
    
    saveImage(map, "rooms");

    
    Room * activeroom = &start;
    
    PopulateGrid(newgrid);
    
    
    Player player1("player1");
    
    int fin = 0;
    int x_coord;
    int y_coord;
    
    int AP = 5;
    
    string verb;
    string noun;
    string a;
    string b;
    
    while(fin == 0)
    {
        
        x_coord = activeroom->Get_xcoord();
        y_coord = activeroom->Get_ycoord();
        newgrid.Add_Inv(player1, x_coord, y_coord);
        
    describe_start:
        activeroom->Descrip();
        newgrid.Describe_inv(x_coord, y_coord);
        
        
    action_start:
        //cin >> verb >> noun;
        string s;
        getline(cin, s, '\n');
        verb = s.substr(1, s.find(' ')-1);
        int pos = s.find(')');
        noun = s.substr(verb.length() + 2, pos-verb.length()-2);

            
        
        if(verb == "exit")
            fin = 1;
        else if(verb == "go")
        {
            if(noun == "north")
            {
                if(activeroom->Check('n') == true)
                {
                    if(activeroom->Checkdoor('n') == true)
                    {
                        activeroom = activeroom->n_room;
                        newgrid.Remove("player1", x_coord, y_coord);
                    }
                    else
                    {
                        cout << "The door is closed!" << endl;
                        goto action_start;

                    }
                    
                }
                else
                {
                    cout << "You cannot go that way!" << endl;
                    goto action_start;

                }
            }
            else if(noun == "south")
            {
                if(activeroom->Check('s') == true)
                {
                    if(activeroom->Checkdoor('s') == true)
                    {
                        activeroom = activeroom->s_room;
                        newgrid.Remove("player1", x_coord, y_coord);
                    }
                    else
                    {
                        cout << "The door is closed!" << endl;
                        goto action_start;

                    }
                    
                }
                else
                {
                    cout << "You cannot go that way!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "east")
            {
                if(activeroom->Check('e') == true)
                {
                    if(activeroom->Checkdoor('e') == true)
                    {
                        activeroom = activeroom->e_room;
                        
                        newgrid.Remove("player1", x_coord, y_coord);
                    }
                    else
                    {
                        cout << "The door is closed!" << endl;
                        goto action_start;
                    }
                    
                }
                else
                {
                    cout << "You cannot go that way!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "west")
            {
                if(activeroom->Check('w') == true)
                {
                    if(activeroom->Checkdoor('w') == true)
                    {
                        activeroom = activeroom->w_room;
                        
                        newgrid.Remove("player1", x_coord, y_coord);
                    }
                    else
                    {
                        cout << "The door is closed!" << endl;
                        goto action_start;
                    }
                }
                else
                {
                    cout << "You cannot go that way!" << endl;
                    goto action_start;
                }
            }
            else
            {
                cout << "That is not a valid direction!" << endl;
                goto action_start;
            }
        }
        else if(verb == "open")
        {
            if(noun == "door")
            {
                cout << "Which door?" << endl;
            }
            if(noun == "north")
            {
                if(activeroom->Check('n') == true)
                {
                    if(activeroom->Checkdoor('n') == true)
                    {
                        cout << "That door is already open!" << endl;
                        goto action_start;
                    }
                    else
                        activeroom->Opendoor('n');
                    
                }
                else
                {
                    cout << "There is no north door!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "south")
            {
                if(activeroom->Check('s') == true)
                {
                    if(activeroom->Checkdoor('s') == true)
                    {
                        cout << "That door is already open!" << endl;
                        goto action_start;
                    }
                    else
                        activeroom->Opendoor('s');
                    
                }
                else
                {
                    cout << "There is no southh door!" << endl;
                    goto action_start;                }
                }
            else if(noun == "east")
            {
                if(activeroom->Check('e') == true)
                {
                    if(activeroom->Checkdoor('e') == true)
                    {
                        cout << "That door is already open!" << endl;
                        goto action_start;
                    }
                    else
                        activeroom->Opendoor('e');
                    
                }
                else
                {
                    cout << "There is no east door!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "west")
            {
                if(activeroom->Check('w') == true)
                {
                    if(activeroom->Checkdoor('w') == true)
                    {
                        cout << "That door is already open!" << endl;
                        goto action_start;
                    }
                    else
                        activeroom->Opendoor('w');
                }
                else
                {
                    cout << "There is no west door!" << endl;
                    goto action_start;
                }
            }
            else
            {
                cout << "You can not open that!" << endl;
                goto action_start;

            }
        }
        else if(verb == "take" || verb == "get")
        {
            if(newgrid.Search_Inv(noun, x_coord, y_coord) == true)
            {
                if(player1.Get_Inv_Size() < 4)
                {
                    player1.Add_Inv(newgrid.Get_Inv(noun, x_coord, y_coord));
                    newgrid.Remove(noun, x_coord, y_coord);
                    cout << "You have added a " << noun << " to your inventory." << endl;
                    goto action_start;
                }
                else
                {
                    cout << "You are carrying too many items!" << endl;
                    goto action_start;

                }
                
            }
            else
                cout << "There is no " << noun << " in the room." << endl;
        }
        else if(verb == "drop")
        {
            if(player1.Search_Inv(noun) == true)
            {
                player1.Remove(noun);
                newgrid.Add_Inv(*new Entity(noun), x_coord, y_coord);
                cout << "You have dropped a " << noun << "." << endl;
                goto action_start;
            }
            else
                cout << "You care not carrying a " << noun << "." << endl;
        }
        else if(verb == "list")
        {
            if(noun == "inventory")
            {
                player1.List_Inv();
                goto action_start;
            }
            else
            {
                cout << "command not understood" << endl;
            }
        }
        else if(verb == "look")
        {
            goto describe_start;
        }
        else if(verb == "show")
        {
            if(noun == "help")
            {
                cout << "Help" << endl;
                goto action_start;
            }
            else
            {
                cout << "Command not understood" << endl;
            }
        }
        else
        {
            cout << "Command not understood" << endl;
            goto action_start;
        }
        
        

    }
    
    
    return 0;
}

