/*! \brief Animation.cpp.
 *
 *  Implements the game animations.
*/
#include "Animation.h"

/********************************************//**
* constructor
***********************************************/
Animation::Animation()
{
	/* Empty */
}

/********************************************//**
* destructor
***********************************************/
Animation::~Animation()
{
	/* Empty */
}

/********************************************//**
* content loader
***********************************************/
void 
Animation::LoadContent( std::string text, sf::Texture &image, sf::Vector2f position )
{
	this->preText = text;
	this->image = image;
	this->position = position;

	alpha = 1.0f;
	textColor = sf::Color(114, 77, 255);

	if ( image.getSize().y > 0 )
		sprite.setTexture(this->image);

	this->text.setString(text);
	active = false;
}

/********************************************//**
* content unloader
***********************************************/
void 
Animation::UnloadContent()
{
	/* Empty */
}

/********************************************//**
* update animation
***********************************************/
void 
Animation::Update( sf::RenderWindow &Window )
{
	/* Empty */
}

/********************************************//**
* render the animation
***********************************************/
void 
Animation::Draw( sf::RenderWindow &Window )
{
	std::string str = text.getString();

	//sprite.setSubRect(sourceRect);

	if ( str != "" )
	{
		text.setColor(sf::Color(255, 255, 255, 255 * alpha));
		text.setPosition(position);
		text.setScale(scale, scale);
		Window.draw(text);
	}

	if ( sprite.getTexture() != NULL )
	{
		sprite.setColor(sf::Color(255, 255, 255, 255 * alpha));
		sprite.setPosition(position);
		sprite.setScale(scale, scale);
		Window.draw(sprite);
	}
}

/********************************************//**
* get animation alpha value
***********************************************/
float 
&Animation::GetAlpha()
{
	return alpha;
}

/********************************************//**
* get animation active
***********************************************/
bool 
&Animation::GetActive()
{
	return active;
}

/********************************************//**
* get animation scale
***********************************************/
float 
&Animation::GetScale()
{
	return scale;
}

/********************************************//**
* set animation alpha value
***********************************************/
void 
Animation::SetAlpha( float value )
{
	alpha = value;
}
