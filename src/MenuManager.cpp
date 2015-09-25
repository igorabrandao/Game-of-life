/*! \brief Class MenuManager.cpp.
 *
 *  Implements menu's functions.
*/
#include "MenuManager.h"

/********************************************//**
* constructor
***********************************************/
MenuManager::MenuManager()
{
	/* Empty */
}

/********************************************//**
* destructor
***********************************************/
MenuManager::~MenuManager()
{
	/* Empty */
}

/********************************************//**
* load menu content
***********************************************/
void 
MenuManager::LoadContent( float width, float height )
{
	/*! Load screen fonts */
	if ( !font.loadFromFile("assets/fonts/8-BIT_WONDER.TTF") )
	{
		std::cout << "Could not find the specific font" << std::endl;
	}

	/*! Load screen music */
	if ( !buffer.loadFromFile("assets/sounds/menu_sound_theme.ogg") )
	{
		std::cout << "Could not find the menu music" << std::endl;
	}
	else
	{
		/* Initialize and play the sound */
		sound.setBuffer(buffer);
		sound.setLoop(true);
		sound.play();
	}

	/*! Load background image */
	if ( !background.loadFromFile("assets/images/menu/background.png") )
	{
		std::cout << "Could not find the background image" << std::endl;
	}
	else
	{
		image.setTexture(background);
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play game");
	menu[0].setPosition(sf::Vector2f(width/3, height/(MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Creditos");
	menu[1].setPosition(sf::Vector2f(width/3, height/(MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width/3, height/(MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}

/********************************************//**
* draw menu content
***********************************************/
void 
MenuManager::Draw( sf::RenderWindow &Window )
{
	Window.draw(image);
	for ( int i = 0; i < MAX_NUMBER_OF_ITEMS; i++ )
	{
		Window.draw(menu[i]);
	}
}

/********************************************//**
* move up on menu
***********************************************/
void 
MenuManager::MoveUp()
{
	if ( selectedItemIndex - 1 >= 0 )
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

/********************************************//**
* move down on menu
***********************************************/
void 
MenuManager::MoveDown()
{
	if ( selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS )
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}
