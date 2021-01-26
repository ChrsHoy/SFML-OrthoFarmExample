//#include "primer.h"
#include "geometries.h"
#include "input.h"


using namespace std;
using namespace sf;



Geom::Geom()
{
    warp_coming_from_x = warp_coming_from_y  = 0;
    xLength=yLength=width=height=0;
    deathtimer = 0;
    //tillable=false;
    centralX=centralY=0;
    warpDirection=-1;
    
}



void Geom::update(Input &input,Primer &primer)
{

    if (deathtimer == 0)
    {
        // It manages timer invincibility
        if (iframes > 0)
            iframes--;

        dirX = 0;
        dirY = 0;

        if (input.getKeys().run)
            isRunning = true;
        else
            isRunning = false;


        if (input.getKeys().left == true)
        {
            dirX -= pspeed +isRunning;

            direction = LEFT;

            if (state!= WALK)
            {

                state = WALK;
                deltatime = pframes;
                maxframe = 8;
                frame = 0;

            }
        }

        else if (input.getKeys().right == true)
        {

            dirX += pspeed + isRunning;

			// And it says it goes to the right (for flip
            // display, remember).
            direction = RIGHT;

            // If it was not his condition before
            if (state!= WALK)
            {
                // It saves the anim 'walking and is initialized to 0
                state = WALK;
                deltatime = pframes;
                maxframe = 8;
                frame = 0;
            }
        }

        // If it detects pressing the up arrow key
        else if (input.getKeys().up == true)
        {
            // It increases the x coordinate of the player
            dirY -= pspeed + isRunning;
            // And it says it goes to the right (for flip
            // display, remember).
            direction = UP;

            // If it was not his condition before
            if (state!= WALK)
            {
                // It saves the anim 'walking and is initialized to 0
                state = WALK;
                deltatime = pframes;
                maxframe = 8;
                frame = 0;
            }
        }

        // If it detects pressing the down arrow
        else if (input.getKeys().down == true)
        {
            // It increases the x coordinate of the player
            dirY += pspeed + isRunning;
            // And it says it goes to the right (for flip
            // display, remember).
            direction = DOWN;

            // If it was not his condition before
            if (state!= WALK)
            {
                // It saves the anim 'walking and is initialized to 0
                state = WALK;
                deltatime = pframes;
                maxframe = 8;
                frame = 0;
            }
        }

        // If it is based on nothing, we load the animation marking inactivity (Idle)
        else if (input.getKeys().right == false && input.getKeys().left == false &&
            input.getKeys().up == false && input.getKeys().down == false)
        {
            // It checks if the player was not already inactive, not to reload animation
            // each turn loop
            if (state!= IDLE)
            {
                // It saves the anim 'inactivity and is initialized to 0
                state = IDLE;
                deltatime = pframes;
                maxframe = 8;
                frame = 0;
            }
        }

		if (input.getKeys().work)
		{
            		isTilling=true;
            		//isTilling=0;
			input.setKeys(work, false);

		}
        //we add our collision detection funtcion that will make the details of our hero update
        mapCollision(primer);

        //It manages scrolling (function below)
        centerScrolling();
		
    }


    if (deathtimer > 0)
    {
        deathtimer--;

        if (deathtimer == 0)
        {
            // If it is dead, the level is reset
            

            changeLevel();
            initialize();

        }
    }

}



void Geom::centerScrolling()
{

    centralX = x + width/2 ;
    centralY = y + height/2 ;

    int minLimX = xSource + LIMIT_X;
    int minLimY = ySource + LIMIT_Y;
    

    int maxLimX = minLimX + LIMIT_W;
    int maxLimY = minLimY + LIMIT_H;


    if (centralX < xSource)
    {
        xSource-=30;
    }

    if (centralX > xSource + SCREEN_WIDTH)
    {
        xSource += 30;
    }

    else if (centralX < minLimX)
    {
        xSource -= (pspeed + isRunning);
    }


    else if (centralX > maxLimX)
    {
        xSource += (pspeed + isRunning);
    }

    if (centralY < minLimY)
    {
        ySource -= (pspeed + isRunning); 
    }
    

    if (centralY > maxLimY)
    {
        ySource += (pspeed + isRunning);
    }

    if (xSource < 0)
    {
        xSource=0;
    }

    if (ySource<0)
    {
        ySource=0;
    }

    else if (xSource + SCREEN_WIDTH >= xBound)
    {
        xSource=xBound - SCREEN_WIDTH;
    }

    else if (ySource + SCREEN_HEIGHT >= yBound)
    {
        ySource= yBound - SCREEN_HEIGHT;
    }
}


void Geom::mapCollision(Primer &primer)
{
    int i, x1, x2, y1, y2;

    if (height > tileSize)
        i = tileSize;
    else
        i = height;


    for (;;)
    {
        x1 = (x + dirX) / tileSize;
        x2 = (x + dirX + width - 1) / tileSize;


        y1 = (y) / tileSize;
        y2 = (y + i - 1) / tileSize;

		if (x1 >= 0 && x2 <tileColMax && y1>= 0 && y2 < tileRowMax)
		{
			if (dirX > 0)
			{
				if ((sub3[y1][x2] >= SPE1 && sub3[y1][x2] <= SPE10)
					|| (sub3[y2][x2] >= SPE1 && sub3[y2][x2] <= SPE10))
				{

					if (sub3[y1][x2] >= SPE1 && sub3[y1][x2] <= SPE10)
						numberSPE=0;//numberSPE = sub3[y1][x2] - SPE1;
					else
						numberSPE=0;//numberSPE = sub3[y2][x2] - SPE1;


					if (primer.getWarpSP(numberSPE) > 0)
					{
			
					primer.setSaveCheck(true);

				        warpDirection=4;
				        warp_coming_from_x=x;
				        warp_coming_from_y=y;

				        primer.setLevel(primer.getWarpSP(numberSPE));
				        changeLevel();
				        reinitialize();
                        
                        
					}

				}

				else if ((sub3[y1][x2] == WALL || sub3[y2][x2] == WALL))
				{

					x = x2 * tileSize;
					x -= (width + 1);
					dirX = 0;

				}
			}
			else if (dirX < 0)
			{

				if ((sub3[y1][x1] >= SPE1 && sub3[y1][x1] <= SPE10)
					|| (sub3[y2][x1] >= SPE1 && sub3[y2][x1] <= SPE10))
				{

					if (sub3[y1][x1] >= SPE1 && sub3[y1][x1] <= SPE10)
						numberSPE=0;//numberSPE = sub3[y1][x1] - SPE1;
					else
						numberSPE=0;//numberSPE = sub3[y2][x1] - SPE1;


					if (primer.getWarpSP(numberSPE) > 0)
					{
                        primer.setSaveCheck(true);
                        warpDirection=4;
                        warp_coming_from_x=x;
                        warp_coming_from_y=y;
                        primer.setLevel(primer.getWarpSP(numberSPE));
                        changeLevel();
                        reinitialize();
					}

				}

				else if (sub3[y1][x1] == WALL || sub3[y2][x1] == WALL)
				{
					x = (x1 + 1) * tileSize;
					dirX = 0;
				}

			}

		}
		if (i == height)
		{
			break;
		}

		i += tileSize;

		if (i > height)
		{
			i = height;
		}
	}

	if (width > tileSize)
		i = tileSize;
	else
		i = width;


	for (;;)
	{
		x1 = (x) / tileSize;
		x2 = (x + i) / tileSize;

		y1 = (y + dirY) / tileSize;
		y2 = (y + dirY + height) / tileSize;

		if (x1 >= 0 && x2 <tileColMax && y1>= 0 && y2 < tileRowMax)
		{
			if (dirY > 0)
			{

				if ((sub3[y2][x1] >= SPE1 && sub3[y2][x1] <= SPE10)
					|| (sub3[y2][x2] >= SPE1 && sub3[y2][x2] <= SPE10))
				

				{

					if (sub3[y2][x1] >= SPE1 && sub3[y2][x1] <= SPE10)
						numberSPE=0;//numberSPE = sub3[y2][x1] - SPE1;
					else
						numberSPE=0;//numberSPE = sub3[y2][x2] - SPE1;


					if (primer.getWarpSP(numberSPE) > 0)
					{
                        primer.setSaveCheck(true);
                        warpDirection=4;
                        warp_coming_from_x=x;
                        warp_coming_from_y=y;
                        primer.setLevel(WarpSP);
                        changeLevel();
                        reinitialize();
					}

				}

				else if (sub3[y2][x1] == WALL || sub3[y2][x2] == WALL)
				{
					y = y2 * tileSize;
					y -= (height + 1);
					dirY = 0;
				}

			}

			else if (dirY < 0)
			{
				if ((sub3[y1][x1] >= SPE1 && sub3[y1][x1] <= SPE10)
					|| (sub3[y1][x2] >= SPE1 && sub3[y1][x2] <= SPE10))
				{
					if (sub3[y1][x1] >= SPE1 && sub3[y1][x1] <= SPE10)
						numberSPE=0;//numberSPE = sub3[y1][x1] - SPE1;
					else
						numberSPE=0;//numberSPE = sub3[y1][x2] - SPE1;

					if (primer.getWarpSP(numberSPE) > 0)
					{
                        primer.setSaveCheck(true);                        
                        warpDirection=4;
                        warp_coming_from_x=x;
                        warp_coming_from_y=y;
                        primer.setLevel(WarpSP);
                        changeLevel();
                        
                        reinitialize();
					}

				}

				else if (sub3[y1][x1] == WALL || sub3[y1][x2] == WALL)
				{
					y = (y1 + 1) * tileSize;
					dirY = 0;
				}

			}
		}

		if (i == width)
		{
			break;
		}

		i += tileSize;

		if (i > width)
		{
			i = width;
		}
	}

	x += dirX;
	y += dirY;

	if (x < 0)
	{

		x = 0;
		if (WarpLeft > 0)
		{
            primer.setSaveCheck(true);            
            warpDirection=LEFT;
            warp_coming_from_x=x;
            warp_coming_from_y=y;
            primer.setLevel(WarpLeft);
            changeLevel();
            reinitialize();
		}

	}

	else if (x + width >= xBound)
	{

		x = xBound - width;

		if (WarpRight > 0)
		{
            primer.setSaveCheck(true);            
            warpDirection=RIGHT;
            warp_coming_from_x=x;
            warp_coming_from_y=y;
            primer.setLevel(WarpRight);
            changeLevel();
            reinitialize();
		}
	}

	else if (y < 0)
	{

		y = 0;

		if (WarpUP > 0)
		{
            primer.setSaveCheck(true);            
            warpDirection=UP;
            warp_coming_from_x=x;
            warp_coming_from_y=y;
            primer.setLevel(WarpUP);
            changeLevel();
            reinitialize();
		}
	}

	else if (y + height > yBound)
	{
		y = yBound - height;

		if (WarpDown > 0)
		{
            primer.setSaveCheck(true);
            warpDirection=DOWN;
            warp_coming_from_x=x;
            warp_coming_from_y=y;
            primer.setLevel(WarpDown);
            changeLevel();
            reinitialize();
		}
	}
}

 
void Geom::reinitialize()
{

	if (warpDirection == -1)
	{
		x = startX;
		y = startY;

		xSource=(startX - (SCREEN_WIDTH / 2));
		ySource=(startY - (SCREEN_HEIGHT / 2));
	}
	else if (warpDirection == UP)
	{

		y = yBound - height - 1;

		ySource=(yBound - SCREEN_HEIGHT);
	}
	else if (warpDirection == DOWN)
	{
		y = 1;
		ySource=0;
	}

	else if (warpDirection == LEFT)
	{
		x = xBound - width - 1;
		xSource=(xBound - SCREEN_WIDTH);
	}
	else if (warpDirection == RIGHT)
	{
		x = 1;
		xSource=0;
	}
	
	else if (warpDirection == 4)
	{
	COORD coord;
	
		coord.x = detectWarpSpe(numberSPE + SPE1).x;
		coord.y = detectWarpSpe(numberSPE + SPE1).y;

		if (direction == UP)
		{
			x = coord.x + 6;
			y = coord.y  -height - 6;
		}
		else if (direction == DOWN)
		{
			x = coord.x + 6;
			y = coord.y+ tileSize +6;
		}
		else if (direction == RIGHT)
		{
			x = coord.x + tileSize+6;
			y = coord.y + 6;
		}
		else if (direction == LEFT)
		{
			x = coord.x - width - 6;
			y = coord.y + 6;
		}
		else
		{
			x = startX;
			y = startY;
		}

		xSource=(x - (SCREEN_WIDTH / 2));
		ySource=(y - (SCREEN_HEIGHT / 2));
	}

}


Geom::POINT Geom::detectWarpSpe(int number)
{

	int x, y, MAXX, MAXY;
	POINT vertex;
	x = y = 0;

	MAXX = xBound / tileSize;
	MAXY = yBound / tileSize;

	for (y = 0; y < MAXY; ++y)
	{
		for (x = 0; x < MAXX; x++)
		{

			if (sub3[y][x]!= 0)
			{
					if (sub3[y][x] == number)
					{
						vertex.x = x * tileSize;
						vertex.y = y * tileSize;
						return vertex;
		
					}

			}

		}

	}

}


                        
