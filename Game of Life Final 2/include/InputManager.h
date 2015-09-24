#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>

class InputManager
{
	/*!
     * Public section
	*/
	public:
		/*! Functions */
		InputManager();  // class destructor
		~InputManager(); // class constructor

		/*! Update event */
		void Update( sf::Event event );

		/*! Catch the pressed key event */
		bool KeyPressed( int key );
		bool KeyPressed( std::vector<int> keys );

		/*! Catch the released key event */
		bool KeyReleased( int key );
		bool KeyReleased( std::vector<int> keys );

		/*! Catch the key down event */
		bool KeyDown( sf::RenderWindow &Window, sf::Keyboard::Key key );
		bool KeyDown( sf::RenderWindow &Window, std::vector<sf::Keyboard::Key> keys );

	/*!
     * Protected section
	*/
	protected:

	/*!
     * Private section
	*/
	private:
		sf::Event event;
};

#endif // INPUTMANAGER_H
