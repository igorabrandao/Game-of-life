/********************************************//**
* \MenuManager.h
* \Class to handle menu's issues
***********************************************/
#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define MAX_NUMBER_OF_ITEMS 3

class MenuManager
{
	/*!
     * Public section
	*/
	public:
		/*! Functions */
		MenuManager();
		~MenuManager();

		void LoadContent( float width, float height );
		void MoveDown(); // Unload memory allocation
		void MoveUp(); // Update the screen content
		void Draw( sf::RenderWindow &Window ); // Print the content on the screen
		int GetPressedItem() { return selectedItemIndex; }
		void SoundStop() { sound.stop(); }
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

