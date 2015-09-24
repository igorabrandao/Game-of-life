/*! \brief Class ConfigScreen.h.
 *
 *  Handle with visual elements.
*/
#ifndef CONFIGSCREEN_H
#define CONFIGSCREEN_H

#include <string>
#include <iostream>
#include "GameScreen.h"
#include "InputManager.h"
#include "LifeScreen.h"
#include "ScreenManager.h"
#include <sstream>

/*! ConfigScreen class */
class ConfigScreen : public GameScreen
{
    /*!
     * Public section
    */
    public:

        /*! Functions */
        ConfigScreen();     /*!< Constructor */
        ~ConfigScreen();    /*!< Destructor */

        void LoadContent(); /*!< Load the content on the screen */
        void UnloadContent(); /*!< Unload the content on the screen */
        void Update(sf::RenderWindow& window, sf::Event event); /*!< Update the screen content */
        void Draw(sf::RenderWindow& window); /*!< Print the content on the screen */
        void HandleInput(sf::RenderWindow& window, sf::Event event); /*!< Handle the input event */

        void SaveFilename(); /*!< Save the file */

    /*!
     * Protected section
    */
    protected:

    /*!
     * Private section
    */
    private:

        /*! Attributes */
        sf::Texture bgTexture;  /*!< Background texture */
        sf::Sprite  bgSprite;   /*!< Background sprite */

        sf::Text text;          /*!< Text object */
        sf::Font font;          /*!< Font */

        std::string tempString; /*!< Temporary string */
        bool flag;              /*!< Status flag that indicates typing event */

        InputManager input;     /*!< InputManager instance */
};

#endif // CONFIGSCREEN_H
