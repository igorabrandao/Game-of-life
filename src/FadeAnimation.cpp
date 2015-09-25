/*! \brief FadeAnimation.cpp.
 *
 *  Implements the fade animation.
*/
#include "FadeAnimation.h"

/********************************************//**
* constructor
***********************************************/
FadeAnimation::FadeAnimation(void)
{
	/* Empty */
}

/********************************************//**
* destructor
***********************************************/
FadeAnimation::~FadeAnimation(void)
{
	/* Empty */
}

/********************************************//**
* content loader
***********************************************/
void 
FadeAnimation::LoadContent( std::string text, sf::Texture &image, sf::Vector2f position )
{
	Animation::LoadContent(text, image, position);
	increase = false;
	fadeSpeed = 0.8f;
}

/********************************************//**
* content unloader
***********************************************/
void 
FadeAnimation::UnloadContent()
{

}

/********************************************//**
* catch the pressed key event
***********************************************/
void 
FadeAnimation::Update( sf::RenderWindow &Window )
{
	if ( active )
	{
		if ( !increase )
			alpha -= 0.02 * fadeSpeed;
		else
			alpha += 0.02 * fadeSpeed;

		if ( alpha >= 1.0f )
		{
			alpha = 1.0f;
			increase = false;
		}
		else if ( alpha <= 0.0f )
		{
			alpha = 0.0f;
			increase = true;
		}
	}
	else
	{
		alpha = 1.0f;
	}

	Animation::Update(Window);
}

/********************************************//**
* catch the pressed key event
***********************************************/
void 
FadeAnimation::Draw( sf::RenderWindow &Window )
{
	Animation::Draw(Window);
}

/********************************************//**
* set animation alpha value
***********************************************/
void 
FadeAnimation::SetAlpha( float value )
{
	alpha = value;

	if ( alpha == 0.0f )
		increase = true;
	else
		increase = false;
}
