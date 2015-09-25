/*! \brief Class TitleScreen.h.
 *
 *  Handle game's menu.
*/
#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "GameScreen.h"
#include "ScreenManager.h"
#include "MenuManager.h"
#include "ConfigScreen.h"
#include <iostream>
#include <SFML/Graphics.hpp>

/*! TitleScreen class */
class TitleScreen : public GameScreen
{
	/*!
     * Public section
	*/
	public:

		/*! Functions */
		TitleScreen();		/*!< Constructor */
		~TitleScreen();		/*!< Destructor */

		void LoadContent(); /*!< Load the content on the screen */
		void UnloadContent(); /*!< Unload memory allocation */
		void Update( sf::RenderWindow &Window, sf::Event event ); /*!< Update the screen content */
		void Draw( sf::RenderWindow &Window ); /*!< Print the content on the screen */

	/*!
     * Protected section
	*/
	protected:

	/*!
     * Private section
	*/
	private:

		/*! Attributes */
		sf::Text text;
		sf::Font font;

		/*! Classes instances */
		MenuManager menu;
};

#endif // TITLESCREEN_H