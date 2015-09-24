#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "GameScreen.h"
#include "TitleScreen.h"
#include "ScreenManager.h"
#include "FadeAnimation.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class SplashScreen : public GameScreen
{
	/*!
     * Public section
	*/
	public:
		/*! Functions */
		SplashScreen();
		~SplashScreen();

		void LoadContent(); // Load the content on the screen
		void UnloadContent(); // Unload the content on the screen
		void Update( sf::RenderWindow &Window, sf::Event event ); // Update the screen content
		void Draw( sf::RenderWindow &Window ); // Print the content on the screen
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
		sf::Texture image;

		std::vector<FadeAnimation*> fade;

		int unsigned imageNumber;
};

#endif // SPLASHSCREEN_H
