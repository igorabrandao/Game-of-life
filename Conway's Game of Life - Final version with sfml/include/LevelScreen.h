#ifndef LevelScreen_H
#define LevelScreen_H

#include "GameScreen.h"
#include "ScreenManager.h"
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class LevelScreen : public GameScreen
{
	/*!
     * Public section
	*/
	public:
		/*! Functions */
		LevelScreen();
		~LevelScreen();

		void LoadContent(); // Load the content on the screen
		void UnloadContent(); // Unload the content on the screen
		void Update( sf::RenderWindow &Window, sf::Event event ); // Update the screen content
		void Draw( sf::RenderWindow &Window ); // Print the content on the screen

		void GenerateEnemies();
	/*!
     * Protected section
	*/
	protected:

	/*!
     * Private section
	*/
	private:
		/*! Attributes */

		/* Background */
		sf::Texture background;
		sf::Sprite image;

		/* Time handle */
		sf::Clock clock;

		/* Sound */
		sf::SoundBuffer buffer;
		sf::Sound sound;

		/* Player */
		sf::Texture pTexture;
		sf::Sprite playerImage;

		/* General settings */
		int level;
};

#endif // LevelScreen_H
