/*! \brief Class FadeAnimation.h.
 *
 *  Handle the fade animation.
*/
#ifndef FADEANIMATION_H
#define FADEANIMATION_H

#include "Animation.h"
#include <iostream>

/*! FadeAnimation class */
class FadeAnimation : public Animation
{
	/*!
     * Public section
	*/
	public:

		/*! Functions */
		FadeAnimation(void);	/*!< Constructor */
		~FadeAnimation(void);	/*!< Destructor */

		void LoadContent( std::string text, sf::Texture &image, sf::Vector2f position ); /*!< Load the content on the screen */
		void UnloadContent(); /*!< Unload the content on the screen */
		void Update( sf::RenderWindow &Window ); /*!< Update the screen content */
		void Draw( sf::RenderWindow &Window ); /*!< Print the content on the screen */

		virtual void SetAlpha( float alpha ); /*!< Set the alpha to fade transition */

	/*!
     * Protected section
	*/
	protected:

	/*!
     * Private section
	*/
	private:

		/*! Attributes */
		bool increase;
		float fadeSpeed;

		/*! Objects */
		sf::Clock clock; /*!< starts the clock */
};

#endif // FADEANIMATION_H
