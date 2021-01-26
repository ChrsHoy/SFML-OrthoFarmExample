
// Legends of Meruvia - C ++ / SFML 2
// Copyright / Copyright: www.meruvia.fr - Jeremiah F. Bellanger

#include "input.h"

using namespace std;
using namespace sf;

// Constructor
Input::Input()
{
    keyon.left = keyon.right = keyon.up = keyon.down = 
		keyon.run = keyon.attack = keyon.enter = keyon.spell= keyon.work= false;
}


// accessor
Input::Keys Input::getKeys(void) const { return keyon; }


// Setter
void Input::setKeys(int keys, bool state)
{
    switch (keys)
    {
    case up:
        keyon.up = state;
        break;

    case down:
        keyon.down = state;
        break;

    case right:
        keyon.right = state;
        break;

    case left:
        keyon.left = state;
        break;

    case attack:
        keyon.attack = state;
        break;

    case run:
        keyon.run = state;
        break;

    case Spell:
        keyon.spell = state;
        break;

    case enter:
        keyon.enter = state;
        break;

	case work:
		keyon.work = state;
		break;
    }
}


// Functions
void Input::gestionInputs(sf::RenderWindow &window)
{
	if (sf::Joystick::isConnected(0))
		getJoystick(window);
	else
		getInput(window);
}

void Input::getJoystick(RenderWindow &window)
{
	// While there's events to handle ...
	while (window.pollEvent(event))
	{
		// We look at the type of the event ...
		switch (event.type)
		{
			// the window is closed
			case Event::Closed:
			window.close();
			break;

			// We press the Escape key to exit
			case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape)
				window.close();
			break;


			// If we press a joystick button
			case Event::JoystickButtonPressed:
			switch (event.joystickButton.button)
			{
				// Depending on the key number, we update our inputs
				// (see mapping a map of the Xbox 360).
				// Depending on your controller, it will probably adjust these values
			case 6:
				window.close();
				break;

			case 0:
				keyon.attack = true;
				break;

			case 1:
				keyon.spell = true;
				break;

			case 2:
				keyon.run = true;
				break;

			case 7:
				keyon.enter = true;
				break;

			default:
				break;
			}
			break;


			// Ditto if releasing a button on the controller
			case Event::JoystickButtonReleased :
			switch (event.joystickButton.button)
			{
			case 0:
				keyon.attack = false;
				break;

			case 1:
				keyon.spell = false;
				break;

			case 2:
				keyon.run = false;
				break;

			case 7:
				keyon.enter = false;
				break;

			default:
				break;
			}
			break;

			// It does not address other types of events
		default:
			break;
		}
	}


	// Treat the race Button X (2) apart
	if (sf::Joystick::isButtonPressed(0, 2))
		keyon.run = true;
	else
		keyon.run = false;


	//*** *** D - PAD 
		// Testing the X axis
		// If its value is negative, it goes left
		if (Joystick::getAxisPosition(0, Joystick::PovX) < -DEAD_ZONE)
		{
			keyon.right = false;
			keyon.left = true;
		}
	// Otherwise, it goes right
		else if (Joystick::getAxisPosition(0, Joystick::PovX) > DEAD_ZONE)
		{
			keyon.right = true;
			keyon.left = false;
		}
	// It does not matter, if there is no support
		else
		{
			keyon.right = false;
			keyon.left = false;
		}

	// Testing the Y axis
	// If its value is negative, it goes down
	if (Joystick::getAxisPosition(0, sf::Joystick::PovY) < -DEAD_ZONE)
	{
		keyon.up = false;
		keyon.down = true;
	}
	// Otherwise, it goes up
	else if (Joystick::getAxisPosition(0, sf::Joystick::PovY) > DEAD_ZONE)
	{
		keyon.up = true;
		keyon.down = false;
	}
	// It does not matter, if there is no support
	else
	{
		keyon.up = false;
		keyon.down = false;
	}

}


void Input::getInput(RenderWindow &window)
{
    // While there's events to handle ...
    while (window.pollEvent(event))
    {
        // see the type of the event ...
        switch (event.type)
        {
            // the window is closed
        case Event::Closed:
            window.close();
            break;

            // Key pressed
        case Event::KeyPressed:
            switch (event.key.code) // The key that was pressed
            {
            case Keyboard::Escape: // Escape
                window.close();
                break;

            case Keyboard::X:
                keyon.run = true;
                break;

            case Keyboard::C:
                keyon.spell = true;
                break;

            case Keyboard::V:
                keyon.attack = true;
                break;

            case Keyboard::Left:
                keyon.left = true;
                break;

            case Keyboard::Right:
                keyon.right = true;
                break;

            case Keyboard::Down:
                keyon.down = true;
                break;

            case Keyboard::Up:
                keyon.up = true;
                break;

            case Keyboard::Return:
                keyon.enter = true;
                break;

			case Keyboard::A:
				keyon.work = true;
				break;

            default:
                break;
            }
            break;

            // Key released
        case Event::KeyReleased:
            switch (event.key.code)
            {
            case Keyboard::X:
                keyon.run = false;
                break;

            case Keyboard::C:
                keyon.spell = false;
                break;

            case Keyboard::V:
                keyon.attack = false;
                break;

            case Keyboard::Left:
                keyon.left = false;
                break;

            case Keyboard::Right:
                keyon.right = false;
                break;

            case Keyboard::Down:
                keyon.down = false;
                break;

            case Keyboard::Up:
                keyon.up = false;
                break;


            case Keyboard::Return:
                keyon.enter = false;
                break;

			case Keyboard::A:
				keyon.work = false;
				break;

            default:
                break;
            }
            break;

            // we do not treat other types of events
        default:
            break;
        }
    }
}
