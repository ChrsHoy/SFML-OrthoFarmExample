
// Legends of Meruvia - C ++ / SFML 2
// Copyright / Copyright: www.meruvia.fr - Jeremiah F. Bellanger
#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>


class Input
{
    // Structures
    struct Keys { bool left, right, up, down, attack, run, enter, spell, work; };

public:

    // Constructor
    Input();

    // accessor
    Keys getKeys(void) const;

    // Setter
    void setKeys(int keyon, bool state);

    // Functions
    void gestionInputs(sf::RenderWindow &window);
    void getInput(sf::RenderWindow &window);
	void getJoystick(sf::RenderWindow &window);
	




private:

    // Variables of the class private access
    sf::Event event;
    Keys keyon;
	const int DEAD_ZONE = 20;
    // Enum for buttons
    enum { up, down, right, left, attack, run, enter, Spell, work };
};
#endif