/*! \brief Class SplashScreen.cpp.
 *
 *  Implements splash screen functions.
*/
#include "SplashScreen.h"

/********************************************//**
* constructor
***********************************************/
SplashScreen::SplashScreen()
{
	/* Empty */
}

/********************************************//**
* destructor
***********************************************/
SplashScreen::~SplashScreen()
{
	/* Empty */
}

/********************************************//**
* load content on screen
***********************************************/
void
SplashScreen::LoadContent()
{
	imageNumber = 0;

	if ( !font.loadFromFile("assets/fonts/8-BIT_WONDER.TTF") )
	{
		std::cout << "Could not find the specific font" << std::endl;
	}

	text.setString("SplashScreen");
	text.setFont(font);

	/* Keys that trigger the event */
	keys.push_back(sf::Keyboard::Return);

	file.LoadContent("assets/settings/splash.life", attributes, contents);

	for ( int unsigned i = 0; i < attributes.size(); i++ )
	{
		for ( int unsigned j = 0; j < attributes[i].size(); j++ )
		{
			std::string att = attributes[i][j];

			if ( att == "Image" )
			{
				sf::Vector2f pos(0, 0);
				image.loadFromFile(contents[i][j]);
				fade.push_back(new FadeAnimation);
				fade[fade.size() - 1]->LoadContent("", image, pos);
				fade[fade.size() - 1]->SetValue(fade[fade.size() - 1]->GetActive(), true);
				fade[fade.size() - 1]->SetValue(fade[fade.size() - 1]->GetScale(), 1.00f);
			}
		}
	}
}

/********************************************//**
* unload screen's content
***********************************************/
void
SplashScreen::UnloadContent()
{
	GameScreen::UnloadContent();

	for ( int unsigned i = 0; i < fade.size(); i++ )
	{
		fade[i]->UnloadContent();
		delete fade[i];
	}
	fade.clear();
}

/********************************************//**
* update screen content
***********************************************/
void 
SplashScreen::Update( sf::RenderWindow &Window, sf::Event event )
{
	input.Update( event );

	if ( fade[imageNumber]->GetAlpha() <= 0.0f )
		imageNumber++;

	if ( imageNumber != fade.size() - 1 );
		fade[imageNumber]->Update(Window);

	if ( input.KeyPressed(keys) || imageNumber >= fade.size() - 1 )
	{
		ScreenManager::GetInstance().AddScreen(new TitleScreen);
	}
}

/********************************************//**
* print the screen content
***********************************************/
void 
SplashScreen::Draw( sf::RenderWindow &Window )
{
	//Window.draw(text);
	fade[imageNumber]->Draw(Window);
}
