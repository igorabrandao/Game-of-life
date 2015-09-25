/*! \brief Class GameScreen.h.
 *
 *  Manage the game screens.
*/
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "FileManager.h"

/*! GameScreen class */
class GameScreen
{
	/*!
     * Public section
	*/
	public:

		/*! Functions */
		GameScreen();  /*!< Constructor */
		~GameScreen(); /*!< Destructor */

		virtual void LoadContent(); /*!< Load the content on the screen */
		virtual void UnloadContent(); /*!< Unload the content on the screen */
		virtual void Update( sf::RenderWindow &Window, sf::Event event ); /*!< Update the screen content */
		virtual void Draw( sf::RenderWindow &Window ); /*!< Print the content on the screen */

	/*!
     * Protected section
	*/
	protected:

		/*! InputManager instance */
		InputManager input;
		std::vector<int> keys;

		/*! FileManager instance */
		FileManager file;

		std::vector<std::vector<std::string>> attributes;
		std::vector<std::vector<std::string>> contents;

		std::string filename;

	/*!
     * Private section
	*/
	private:
};

#endif // GAMESCREEN_H

