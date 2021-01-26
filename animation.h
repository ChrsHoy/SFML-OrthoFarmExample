#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "primer.h"


class Draw : public Primer {

public:

    Draw();

    //Functions
    void player(sf::RenderWindow &window);
	void map(int layer, sf::RenderWindow &window);
    void initialize(void);
    void blitter(int i, int j, int x,int y, int tile_size, sf::RenderWindow &window);
    void tillage( sf::RenderWindow &window);
    void plant( sf::RenderWindow &window);
protected:

    //map data values

    static int mapX,mapY;
    static int xSource,ySource;
    static int x,y;
    static int dirX,dirY;
    static int state;
    static int direction;
    static int width,height;
    int maxframe, frame, iframes, aframes;
    int deltatime;
    int deathtimer;
	static bool isTilling;
    bool isRunning;
    bool animCheck;

    
private:
    //map data values

    int mframes;
    bool tileSet;
    int blitX1,blitX2,blitY1,blitY2; 
    int testscroll;
        
    //Map
    sf::Texture tileSet1Texture;
	sf::Sprite tileSet1;
	sf::Texture tileSet1BTexture;
	sf::Sprite tileSet1B;
    
	//HUD
	sf::Texture HUDTexture;
	sf::Sprite HUD;
	sf::Texture HUDHeartsTexture;
	sf::Sprite HUDHearts;
	sf::Texture HUDMagicTexture;
	sf::Sprite HUDMagic;
	float HUDtimer;
	int HUDDirection;

    //Player
	sf::Texture heroTexture;
	sf::Sprite hero;

};

#endif
