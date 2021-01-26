#pragma once

#ifndef PRIMER_H
#define PRIMER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Primer
{
    //static int xBound,yBound;
public:
    Primer();
    
    
	//Structures

    struct NPC { int type, text, quest; };
	struct CHEST { int type; };
	struct WARPSPE { int value; };
	struct KEYON { int type; };
	struct TRAP { int type; };
    
    
    static int xBound,yBound;
    static int startX,startY;
    
	//struct POINT { int x, y; };
    
    const int  SCREEN_WIDTH = 800;
    const int  SCREEN_HEIGHT = 480;
    

    //std::string* sPtr;

    bool getCheck(void) const;
    bool getLevelCheck(void) const;
    bool getSaveCheck(void) const;
    bool getHealthCheck(void) const;

    // mutators
    void setLevel(int value);
    void setCheck(bool value);
    void setLevelCheck(bool value);
    void setSaveCheck(bool value) ;
    void setHealthCheck(bool value);
    int getWarpSP(int number) const;
    int getWarpS(int number) const;
    
    //Functions
    void draw(int layer,sf::RenderWindow &window);
    void LoadMap(std::string filename,std::string sFile);
	void changeLevel(void);
    void testScroll(void);
    
protected:

    //int startX,startY;
    //int xBound,yBound;
    //static int xBound,yBound;
    bool tileSet;
    int tileSetGroup;
        bool checkLevel;

    //int startX,startY;
    std::string* sPtr;
    static int level;
    static int layer;
    static int tiles[80][80];
    static int sub1[80][80];
    static int sub2[80][80];
    static int sub3[80][80];
    
    static int tileState[320][80];
    static int extraState[119];
    static int extraState2[3];
    
    /*
    bool check;
    bool checkLevel;
    static bool checkSave;
    static bool checkHealth;
    bool checkLoad[10];
    */
    static int WarpUP, WarpDown, WarpLeft, WarpRight,WarpSP;
    
    int deltaCycle;
    

    // variables for A-RPG
    //int WarpUP, warpDown, warpLeft, warpRight;
    WARPSPE warpSP[10];
    NPC NPC[20];
    CHEST chest[20];
    int loot, weather;
    int cinematics, cinematics_condition;
    int musicNumber;
    KEYON keyon[10];
    TRAP trap[10];
    
    



	const int  tileSize = 32;
	const int  deltaframes = 20;
    
    const int pframes = 3;
    const float swordframes = 1;

    /*Size of the sprite of our hero(width = width and height = heigth) */
    const int PLAYER_WIDTH = 40;
    const int PLAYER_HEIGTH = 48;

    // travel speed in pixels of the sprite
    const int pspeed = 3;

    // values ​​assigned to states / directions partitions
    const int IDLE = 0;
    const int WALK = 1;

    const int DEAD = 4;

    const int DOWN = 0;
    const int UP = 1;
    const int RIGHT = 2;
    const int LEFT = 3;
    //std::string* sPtr;
    

private:
    
    bool check;

    static bool checkSave;
    static bool checkHealth;
    bool checkLoad[10];
    int warps[10];
    const int  MAX_MAP_X = 80;
	const int  MAX_MAP_Y = 80;
    //int xBound,yBound;
    std::string sFile;
    std::string filename;
    //int level;
    //int testscroll;
    
};

#endif
