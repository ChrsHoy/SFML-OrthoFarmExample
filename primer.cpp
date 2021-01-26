#include "primer.h"

using namespace std;
using namespace sf;

ofstream save;

//static int state[10]{0,0,0,0,0,0,0,0,0,0};
static bool state[10]{false,false,false,false,false,false,false,false,false,false };
//sf::Time elapsed=sf::seconds(0.1f);

int Primer::xBound=0;
int Primer::yBound=0;
int Primer::startX=0;
int Primer::startY=0;

int Primer::tiles[80][80];
int Primer::sub1[80][80];
int Primer::sub2[80][80];
int Primer::sub3[80][80];

int Primer::tileState[320][80];
int Primer::extraState[119];
int Primer::extraState2[3];

int Primer::WarpUP=0;
int Primer::WarpDown=0;
int Primer::WarpLeft=0;
int Primer::WarpRight=0;
int Primer::WarpSP=0;

bool Primer::checkSave=false;
bool Primer::checkHealth=false;

int Primer::level=0;

// Constructor
Primer::Primer()
{

    // Other variables

    level = 1;

    //checkLevel=false;
    checkLevel=true;

    checkSave=false;
    checkHealth=false;
    deltaCycle=0;
    tileSet=false;
    
//    for(int i=0;i<10;i++){checkLoad[i]=false;}
        
    for(int i=0;i<10;i++)
        warps[i]=0;


}

bool Primer::getCheck(void) const {return check;}
bool Primer::getLevelCheck(void) const {return checkLevel;}
bool Primer::getSaveCheck(void) const {return checkSave;}
bool Primer::getHealthCheck(void) const {return checkHealth;}


int Primer::getWarpSP(int number) const { return warpSP[number].value; }
int Primer::getWarpS(int number) const {return warps[number];}

void Primer::setCheck(bool value){check=value;}
void Primer::setLevel(int value) { level = value; }
void Primer::setLevelCheck(bool value){checkLevel=value;}
void Primer::setSaveCheck(bool value){checkSave=value;}
void Primer::setHealthCheck(bool value){checkHealth=value;}



// Functions
void Primer::changeLevel(void)
{
	//Save primer
    
///*
    if(getSaveCheck()||getHealthCheck()==true)
    {

    for(int i=0;i<3;i++)
        save << extraState2[i] << " ";

    for(int i=0;i<MAX_MAP_Y*4;i++)
	{
        if (i != 0)
            save << "\n";
        for(int j=0;j<MAX_MAP_X;j++){save << tileState[i][j] << " ";}

    }
    save << "\n";
    for (int i = 0; i < 119; i++)
    {
        save << extraState[i] << " ";
    }
        save.close();       
    }

//*/ 

    filename = "map/map" + to_string(level) + ".txt";
	sFile = "state/save"+to_string(level)+".txt";
    
    LoadMap(filename,sFile);

    sPtr=&sFile;
    setSaveCheck(false);
    setHealthCheck(false);
    //setLevelCheck(true);


}



void Primer::LoadMap(string filename,string sFile)
{
    /*This function will be called at the onset of the changelevel instance
     Create a stream (stream) to read our file
     x and y will serve us for loops below */
    fstream fin;
    //fstream end;
    int x = 0;
    int y = 0;


	for (x; x < MAX_MAP_X; x++)
		for (y; y < MAX_MAP_Y * 4; y++)
			tileState[y][x] = 0;

	//vector<vector<int>> Map::tileState(MAX_MAP_Y*4+1,vector<int>(MAX_MAP_X));

    // We resets maxX maxY and that will help us
    // determine the size of the map
    xBound = 0;
    yBound = 0;

    // Create a 2-dimensional vector (a vector of vectors, what)
    vector < vector < int >> lines;

    // Create a temporary vector to read a line
    vector < int > myVectData;

    // temporary character strings are created
    string strBuf, strTmp;

    // Create a stringstream to manage our channels
    stringstream iostr;

    /*Here we create a buffer to load the inputs
    Then we convert into integer so we can then use in our operations 
    such as Draw function*/

    // Open the file

    ///*
    if(state[level-1]==false)
    {
        fin.open(filename, fstream::in);
        state[level-1] = true;
    }
    else
        fin.open(sFile, fstream::in);
    //*/
    //fin.open(filename, fstream::in);
    // If it fails, an error is made
    if (!fin.is_open())
    {
        cerr << "Error loading file. \n";
        exit(1);
    }

    // We read our file to the end (eof = end of file)
    while (!fin.eof())
    {
        // line is recovered in the chain strBuf
        getline(fin, strBuf);

        // If the line is empty, the loop is continued
        if (!strBuf.size())
            continue;

        // If it continues and we reset our stringstream
        iostr.clear();

        // It sends the contents of the buffer strBuf
        iostr.str(strBuf);

        // we reset the row vector
        myVectData.clear();

        /* Loop to read each tile number of the map file
        //this loop converts the strings from the buffer from the map instance
        //into integers for the draw function
        into a vector array*/
        while (true)
        {
            // For each line is recovered the number of the tile in
            // parsing through the spaces that separate them ( '')
            getline(iostr, strTmp, ' ');

            // Get this number in our row vector
            myVectData.push_back(atoi(strTmp.c_str()));

            // If we finished, we leave the loop
            if (!iostr.good()) break;
        }

        // If the vector line is not empty, we send our vector 2D
        if (myVectData.size())
            lines.push_back(myVectData);
    }

    // Close the file
    fin.close();

    /*We will now fill the variables of our class with our vector
    2 temporary dimensions.
    We first retrieve the first 3 values ​​of the first line (0)
    that are the starting values ​​of the hero and the tileset to display
    note x.size=80 after 1st column where we exclude meta data */
    startX = lines[0][0];
    startY = lines[0][1];
    tileSetGroup = lines[0][2];

    extraState2[0]= lines[0][0];
    extraState2[1] = lines[0][1];
    extraState2[2] = lines[0][2];

    /*These loops are over the partitions in the map.txt for each respective layer
    The loops are integral in populating the tile array members 
    which are used for the draw function
    the first line is then loaded individually because it contains data +
    (offset 3 numbers because the previous 3) */
        for (x = 3; x < MAX_MAP_X+3; x++)
        {
            tiles[0][x-3] = lines[0][x];

            tileState[0][x-3] = lines[0][x];

        }


    /* Then we load the rest of the tile table for layer 1.
     Loop until MAX_MAP_Y and MAX_MAP_X or dimensions
     max of the map (400 x 150 tiles, for booster) */
    for (y = 1; y < MAX_MAP_Y; ++y)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            // Copy the value of our temporary vector
            // in our two-dimensional array
            tiles[y][x] = lines[y][x];
        
            tileState[y][x]=lines[y][x];
		
            
			// is detected if the tile is not empty
            if (tiles[y][x] > 0)
            {
                /* If this is the case, increases the value of maxX or
                maxY because the map is not yet over.
                layer 1 has more properties therefore it will be the largest set*/
                if (x > xBound)
                {xBound = x;}

                if (y > yBound)
                {yBound = y;}
                
            }

        }

	}

    // Do the same for the second layer of tiles:
    for (y = 0; y < MAX_MAP_Y; ++y)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            //appropriates the row
            sub1[y][x] = lines[y + MAX_MAP_Y][x];

            tileState[y+MAX_MAP_Y][x]=sub1[y][x];
        }
    }

    // And the third:
    for (y = 0; y < MAX_MAP_Y; ++y)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            sub2[y][x] = lines[y + MAX_MAP_Y * 2][x];

            tileState[y+MAX_MAP_Y*2][x]=sub2[y][x];
        }
    }

    // And finally the fourth (the collision layer
    // and special tiles)
    for (y = 0; y < MAX_MAP_Y; ++y)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            sub3[y][x] = lines[y + MAX_MAP_Y * 3][x];

            tileState[y+MAX_MAP_Y*3][x]=sub3[y][x];
		
		}
    }

    // Load the additional variables

    save.open(sFile);

    y = MAX_MAP_Y * 4;

    WarpUP = lines[y][0];
    WarpDown = lines [y][1];
    WarpLeft = lines  [y][2];
    WarpRight = lines  [y][3];
    WarpSP=lines[y][4];
    for (int i = 0; i < 10; i++)
    {
        warpSP[i].value = lines[y][i + 4];

    }

    for (int i = 0; i < 20; i++)
    {
        NPC[i].type = lines[y][14 + i * 3];
        NPC[i].text = lines[y][15 + i * 3];
        NPC[i].quest = lines[y][16 + i * 3];
    }

    for (int i = 0; i < 20; i++)
    {
        chest[i].type = lines[y][74 + i];
    }

    loot = lines[y][94];
    weather = lines[y][95];
    cinematics = lines[y][96];
    cinematics_condition = lines[y][97];
    musicNumber = lines[y][98];

    for (int i = 0; i < 10; i++)
    {
        keyon[i].type = lines[y][99 + i];
    }

    for (int i = 0; i < 10; i++)
    {
        trap[i].type = lines[y][109 + i];
    }
	
    /* It converts the maximum dimensions of our map in pixels, adding
    1 (since it starts at the row / column 0) and multiplying by the value
     pixels in a tile (32 pixels). */
    xBound= (xBound + 1) * tileSize;
    yBound = (yBound + 1) * tileSize;
    
    for (int i = 0; i < 119; i++)
        extraState[i] = lines[y][i];
    
}
