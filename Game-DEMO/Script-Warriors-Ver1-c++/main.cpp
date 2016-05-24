
#include <iostream>
#include "Grid.h"
#include "Room.h"
#include "bitmap_image.h"
#include <time.h>
#include "Entity.h"
#include "Player.h"
#include "Gun.h"
#include "Playerslist.h"
#include <sys/socket.h>
#include <fstream>

using namespace std;



void saveImage(bitmap_image &map, string fname)
{
    map.save_image("/Users/laria/Desktop/rpgmap/" + fname + ".bmp");
}



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
                    newgrid.Add_Inv(*new Entity("ammobox"), i, j);
                    
                }
                else if(r == 1)
                {
                    newgrid.Add_Inv(*new Entity("healthpack"), i, j);
                }
            }
        }

}

bool Shoot_Inroom()
{
    int r = arc4random_uniform(100);
    if(r < 80)
    {
        return true;
    }
    else
        return false;
}

bool Shoot_Nextroom()
{
    int r = arc4random_uniform(100);
    if(r < 40)
    {
        return true;
    }
    else
        return false;
}


void Turn(Player & player1, Grid & newgrid, Playerslist & list, ofstream &fout, int turn = -1)
{
    if(player1.alive == false)
    {
        cout << player1.Getname() << " is dead." << endl;
        return;
    }
    
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

    
    
    /*if (player_type == 'f')
    {
        string Result;
        
        stringstream convert; 
        
        convert << turn;
        
        Result = convert.str()
        fout.open("/Users/laria/Documents/c++/rpg/rpg/f" + char(turn) + ".txt");
    }*/
    
    while(AP > 0)
    {
        player1.Set_x(player1.activeroom->Get_xcoord());
        player1.Set_y(player1.activeroom->Get_ycoord());
        if(newgrid.Search_Inv(player1.Getname(), player1.Get_x(), player1.Get_y()) == false)
        {
            newgrid.Add_Inv(player1, player1.Get_x(), player1.Get_y());
        }
        
    describe_start:
        cout << endl;
        if(player_type == 's')
        {
            player1.activeroom->Descrip();
            newgrid.Describe_inv(player1.Get_x(), player1.Get_y());
        }
        
        
    action_start:
        //cout << list.Get("player3").alive;

        if(AP < 1)
            break;
        if(player_type == 's')
            cout << "Action points: " << AP << endl;
        
        
        /*if(player_type == 's')
        {
            getline(cin, s, '\n');
            fout.open("/Users/laria/Documents/c++/rpg/rpg/output.txt");
            
            fout << s;
            fout.close();
            
            fstream fin;
            fin.open("/Users/laria/Documents/c++/rpg/rpg/output.txt");
            fin>>verb>>noun;
            
            
            fin.close();
        }*/
        
        
        getline(cin, s, '\n');
        fout.open("/Users/laria/Documents/c++/rpg/rpg/output.txt");
        
        fout << s;
        fout.close();
        
        fstream fin;
        fin.open("/Users/laria/Documents/c++/rpg/rpg/output.txt");
        fin>>verb>>noun;
        
        
        fin.close();
        
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
                        {
                            cout << "You have opened North door" << endl;
                            goto action_start;

                        }
                        
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
                        {
                            cout << "You have opened South door" << endl;
                            goto action_start;
                            
                        }
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
                        {
                            cout << "You have opened East door" << endl;
                            goto action_start;
                            
                        }
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
                        {
                            cout << "You have opened West door" << endl;
                            goto action_start;
                            
                        }
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
                        cout << player1.Getname() << " has dropped a " << noun << "." << endl;
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
            if(newgrid.Search_Inv(noun, player1.Get_x(), player1.Get_y()) == true)
            {
                if(player1.Search_Inv("handgun") == true)
                {
                    if(player1.ammo > 0)
                    {
                        
                        if(newgrid.Get_Inv(noun, player1.Get_x(), player1.Get_y()).Get_type() == 'o')
                        {
                            (player1.ammo)--;
                            AP = AP - 3;
                            if(Shoot_Inroom())
                            {
                                if(player_type == 's')
                                {
                                    cout << "You shoot the " << noun << ". Gee, calm down." << endl;
                                    goto action_start;

                                }
                                else if (player_type == 'f')
                                    cout << player1.Getname() << " shoots a " << noun <<"." << endl;
                            }
                            else
                            {
                                if(player_type == 's')
                                {
                                    cout << "You shoot at the " << noun << " and miss." << endl;
                                    goto action_start;

                                }
                                else if (player_type == 'f')
                                    cout << player1.Getname() << " shoots at a " << noun <<" and misses." << endl;
                            }
                        }
                        else if(newgrid.Get_Inv(noun, player1.Get_x(), player1.Get_y()).Get_type() == 'f')
                        {
                            if(player_type == 's')
                            {
                                cout << "You can't shoot at your friend!" << endl;
                                goto action_start;

                            }
                        }
                        else if(newgrid.Get_Inv(noun, player1.Get_x(), player1.Get_y()).Get_type() == 's')
                        {
                            if(player_type == 's')
                            {
                                cout << "You can't shoot yourself." << endl;
                                cout << "1 (800) 273-8255" << endl;
                                goto action_start;
                                
                            }
                        }
                        else if(newgrid.Get_Inv(noun, player1.Get_x(), player1.Get_y()).Get_type() == 'e')
                        {
                            (player1.ammo)--;
                            AP = AP - 3;
                            if(Shoot_Inroom())
                            {
                                if(player_type == 's')
                                {
                                    cout << "You shoot " << noun << " and hit." << endl;
                                    list.Get(noun).kill();
                                    newgrid.Remove(noun, player1.Get_x(), player1.Get_y());
                                    //cout << list.Get("player3").alive;
                                    //cout << newgrid.Get_Inv(noun, player1.Get_x(), player1.Get_y()).HP << endl;
                                    goto action_start;
                                    
                                }
                                else if (player_type == 'f')
                                {
                                    cout << player1.Getname() << " shoots " << noun <<" and hits." << endl;
                                    newgrid.Get_Inv(noun, player1.Get_x(), player1.Get_y()).kill();
                                    newgrid.Remove(noun, player1.Get_x(), player1.Get_y());
                                }
                            }
                            else
                            {
                                if(player_type == 's')
                                {
                                    cout << "You shoot at " << noun << " and miss." << endl;
                                    goto action_start;
                                    
                                }
                                else if (player_type == 'f')
                                    cout << player1.Getname() << " shoots at " << noun <<" and misses." << endl;
                            }

                        }
                    }
                    else
                    {
                        if(player_type == 's')
                        {
                            cout << "You do not have ammo!" << endl;
                        }
                        goto action_start;
                    }
                    
                    
                }
                else
                {
                    if(player_type == 's')
                    {
                        cout << "You do not have a gun!" << endl;
                    }
                    goto action_start;

                }
            }
            else
            {
                if(player_type == 's')
                {
                    cout << "Target is not in sight!" << endl;
                }
                goto action_start;

            }
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
        else if(verb == "look") 
        {
            if (noun == "around")
            {
                if(player_type == 's')
                {
                    goto describe_start;
                }
            }
            if(noun == "north")
            {
                if(player1.activeroom->Check('n') == true)
                {
                    if(player1.activeroom->Checkdoor('n') == true)
                    {
                        cout << "North room: " << endl;
                        newgrid.Describe_inv(player1.Get_x(), player1.Get_y() + 1);
                        goto action_start;

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
                        cout << "There is nothing there!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "south")
            {
                if(player1.activeroom->Check('s') == true)
                {
                    if(player1.activeroom->Checkdoor('s') == true)
                    {
                        cout << "South room: " << endl;
                        newgrid.Describe_inv(player1.Get_x(), player1.Get_y() - 1);
                        goto action_start;

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
                        cout << "There is nothing there!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "east")
            {
                if(player1.activeroom->Check('e') == true)
                {
                    if(player1.activeroom->Checkdoor('e') == true)
                    {
                        cout << "East room: " << endl;
                        newgrid.Describe_inv(player1.Get_x() + 1, player1.Get_y());
                        goto action_start;

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
                        cout << "There is nothing there!" << endl;
                    goto action_start;
                }
            }
            else if(noun == "west")
            {
                if(player1.activeroom->Check('w') == true)
                {
                    if(player1.activeroom->Checkdoor('w') == true)
                    {
                        cout << "West room: " << endl;
                        newgrid.Describe_inv(player1.Get_x() -1, player1.Get_y());
                        goto action_start;

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
                        cout << "There is nothing there!" << endl;
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
        else if(verb == "show") 
        {
            if(player_type == 's' || player_type == 'e')
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
            else if(noun == "stats")
            {
                cout << "HP: " << player1.HP << endl;
                cout << "Ammo: " << player1.ammo << endl;
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
    player.Add_Inv(*new Gun("handgun"));
    newgrid.Add_Inv(player, 5, 5);

}

int main()
{
    

    ofstream fout;
    ifstream fin;
   
  
    bitmap_image map(1000,1000);

    Grid newgrid;
    Room start(newgrid, map);
    
    saveImage(map, "rooms");

    
    
    PopulateGrid(newgrid);
    
    
    Player player1(start, "player1");
    Player player2(start, "player2");
    Player player3(start, "player3");

  
    
    int player_num = 1; //user inputted
    int team_num = 1;

    
    
    Initialize(player1, newgrid, 1, player_num, 1, team_num);
    Initialize(player2, newgrid, 2, player_num, 1, team_num);
    Initialize(player3, newgrid, 3, player_num, 2, team_num);
    
    Playerslist plist;
    plist.add(player1);
    plist.add(player2);
    plist.add(player3);
        
    
    for(int i = 1; i < 11; i++)
    {
        Turn(player1, newgrid, plist, fout, i);
        Turn(player2, newgrid, plist, fout, i);
        Turn(player3, newgrid, plist, fout, i);
    }
    
    return 0;
}

