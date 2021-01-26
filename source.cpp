#include "source.h"


int main(int argc, char *argv[])
{

	Input input;
	Primer primer;
    Draw draw;
    Geom geom;

	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),"A-RPG/SFML2 - Branch");

	window.setVerticalSyncEnabled(true);

	primer.setLevel(1);

    primer.changeLevel();
    
    draw.initialize();

    
	// Boucle infinie, principale, du jeu 
	while (window.isOpen())
	{

		input.gestionInputs(window);

		update(input,geom, primer);

		render(window, draw);

		window.display();
	}

	return 0;

}

// Game update function: manages the game logic
void update ( Input &input,Geom &geom,Primer &primer )
{
    geom.update(input,primer);
}
   

void render( RenderWindow & window , Draw &draw )
{
window.clear();
 

draw.map(2, window );
draw.map(1, window );
draw.player(window);
draw.map(3, window );




}
