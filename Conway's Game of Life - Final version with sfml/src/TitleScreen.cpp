#include "TitleScreen.h"

/********************************************//**
* \class constructor
***********************************************/
TitleScreen::TitleScreen()
{
	/* Empty */
}

/********************************************//**
* \class destructor
***********************************************/
TitleScreen::~TitleScreen()
{
	/* Empty */
}

/********************************************//**
* \load content on screen
***********************************************/
void TitleScreen::LoadContent()
{
	if ( !font.loadFromFile("assets/fonts/8-BIT_WONDER.TTF") )
	{
		std::cout << "Could not find the specific font" << std::endl;
	}

	text.setString("TitleScreen");
	text.setFont(font);

	keys.push_back(sf::Keyboard::Return);

	/* Load menu */
	menu.LoadContent(screenWidth, screenHeight);
}

/********************************************//**
* \unload screen's content
***********************************************/
void TitleScreen::UnloadContent()
{
	GameScreen::UnloadContent();
}

/********************************************//**
* \update screen content
***********************************************/
void TitleScreen::Update( sf::RenderWindow &Window, sf::Event event )
{
	input.Update( event );

	/* Catch window event */
	switch ( event.type )
	{
		case sf::Event::KeyPressed:

			/* Check wich key was pressed */
			switch (event.key.code)
			{
				/*! Up */
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				/*! Down */
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				/*! Enter */
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
						/*! New game */
						case 0:
							ScreenManager::GetInstance().AddScreen(new ConfigScreen);
							menu.SoundStop();
							break;

						/*! Options */
						case 1:
							std::cout << "Option menu selected" << std::endl;
							break;

						/*! Exit */
						case 2:
							Window.close();
							break;

					} break;

			} break;

		case sf::Event::Closed:
			Window.close();
			break;
	}
}

/********************************************//**
* \print the screen content
***********************************************/
void TitleScreen::Draw( sf::RenderWindow &Window )
{
	//Window.draw( text );
	menu.Draw(Window);
}
