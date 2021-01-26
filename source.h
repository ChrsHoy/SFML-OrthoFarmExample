#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "input.h"
#include "primer.h"
#include "animation.h"
#include "geometries.h"

using namespace std;
using namespace sf;


//Fonctions
void update(Input &input,Geom &geom,Primer &primer);
void render(RenderWindow &window, Draw &draw);


// Taille de la fenêtre : 800x480 pixels 
const int  SCREEN_WIDTH = 800;
const int  SCREEN_HEIGHT = 480;
