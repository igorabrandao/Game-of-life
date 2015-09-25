/*! \brief Class ScreenManager.cpp.
 *
 *  Implements ScreenManager class functions
*/
#include "ScreenManager.h"

GameScreen *currentScreen, *newScreen;

/********************************************//**
* instance generator
***********************************************/
ScreenManager &ScreenManager::GetInstance()
{
	static ScreenManager instance;
	return instance;
}

/********************************************//**
*  destructor
***********************************************/
ScreenManager::~ScreenManager()
{ }

/********************************************//**
* generate new screen instance
***********************************************/
void 
ScreenManager::Initialize()
{
	currentScreen = new SplashScreen();
	transition = false;

	//file.LoadContent("assets/settings/test.hell", attributes, contents);
}

/********************************************//**
* screen's content loader
***********************************************/
void 
ScreenManager::LoadContent()
{
	currentScreen->LoadContent();

	sf::Texture image;
	sf::Vector2f pos;
	fade.LoadContent("", image, pos);
	fade.SetAlpha(0.0f);
}

/********************************************//**
* screen's content unloader
***********************************************/
void 
ScreenManager::Update( sf::RenderWindow &Window, sf::Event event )
{
	if ( !transition )
		currentScreen->Update(Window, event);
	Transition(Window);
}

/********************************************//**
* print the content on screen
***********************************************/
void 
ScreenManager::Draw( sf::RenderWindow &Window )
{
	currentScreen->Draw(Window);
}

/********************************************//**
* add a new screen
***********************************************/
void 
ScreenManager::AddScreen( GameScreen *screen )
{
	// Set transition state as true
	transition = true;

	// Pass the pointer to the attribute
	newScreen = screen;

	// Activate fade transition effect
	fade.SetValue(fade.GetActive(), true);

	// Define the fade transition value
	fade.SetAlpha(0.0f);
}

/********************************************//**
* handle screen transition
***********************************************/
void 
ScreenManager::Transition( sf::RenderWindow &Window )
{
	if ( transition )
	{
		fade.Update(Window);

		if ( fade.GetAlpha() >= 1.0f )
		{
			currentScreen->UnloadContent();
			delete currentScreen;
			currentScreen = newScreen;
			currentScreen->LoadContent();
			newScreen = NULL;
		}
		else if ( fade.GetAlpha() <= 0.0f )
		{
			transition = false;
			fade.SetValue(fade.GetActive(), false);
		}
	}
}

/********************************************//**
* get animation alpha value
***********************************************/
float 
ScreenManager::GetAlpha()
{
	return fade.GetAlpha();
}
