/*! \brief Class MenuManager.h.
 *
 *  Handle menu's issues.
*/
#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*! Constants */
#define MAX_NUMBER_OF_ITEMS 3

/*! MenuManager class */
class MenuManager
{
	/*!
     * Public section
	*/
	public:

		/*! Functions */
		MenuManager();		/*!< Constructor */
		~MenuManager();		/*!< Destructor */

		void LoadContent( float width, float height ); /*!< Load the content on the screen */
		void MoveDown(); /*!< Unload memory allocation */
		void MoveUp(); /*!< Update the screen content */
		void Draw( sf::RenderWindow &Window ); /*!< Print the content on the screen */
		int GetPressedItem() { return selectedItemIndex; } /*!< Get the pressed item */
		void SoundStop() { sound.stop(); } /*!< Stop sound */

	/*!
     * Protected section
	*/
	protected:

	/*!
     * Private section
	*/
	private:

		/*! Attributes */
		int selectedItemIndex;
		sf::Font font;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		sf::Texture background;
		sf::Sprite image;
		sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

#endif // MENUMANAGER_H

