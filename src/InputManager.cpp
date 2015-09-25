/*! \brief Class InputManager.cpp.
 *
 *  Implements input operations.
*/
#include "InputManager.h"

/********************************************//**
* constructor
***********************************************/
InputManager::InputManager()
{
	/* Empty */
}

/********************************************//**
* destructor
**********************************	*************/
InputManager::~InputManager()
{
	/* Empty */
}

/********************************************//**
* update event handler
***********************************************/
void 
InputManager::Update( sf::Event event_ )
{
	this->event = event_;
}

/********************************************//**
* catch the pressed key event
***********************************************/
bool 
InputManager::KeyPressed( int key_ )
{
	if ( event.key.code == key_ && event.type == sf::Event::KeyPressed )
		return true;
	return false;
}

/********************************************//**
* catch the pressed key event
***********************************************/
bool 
InputManager::KeyPressed( std::vector<int> keys_ )
{
	for ( int i = 0; i < keys_.size(); i++ )
	{
		if ( KeyPressed(keys_[i]) )
			return true;
	}
	return false;
}

/********************************************//**
* catch the released key event
***********************************************/
bool 
InputManager::KeyReleased( int key_ )
{
	if ( event.key.code == key_ && sf::Event::KeyReleased )
		return true;
	return false;
}

/********************************************//**
* catch the released key event
***********************************************/
bool 
InputManager::KeyReleased( std::vector<int> keys_ )
{
	for ( int i = 0; i < keys_.size(); i++ )
	{
		if ( KeyReleased(keys_[i]) )
			return true;
	}
	return false;
}

/********************************************//**
* catch the key down event
***********************************************/
bool 
InputManager::KeyDown( sf::RenderWindow &Window, sf::Keyboard::Key key_ )
{
	if ( sf::Keyboard::isKeyPressed(key_) )
		return true;
	return false;
}

/********************************************//**
* catch the key down event
***********************************************/
bool 
InputManager::KeyDown( sf::RenderWindow &Window, std::vector<sf::Keyboard::Key> keys_ )
{
	for ( int i = 0; i < keys_.size(); i++ )
	{
		if ( sf::Keyboard::isKeyPressed(keys_[i]) )
			return true;
	}
	return false;
}
