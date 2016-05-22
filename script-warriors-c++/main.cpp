
#include <iostream>
#include "Grid.h"
#include "Room.h"
#include "bitmap_image.h"
#include <time.h>
#include "Entity.h"
#include "Player.h"
#include "Gun.h"
//#include "Friendly.h"

using namespace std;



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

void Turn(Player & player1, Grid & newgrid, int turn = -1)
{
    
    char player_type = player1.Get_type();
    
    int AP = 5;
    string verb, noun, s;
    cout << endl << endl << player1.Getname();
    switch (player_type)
    {
        case 's': cout << "(me)" << endl; break;
        case 'f': cout << "(friend)" << endl; break;
        case 'e': cout << "(enemy)" << endl; break;
        default: cout << "invalid playertype" << endl; break;
    }
    cout << "Turn " << turn << endl << endl;

    while(AP > 0)
    {
        player1.Set_x(player1.activeroom->Get_xcoord());
        player1.Set_y(player1.activeroom->Get_ycoord());
        if(newgrid.Search_Inv(player1.Getname(), player1.Get_x(), player1.Get_y()) == false)
            newgrid.Add_Inv(player1, player1.Get_x(), player1.Get_y());
        
    describe_start:
        if(player_type == 's')
        {
            player1.activeroom->Descrip();
            newgrid.Describe_inv(player1.Get_x(), player1.Get_y());
        }
        
        
    action_start:
        if(AP < 1)
            break;
        if(player_type == 's')
            cout << "Action points: " << AP << endl;
        
        getline(cin, s, '\n');
        verb = s.substr(1, s.find(' ')-1);
        int pos = s.find(')');
        noun = s.substr(verb.length() + 2, pos-verb.length()-2);
        
        if(verb == "go")
        {
            if(AP < 3)
            {
                if(player_type == 's')
                    cout << "You do not have enough Action Points for that task." << endl;
                goto action_start;
            }
            if(noun == "north")
            {
                if(player1.activeroom->Check('n') == true)
                {
                    if(player1.activeroom->Checkdoor('n') == true)
                    {
                        player1.activeroom = player1.activeroom->n_room;
                        newgrid.Remove(player1.Getname(), player1.Get_x(), player1.Get_y());
                        AP = AP - 3;
                        if(player_type == 'f')
                            cout << player1.Getname() << " has gone North." << endl;
                    }
                    else
                    {
                        if(player_type == 's')
                        {
                            cout << "The door is closed!" << endl;
                        }
                        goto action_start;
                        
                    }
                    
                }
                else
                {
                    if(player_type == 's')
                        cout << "You cannot go that way!" << endl;
                    goto action_start;
                    
                }
            }
            else if(noun == "south")
            {
                if(player1.activeroom->Check('s') == true)
                {
                    if(player1.activeroom->Checkdoor('s') == true)
                    {
                        player1.activeroom = player1.activeroom->s_room;
                        newgrid.Remove(player1.Getname(), player1.Get_x(), player1.Get_y());
                        AP = AP - 3;
                        if(player_type == 'f')
                            cout << player1.Getname() << " has gone South." << endl;
                        
                    }
                    else
                    {
                        if(player_type == 's')
                            cout << "The door is closed!" << endl;
                        goto action_start;
                        
                    }
                    
                }
                else
                {
                    if(player_type == 's')
                        cout << "You cannot go that way!" << endl;
                    AP = AP - 3;
                    
                    goto action_start;
                }
            }
            else if(noun == "east")
            {
                if(player1.activeroom->Check('e') == true)
                {
                    if(player1.activeroom->Checkdoor('e') == true)
                    {
                        player1.activeroom = player1.activeroom->e_room;
                        newgrid.Remove(player1.Getname(), player1.Get_x(), player1.Get_y());
                        AP = AP - 3;
                        if(player_type == 'f')
                            cout << player1.Getname() << " has gone East." << endl;
                        
                    }
                    else
                    {
                        if(player_type == 's')
                            cout << "The door is closed!" << endl;
                        goto action_start;
                    }
                    
                }
                else
                {
                    if(player_type == 's')
                        cout << "You cannot go that way!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "west")
            {
                if(player1.activeroom->Check('w') == true)
                {
                    if(player1.activeroom->Checkdoor('w') == true)
                    {
                        player1.activeroom = player1.activeroom->w_room;
                        
                        newgrid.Remove(player1.Getname(), player1.Get_x(), player1.Get_y());
                        AP = AP - 3;
                        if(player_type == 'f')
                            cout << player1.Getname() << " has gone West." << endl;
                        
                    }
                    else
                    {
                        if(player_type == 's')
                            cout << "The door is closed!" << endl;
                        goto action_start;
                    }
                }
                else
                {
                    if(player_type == 's')
                        cout << "You cannot go that way!" << endl;
                    goto action_start;
                }
            }
            else
            {
                if(player_type == 's')
                    cout << "That is not a valid direction!" << endl;
                goto action_start;
            }
        }
        else if(verb == "open")
        {
            if(AP < 2)
            {
                if(player_type == 's')
                    cout << "You do not have enough Action Points for that task." << endl;
                goto action_start;
                
            }
            if(noun == "door")
            {
                if(player_type == 's')
                    cout << "Which door?" << endl;
                goto action_start;
            }
            if(noun == "north")
            {
                if(player1.activeroom->Check('n') == true)
                {
                    if(player1.activeroom->Checkdoor('n') == true)
                    {
                        if(player_type == 's')
                            cout << "That door is already open!" << endl;
                        goto action_start;
                        
                        
                    }
                    else
                    {
                        player1.activeroom->Opendoor('n');
                        AP = AP - 2;
                        if(player_type == 's')
                            cout << "You have opened North door" << endl;
                        else if (player_type == 'f')
                            cout << player1.Getname() << " has opened North door." << endl;
                    }
                    
                }
                else
                {
                    if(player_type == 's')
                        cout << "There is no north door!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "south")
            {
                if(player1.activeroom->Check('s') == true)
                {
                    if(player1.activeroom->Checkdoor('s') == true)
                    {
                        if(player_type == 's')
                            cout << "That door is already open!" << endl;
                        goto action_start;
                    }
                    else
                    {
                        player1.activeroom->Opendoor('s');
                        AP = AP - 2;
                        if(player_type == 's')
                            cout << "You have opened South door" << endl;
                        else if (player_type == 'f')
                            cout << player1.Getname() << " has opened South door." << endl;

                    }
                    
                }
                else
                {
                    if(player_type == 's')
                        cout << "There is no south door!" << endl;
                    goto action_start;                }
            }
            else if(noun == "east")
            {
                if(player1.activeroom->Check('e') == true)
                {
                    if(player1.activeroom->Checkdoor('e') == true)
                    {
                        if(player_type == 's')
                            cout << "That door is already open!" << endl;
                        goto action_start;
                    }
                    else
                    {
                        player1.activeroom->Opendoor('e');
                        AP = AP - 2;
                        if(player_type == 's')
                            cout << "You have opened East door" << endl;
                        else if (player_type == 'f')
                            cout << player1.Getname() << " has opened East door." << endl;

                    }
                    
                }
                else
                {
                    if(player_type == 's')
                        cout << "There is no east door!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "west")
            {
                if(player1.activeroom->Check('w') == true)
                {
                    if(player1.activeroom->Checkdoor('w') == true)
                    {
                        if(player_type == 's')
                            cout << "That door is already open!" << endl;
                        goto action_start;
                    }
                    else
                    {
                        player1.activeroom->Opendoor('w');
                        AP = AP - 2;
                        if(player_type == 's')
                            cout << "You have opened West door" << endl;
                        else if (player_type == 'f')
                            cout << player1.Getname() << " has opened West door." << endl;

                    }
                }
                else
                {
                    if(player_type == 's')
                        cout << "There is no west door!" << endl;
                    goto action_start;
                }
            }
            else
            {
                if(player_type == 's')
                    cout << "You can not open that!" << endl;
                goto action_start;
                
            }
        }
        else if(verb == "close")
        {
            if(AP < 2)
            {
                if(player_type == 's')
                    cout << "You do not have enough Action Points for that task." << endl;
                goto action_start;
                
            }
            if(noun == "door")
            {
                if(player_type == 's')
                    cout << "Which door?" << endl;
                goto action_start;
            }
            if(noun == "north")
            {
                if(player1.activeroom->Check('n') == true)
                {
                    if(player1.activeroom->Checkdoor('n') == false)
                    {
                        if(player_type == 's')
                            cout << "That door is already closed!" << endl;
                        goto action_start;
                        
                        
                    }
                    else
                    {
                        player1.activeroom->Closedoor('n');
                        AP = AP - 2;
                        if(player_type == 's')
                            cout << "You have closed North door" << endl;
                        else if (player_type == 'f')
                            cout << player1.Getname() << " has closed North door." << endl;
                    }
                    
                }
                else
                {
                    if(player_type == 's')
                        cout << "There is no north door!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "south")
            {
                if(player1.activeroom->Check('s') == true)
                {
                    if(player1.activeroom->Checkdoor('s') == false)
                    {
                        if(player_type == 's')
                            cout << "That door is already closed!" << endl;
                        goto action_start;
                    }
                    else
                    {
                        player1.activeroom->Closedoor('s');
                        AP = AP - 2;
                        if(player_type == 's')
                            cout << "You have closed South door" << endl;
                        else if (player_type == 'f')
                            cout << player1.Getname() << " has closed South door." << endl;
                        
                    }
                    
                }
                else
                {
                    if(player_type == 's')
                        cout << "There is no south door!" << endl;
                    goto action_start;                }
            }
            else if(noun == "east")
            {
                if(player1.activeroom->Check('e') == true)
                {
                    if(player1.activeroom->Checkdoor('e') == false)
                    {
                        if(player_type == 's')
                            cout << "That door is already closed!" << endl;
                        goto action_start;
                    }
                    else
                    {
                        player1.activeroom->Closedoor('e');
                        AP = AP - 2;
                        if(player_type == 's')
                            cout << "You have closed East door" << endl;
                        else if (player_type == 'f')
                            cout << player1.Getname() << " has closed East door." << endl;
                        
                    }
                    
                }
                else
                {
                    if(player_type == 's')
                        cout << "There is no east door!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "west")
            {
                if(player1.activeroom->Check('w') == true)
                {
                    if(player1.activeroom->Checkdoor('w') == false)
                    {
                        if(player_type == 's')
                            cout << "That door is already closed!" << endl;
                        goto action_start;
                    }
                    else
                    {
                        player1.activeroom->Closedoor('w');
                        AP = AP - 2;
                        if(player_type == 's')
                            cout << "You have closed West door" << endl;
                        else if (player_type == 'f')
                            cout << player1.Getname() << " has closed West door." << endl;
                        
                    }
                }
                else
                {
                    if(player_type == 's')
                        cout << "There is no west door!" << endl;
                    goto action_start;
                }
            }
            else
            {
                if(player_type == 's')
                    cout << "You can not close that!" << endl;
                goto action_start;
                
            }
        }
        else if(verb == "take" || verb == "get")
        {
            if(AP < 2)
            {
                if(player_type == 's')
                    cout << "You do not have enough Action Points for that task." << endl;
                goto action_start;
                
            }
            if(newgrid.Search_Inv(noun, player1.Get_x(), player1.Get_y()) == true)
            {
                if(player1.Get_Inv_Size() < 4)
                {
                    if(newgrid.Get_Inv(noun, player1.Get_x(), player1.Get_y()).Get_type() == 'o')
                    {
                        player1.Add_Inv(newgrid.Get_Inv(noun, player1.Get_x(), player1.Get_y()));
                        newgrid.Remove(noun, player1.Get_x(), player1.Get_y());
                        if(player_type == 's')
                            cout << "You have added a " << noun << " to your inventory." << endl;
                        else if(player_type == 'f')
                            cout << player1.Getname() << " has added a " << noun << " to their inventory." << endl;
                        AP = AP - 2;
                        goto action_start;
                    }
                    else
                    {
                        if(player_type == 's')
                            cout<< "You can't pick THAT up!" << endl;
                        goto action_start;
                        
                    }
                }
                else
                {
                    if(player_type == 's')
                        cout << "You are carrying too many items!" << endl;
                    goto action_start;
                    
                }
                
            }
            else
                if(player_type == 's')
                    cout << "There is no " << noun << " in the room." << endl;
        }
        else if(verb == "drop")
        {
            if(player1.Search_Inv(noun) == true)
            {
                if(player1.Get_Inv(noun).Get_type() == 'o')
                {
                    player1.Remove(noun);
                    newgrid.Add_Inv(*new Entity(noun), player1.Get_x(), player1.Get_y());
                    if(player_type == 's')
                        cout << "You have dropped a " << noun << "." << endl;
                    if(player_type == 'f')
                        cout << player1.Getname() << " has have dropped a " << noun << "." << endl;
                    AP = AP - 1;
                    goto action_start;
                }
                else
                {
                    if(player_type == 's')
                        cout<< "You can't drop THAT!" << endl;
                    goto action_start;
                    
                }
                
            }
            else
            {
                if(player_type == 's')
                    cout << "You are not carrying a " << noun << "." << endl;
                goto action_start;
            }
        }
        else if(verb == "shoot") //3 AP
        {
            
        }
        else if(verb == "reload") //2 AP
        {
            
        }
        else if(verb == "use")
        {
            
        }
        else if(verb == "list")
        {
        
            if(player_type == 's')
            {
                if(noun == "inventory")
                {
                    player1.List_Inv();
                    goto action_start;
                }
                else
                {
                    cout << "command not understood" << endl;
                    goto action_start;
                    
                }
            }

            
        }
        else if(verb == "look") //north south east west
        {
            if(player_type == 's')
            {
            goto describe_start;
            }
        }
        else if(verb == "show")
        {
            if(player_type == 's')
            {
            if(noun == "help")
            {
                cout << endl;
                cout << "Commands:" << endl;
                cout << "(show help) - display this menu" << endl;
                cout << "(skip turn) - go on to next player's turn" << endl;
                cout << "(look around) - display description of current surroundings" << endl;
                cout << "(go [north/south/east/west]) - go to adjacent room (3 AP)" << endl;
                
                cout << "(open [north/south/east/west]) - open door (2 AP)" << endl;
                
                cout << "(take [item name]) - add item to inventory (2 AP)" << endl;
                
                cout << "(drop [item name]) - drop item from inventory (1 AP)" << endl;
                
                goto action_start;
            }
            else
            {
                cout << "Command not understood" << endl;
            }
            }
        }
        else if(verb == "skip")
        {
            if(noun == "turn")
            {
                break;
            }
            else
            {
                if(player_type == 's')
                {
                    cout << "Command not understood" << endl;
                }
            }
        }
        else
        {
            if(player_type == 's')
                cout << "Command not understood" << endl;
            goto action_start;
        }
        
    }
}

void Initialize(Player & player, Grid & newgrid, int playernum = -1, int mynum = -1, int playerteam = -1, int myteam = -1)
{
    if(playernum == mynum)
    {
        player.Set_type('s');
    }
    else
    {
        if(playerteam == myteam)
        {
            player.Set_type('f');
        }
        else
        {
            player.Set_type('e');

        }
    }
    newgrid.Add_Inv(player, 5, 5);

}

int main()
{
    

    bitmap_image map(1000,1000);

    Grid newgrid;
    Room start(newgrid, map);
    
    saveImage(map, "rooms");

    
    
    PopulateGrid(newgrid);
    
    
    Player player1(start, "player1");
    Player player2(start, "player2");
    Player player3(start, "player3");

  
    
    int player_num = 1; //from server
    int team_num = 1;

    
    Initialize(player1, newgrid, 1, player_num, 1, team_num);
    Initialize(player2, newgrid, 2, player_num, 1, team_num);
    Initialize(player3, newgrid, 3, player_num, 2, team_num);
    
    
    /*string verb;
    string noun;
    string a;
    string b;
    string s;*/

    
    /*for(turn; turn < 11; turn++)
    {
        while(AP > 0)
        {
            cout << "Turn " << turn << endl;
            
            x_coord = player1.activeroom->Get_xcoord();
            y_coord = player1.activeroom->Get_ycoord();
            newgrid.Add_Inv(player1, x_coord, y_coord);
            
        describe_start:
            player1.activeroom->Descrip();
            newgrid.Describe_inv(x_coord, y_coord);
            
            
        action_start:
            //cin >> verb >> noun;
            if(AP < 1)
                break;
            cout << "Action points: " << AP << endl;

            getline(cin, s, '\n');
            verb = s.substr(1, s.find(' ')-1);
            int pos = s.find(')');
            noun = s.substr(verb.length() + 2, pos-verb.length()-2);
                        
            if(verb == "go")
            {
                if(AP < 3)
                {
                    cout << "You do not have enough Action Points for that task." << endl;
                    goto action_start;
                }
                if(noun == "north")
                {
                    if(player1.activeroom->Check('n') == true)
                    {
                        if(player1.activeroom->Checkdoor('n') == true)
                        {
                            player1.activeroom = player1.activeroom->n_room;
                            newgrid.Remove("player1", x_coord, y_coord);
                            AP = AP - 3;
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
                    if(player1.activeroom->Check('s') == true)
                    {
                        if(player1.activeroom->Checkdoor('s') == true)
                        {
                            player1.activeroom = player1.activeroom->s_room;
                            newgrid.Remove("player1", x_coord, y_coord);
                            AP = AP - 3;

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
                        AP = AP - 3;

                        goto action_start;
                    }
                }
                else if(noun == "east")
                {
                    if(player1.activeroom->Check('e') == true)
                    {
                        if(player1.activeroom->Checkdoor('e') == true)
                        {
                            player1.activeroom = player1.activeroom->e_room;
                            newgrid.Remove("player1", x_coord, y_coord);
                            AP = AP - 3;

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
                    if(player1.activeroom->Check('w') == true)
                    {
                        if(player1.activeroom->Checkdoor('w') == true)
                        {
                            player1.activeroom = player1.activeroom->w_room;
                            
                            newgrid.Remove("player1", x_coord, y_coord);
                            AP = AP - 3;

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
                if(AP < 2)
                {
                    cout << "You do not have enough Action Points for that task." << endl;
                    goto action_start;

                }
                if(noun == "door")
                {
                    cout << "Which door?" << endl;
                }
                if(noun == "north")
                {
                    if(player1.activeroom->Check('n') == true)
                    {
                        if(player1.activeroom->Checkdoor('n') == true)
                        {
                            cout << "That door is already open!" << endl;
                            goto action_start;
                            

                        }
                        else
                        {
                            player1.activeroom->Opendoor('n');
                            AP = AP - 2;
                        }
                        
                    }
                    else
                    {
                        cout << "There is no north door!" << endl;
                        goto action_start;
                    }
                }
                else if(noun == "south")
                {
                    if(player1.activeroom->Check('s') == true)
                    {
                        if(player1.activeroom->Checkdoor('s') == true)
                        {
                            cout << "That door is already open!" << endl;
                            goto action_start;
                        }
                        else
                        {
                            player1.activeroom->Opendoor('s');
                            AP = AP - 2;
                        }
                    
                    }
                    else
                    {
                        cout << "There is no southh door!" << endl;
                        goto action_start;                }
                }
                else if(noun == "east")
                {
                    if(player1.activeroom->Check('e') == true)
                    {
                        if(player1.activeroom->Checkdoor('e') == true)
                        {
                            cout << "That door is already open!" << endl;
                            goto action_start;
                        }
                        else
                        {
                            player1.activeroom->Opendoor('e');
                            AP = AP - 2;
                        }
                        
                    }
                    else
                    {
                        cout << "There is no east door!" << endl;
                        goto action_start;
                    }
                }
                else if(noun == "west")
                {
                    if(player1.activeroom->Check('w') == true)
                    {
                        if(player1.activeroom->Checkdoor('w') == true)
                        {
                            cout << "That door is already open!" << endl;
                            goto action_start;
                        }
                        else
                        {
                            player1.activeroom->Opendoor('w');
                            AP = AP - 2;
                        }
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
                if(AP < 2)
                {
                    cout << "You do not have enough Action Points for that task." << endl;
                    goto action_start;

                }
                if(newgrid.Search_Inv(noun, x_coord, y_coord) == true)
                {
                    if(player1.Get_Inv_Size() < 4)
                    {
                        if(newgrid.Get_Inv(noun, x_coord, y_coord).Get_type() == 'o')
                        {
                            player1.Add_Inv(newgrid.Get_Inv(noun, x_coord, y_coord));
                            newgrid.Remove(noun, x_coord, y_coord);
                            cout << "You have added a " << noun << " to your inventory." << endl;
                            AP = AP - 2;
                            goto action_start;
                        }
                        else
                        {
                            cout<< "You can't pick THAT up!" << endl;
                            goto action_start;

                        }
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
                    if(player1.Get_Inv(noun).Get_type() == 'o')
                    {
                        player1.Remove(noun);
                        newgrid.Add_Inv(*new Entity(noun), x_coord, y_coord);
                        cout << "You have dropped a " << noun << "." << endl;
                        AP = AP - 1;
                        goto action_start;
                    }
                    else
                    {
                        cout<< "You can't drop THAT!" << endl;
                        goto action_start;

                    }
                    
                }
                else
                {
                    cout << "You are not carrying a " << noun << "." << endl;
                    goto action_start;
                }
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
                    goto action_start;

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
                    cout << endl;
                    cout << "Commands:" << endl;
                    cout << "(show help) - display this menu" << endl;
                    cout << "(skip turn) - go on to next player's turn" << endl;
                    cout << "(look around) - display description of current surroundings" << endl;
                    cout << "(go [north/south/east/west]) - go to adjacent room (3 AP)" << endl;

                    cout << "(open [north/south/east/west]) - open door (2 AP)" << endl;

                    cout << "(take [item name]) - add item to inventory (2 AP)" << endl;

                    cout << "(drop [item name]) - drop item from inventory (1 AP)" << endl;

                    goto action_start;
                }
                else
                {
                    cout << "Command not understood" << endl;
                }
            }
            else if(verb == "skip")
            {
                if(noun == "turn")
                {
                    break;
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
        AP = 5;

        //FriendTurn(friendly1, newgrid);
        
        

    
    
    }*/
    
    
    for(int i = 1; i < 11; i++)
    {
        Turn(player1, newgrid, i);
        Turn(player2, newgrid, i);
        Turn(player3, newgrid, i);
    }
    
    return 0;
}

