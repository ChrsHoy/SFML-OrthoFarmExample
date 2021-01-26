#include "animation.h"


using namespace std;
using namespace sf;

int Draw::y=0;
int Draw::x=0;
int Draw::mapX=0;
int Draw::mapY=0;
int Draw::dirY=0;
int Draw::dirX=0;
int Draw::width=0;
int Draw::height=0;
int Draw::state=0;
int Draw::direction=0;
int Draw::xSource=0;
int Draw::ySource=0;
bool Draw::isTilling=false;


Draw::Draw()
{
    // Initialize the variables:
    if (!tileSet1Texture.loadFromFile("graphics/tileset1.png"))
    {cout << "Error loading the tileset image 1." << endl;    }
    else
        tileSet1.setTexture(tileSet1Texture);

    if (!tileSet1BTexture.loadFromFile("graphics/tileset1b.png"))
    {cout << "Error loading the tileset image 1b." << endl;    }
    else
        tileSet1B.setTexture(tileSet1BTexture);

    // Load the spritesheet hero
    if (!heroTexture.loadFromFile("graphics/hero.png"))
    {cout << "Error loading spritesheet the hero." << endl;    }
    else
        hero.setTexture(heroTexture);

    xSource=ySource = 0;
    state = direction = 0;

    width=height=0;
    dirX = dirY = 0;
    deathtimer = 0;

    mframes = deltaframes * 3;
    frame = deltatime=maxframe=iframes = 0;
    mapX=mapY=blitX1=blitX2=blitY1=blitY2=0;
    
    // Other variables

    HUDtimer = 3;
    HUDDirection = DOWN;

    deltaCycle=0;
    tileSet=false;

}


void Draw::initialize()
{
    iframes = 0;

    // Shows status and direction 
    direction = RIGHT;
    state = IDLE;

    // Indicates the frame number where to start
    frame = 0;
    deltatime=pframes;

    maxframe = 8;

    // Starts at the beginning of the map
    x = startX;
    y = startY;

    // We initialize the camera
	// It refocuses the camera
	xSource = startX-(SCREEN_WIDTH / 2);
    ySource = startY-(SCREEN_WIDTH / 2);
    
    //Height and width of our hero 
    width = PLAYER_WIDTH;
    height = PLAYER_HEIGTH;

    // Variables necessary for the operation of the management of collisions
    deathtimer=0;
isTilling=false;
}


void Draw::map(int layer, RenderWindow &window)
{
    int i,j,tile,xIndex,yIndex;

    mapX = xSource / tileSize;
	blitX1 = (xSource % tileSize) * -1;
	blitX2 = blitX1 + SCREEN_WIDTH + (blitX1 == 0 ? 0 : tileSize);

	mapY = ySource / tileSize;
	blitY1 = (ySource % tileSize) * -1;
	blitY2 = blitY1 + SCREEN_HEIGHT + (blitY1 == 0 ? 0 : tileSize);

    if(mframes!=0)
        mframes--;
    else{mframes=deltaframes*3;tileSet=!tileSet;}



	if (layer == 1)
	{
		for (j = blitY1; j < blitY2; j += tileSize)
		{
			mapX = xSource / tileSize;

			for (i = blitX1; i < blitX2; i+= tileSize)
			{
				tile = tiles[mapY][mapX];

				yIndex= tile / 10 * tileSize;
				xIndex = tile % 10 * tileSize;

                blitter(i,j,xIndex,yIndex,tileSize,window);
				mapX++;
			}

			mapY++;
		}
	}

	else if (layer == 2)
	{		
        for (j = blitY1; j < blitY2; j+= tileSize)
		{
			mapX = xSource / tileSize;

			for (i = blitX1; i < blitX2; i+= tileSize)
			{
				plant(window);
				tillage(window);
				tile = sub1[mapY][mapX];

				yIndex = tile / 10 * tileSize;
				xIndex = tile % 10 * tileSize;

                blitter(i,j,xIndex,yIndex,tileSize,window);
				mapX++;
			}

			mapY++;
		}
	}
	else if (layer == 3)
	{
		for (j = blitY1; j < blitY2; j+= tileSize)
		{
			mapX = xSource / tileSize;

			for (i = blitX1; i < blitX2; i+= tileSize)
			{


				tile = sub2[mapY][mapX];

				yIndex = tile / 10 * tileSize;
				xIndex = tile % 10 * tileSize;
                
                blitter(i,j,xIndex,yIndex,tileSize,window);
				mapX++;
			}

			mapY++;
		}
	}

}

void Draw::player(RenderWindow &window)
{
	if (deltatime<= 0)
	{
		deltatime= pframes;
		frame++;

		if (frame >= maxframe)
			frame = 0;
	}

	else
	{
		if (state != IDLE)
			deltatime -= (1 + (isRunning * 2));
		else
			deltatime--;
	}

	hero.setPosition(Vector2f(x - xSource, y - ySource));


	if (iframes > 0)
	{
		if (frame % 2 == 0)
		{
			if (direction == LEFT)
			{
				hero.setTextureRect(sf::IntRect(frame * width,(state * 3 * height + (direction - 1) * 					height ),width, height));
				window.draw(hero);
			}
			else
			{
				hero.setTextureRect(sf::IntRect((frame + 1) * width,
					(state * 3 * height + direction * height  ),
					-width, height));
				window.draw(hero);
			}
		}

	}

	else
	{
		if (direction == LEFT)
		{
			hero.setTextureRect(sf::IntRect(frame * width,(state * 3 * height + (direction - 1) * height ),width, height));
			window.draw(hero);
		}
		else
		{
			hero.setTextureRect(sf::IntRect((frame + 1) * width,
				(state * 3 * height + direction * height ),
				-width, height));
			window.draw(hero);
		}
	}

    
}

void Draw::blitter(int i, int j, int x, int y, int tile_size,RenderWindow &window)
{
        if (tileSet == 0)
    {
        tileSet1.setPosition(Vector2f(i, j));
        tileSet1.setTextureRect(sf::IntRect(x, y, tile_size, tile_size));
        window.draw(tileSet1);
    }
    else
    {
        tileSet1B.setPosition(Vector2f(i, j));
        tileSet1B.setTextureRect(sf::IntRect(x, y, tile_size, tile_size));
        window.draw(tileSet1B);
    }
    
    
}


void Draw::tillage(RenderWindow &window)
{

	int posX, posY, row, coll, check;

	check=isTilling;


	if (check && checkLevel== true)
	{

		switch (direction)
		{
		case 0:
			posX = (x+20) / tileSize;
			posY = (y+24+tileSize) / tileSize;
			sub1[posY][posX] = 29;
            tileState[posY+80][posX]=sub1[posY][posX];
			break;
            
		case 1:
			posX = (x + 20) / tileSize;
			posY = (y ) / tileSize;
            sub1[posY][posX] = 29;
            tileState[posY+80][posX]=sub1[posY][posX];
            break;
            
		case 2:
			posX = (x + 20+tileSize) / tileSize;
			posY = (y + 48) / tileSize;
            sub1[posY][posX] = 29;
            tileState[posY+80][posX]=sub1[posY][posX];
            break;
            
		case 3:
			posX = (x  ) / tileSize;
			posY = (y +48) / tileSize;
			sub1[posY][posX] = 29;
            tileState[posY+80][posX]=sub1[posY][posX];
			break;
            
		}


		row = 2*tileSize;
		coll = 9*tileSize;

        blitter(posX,posY,coll,row,tileSize,window);
        
		isTilling = false;
        
	}

}


void Draw::plant(RenderWindow &window)
{

	int posX, posY,check;

	check=isTilling;

	switch (direction)
	{
	case 0:
		posX = (x + 20) / tileSize;
		posY = (y + 24 + tileSize) / tileSize;
		break;

	case 1:
		posX = (x + 20) / tileSize;
		posY = y / tileSize;
		break;

	case 2:
		posX = (x + 20 + tileSize) / tileSize;
		posY = (y + 48) / tileSize;
		break;

	case 3:
		posX = x / tileSize;
		posY = (y + 48) / tileSize;
		break;
	}
	
	if (check == true && sub1[posY][posX] == 29) 
	{
		tiles[posY][posX] = 51;
        tileState[posY][posX]=tiles[posY][posX];

        blitter(posX,posY,xSource,ySource,tileSize,window);


		isTilling = false;

	
	}

}

