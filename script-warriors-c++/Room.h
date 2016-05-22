//
//  Room.h
//  rpg
//
//  Created by Laria R on 5/21/16.
//  Copyright (c) 2016 Laria R. All rights reserved.
//

//origin chars:
//n = north, s = south, e = east, w = west, f = first.
//door
// 0 = door closed, 1 = door open

#ifndef rpg_Room_h
#define rpg_Room_h
#include "Grid.h"
#include "bitmap_image.h"
#include <time.h>

using namespace std;

class Room
{
private:
    int x_pos;
    int y_pos;
    bool n;
    bool e;
    bool s;
    bool w;
    
public:
    Room(Grid &map, bitmap_image &img, Room * lastroom = NULL, int x = 5, int y = 5, bool doorpos = 0, char origin = 'f')
    {

        x_pos = x;
        y_pos = y;
        if (x > 10 || x < 0 || y >10 || y < 0)
        {
            return;
        }
        n = false;
        e = false;
        s = false;
        w = false;
        map.Set(x, y);
        switch(origin) //connecting pointer back to previous room; setting door position
        {
            case 'f':
                break;
            case 'n':
                s_room = lastroom;
                s = true;
                sdoor = doorpos;
                break;
            case 's':
                n_room = lastroom;
                n = true;

                ndoor = doorpos;
                break;
            case 'e':
                w_room = lastroom;
                w = true;

                wdoor = doorpos;
                break;
            case 'w':
                e_room = lastroom;
                e = true;

                edoor = doorpos;
                break;
            default:
                cout << "invalid origin" << endl;
                break;
        }

        GenerateRooms(map, img);
        DrawRoom(img);


    }
    bool ndoor;
    bool edoor;
    bool sdoor;
    bool wdoor;
    Room * n_room;
    Room * e_room;
    Room * s_room;
    Room * w_room;
    void DrawRoom(bitmap_image &img)
    {
        int x = x_pos*70;
        int y = y_pos*70;
        if(s)
            drawLineSegment(x, y, x + 70, y, img, 200, 100, 100);
        else
            drawLineSegment(x, y, x + 70, y, img, 255, 255, 255);
        
        if(w)
            drawLineSegment(x, y, x, y + 70, img, 200, 100, 100);
        else
            drawLineSegment(x, y, x, y + 70, img, 255, 255, 255);
        
        if(e)
            drawLineSegment(x+70, y, x+70, y+70, img, 200, 100, 100);
        else
            drawLineSegment(x+70, y, x+70, y+70, img, 255, 255, 255);
        
        if(n)
            drawLineSegment(x, y+70, x+70, y+70, img, 200, 100, 100);
        else
            drawLineSegment(x, y+70, x+70, y+70, img, 200, 255, 255);
    }
    
    void drawLineSegment(int p1x, int p1y, int p2x, int p2y, bitmap_image &img, int r, int g, int b)
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
            img.set_pixel(p1x + i*x_comp + 50, (-1*(p1y + i*y_comp)+950), r, g, b);
        }
        
    }
    void GenerateRooms(Grid &map, bitmap_image &img)
    {
        if(map.GetNum() > 30)
        {
            cout << "room limit reached" << endl;
            return;
        }
        if(map.Get(x_pos, y_pos + 1) == false && y_pos < 12 && y_pos > 2) //checking north square
        {
            int r = arc4random_uniform(7);

            if(r < 3)
            {
                n = true;
                int door = rand()% 2;
                ndoor = door;
                n_room = new Room(map, img, this, x_pos, y_pos+1, door, 'n');
            }
        }
        if(map.Get(x_pos, y_pos - 1) == false && y_pos < 12 && y_pos > 2) //checking south square
        {
            int r = arc4random_uniform(7);

            if(r < 3)
            {

                s = true;
                int door = rand()% 2;
                sdoor = door;
                s_room = new Room(map,img, this, x_pos, y_pos-1, door, 's');
            }
        }
        if(map.Get(x_pos + 1, y_pos) == false && x_pos < 10 && x_pos > 2) //checking east square
        {
            int r = arc4random_uniform(7);

            if(r < 3)
            {

                e = true;
                int door = rand()% 2;
                edoor = door;
                e_room = new Room(map, img, this, x_pos + 1, y_pos, door, 'e');

            }
        }
        if(map.Get(x_pos - 1, y_pos) == false && x_pos < 10 && x_pos > 2) //checking west square
        {
            int r = arc4random_uniform(7);

            if(r < 3)
            {

                w = true;
                int door = rand()% 2;
                wdoor = door;
                w_room = new Room(map, img, this, x_pos - 1, y_pos, door, 'w');

            }
        }
    }
    void Descrip()
    {
        //cout << "You are in room " << x_pos << ", " << y_pos << endl;
        if(n == 1)
        {
            cout << "There is a room to the north. ";
            if(ndoor == 1)
                cout << "The door is open." << endl;
            else
                cout << "The door is closed." << endl;
        }
        if(s == 1)
        {
            cout << "There is a room to the south. ";
            if(sdoor == 1)
                cout << "The door is open." << endl;
            else
                cout << "The door is closed." << endl;
        }
        
        if(e == 1)
        {
            cout << "There is a room to the east. ";
            if(edoor == 1)
                cout << "The door is open." << endl;
            else
                cout << "The door is closed." << endl;
        }
        if(w == 1)
        {
            cout << "There is a room to the west. ";
            if(wdoor == 1)
                cout << "The door is open." << endl;
            else
                cout << "The door is closed." << endl;
        }
        
    }
    
    bool Check(char direction)
    {
        switch(direction)
        {
        case 'n': return n; break;
        case 's': return s; break;
        case 'e': return e; break;
        case 'w': return w; break;
            default: cout << "invalid direction" << endl; return false; break;
        }
    }
    bool Checkdoor(char direction)
    {
        switch(direction)
        {
            case 'n': return ndoor; break;
            case 's': return sdoor; break;
            case 'e': return edoor; break;
            case 'w': return wdoor; break;
            default: cout << "invalid direction" << endl; return false; break;
        }
    }
    void Opendoor(char direction)
    {
        switch(direction)
        {
            case 'n': ndoor = true; (n_room)->sdoor = true; break;
            case 's': sdoor = true; (s_room)->ndoor = true; break;
            case 'e': edoor = true; (e_room)->wdoor = true; break;
            case 'w': wdoor = true; (w_room)->edoor = true; break;
            default: cout << "invalid direction" << endl; break;
        }

    }
    int Get_xcoord()
    {
        return x_pos;
    }
    int Get_ycoord()
    {
        return y_pos;
    }





};

#endif
