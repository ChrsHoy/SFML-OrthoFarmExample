#pragma once

#ifndef MONEMENT_H
#define MOVEMENT_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "animation.h"

//#include "primer.h"

class Input;
class Primer;

class Geom : public Draw
{

public:

	//Structures
struct COORD{int x,y;};

//struct POINT{int a,b;};
struct POINT{int x,y;};
    Geom();

    //Functions
    void centerScrolling();
    void mapCollision(Primer &primer);
    void update(Input &input,Primer &primer);
    POINT detectWarpSpe(int number);
    void reinitialize();
	void detectTilesSpecials(int mapY, int mapX);
    void tillage(Draw &draw,Primer &primer, sf::RenderWindow &window);
    void plant(Draw &draw,Primer &primer, sf::RenderWindow &window);
    
protected:


    int xLength,yLength;


    //Action Toggle

    int numberSPE;

    const int LIMIT_X = 400;
    const int LIMIT_Y = 220;
    const int LIMIT_W = 100;
    const int LIMIT_H = 80;
    
    // Enum for buttons
    //remove const
    enum { up, down, right, left, attack, run, enter, spell, work };

    // Max number of levels
    const int LEVEL_MAX = 2;

    // An enum to manage the menu.
    enum { START, PAUSE };

    // Max shurikens on screen
    const int MAGIC_MAX = 6;


    /*************************/
        /**VALUES TILES /
        / ************************/

    const int WALL = 1;
    const int SPE1 = 10;
    const int SPE2 = 11;
    const int SPE3 = 12;
    const int SPE4 = 13;
    const int SPE5 = 14;
    const int SPE6 = 15;
    const int SPE7 = 16;
    const int SPE8 = 17;
    const int SPE9 = 18;
    const int SPE10 = 19;
    
private:
	int posX,posY;
	const int  tileRowMax = 400;
	const int  tileColMax = 150;
	int centralX,centralY;
    
	//int dirX,dirY;
	//action checks
	bool check;
	bool checkAction;
	bool tillable;
	//int numberSPE;
	int warpDirection;
	int warp_coming_from_x;
	int warp_coming_from_y;



    
    
    
    

};
#endif
