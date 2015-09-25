/*! \brief Class ScreenManager.h.
 *
 *  Handle with screen issues
*/
#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <iostream>
#include "GameScreen.h"
#include "SplashScreen.h"
#include "TitleScreen.h"
#include "FadeAnimation.h"
#include "FileManager.h"

/*! CONSTANTS */
#define screenWidth 800
#define screenHeight 600

/*! ScreenManager class */
class ScreenManager
{
    /*!
     * Public section
    */
    public:

        /*! Functions */
        ~ScreenManager(); /*!< Destructor */
        static ScreenManager &GetInstance(); /*!< Instance generator */

        void Initialize(); /*!< Initialize the screen */
        void LoadContent(); /*!< Load the content on the screen */
        void UnloadContent(); /*!< Unload the content on the screen */
        void Update( sf::RenderWindow &Window, sf::Event event ); /*!< Update the screen content */
        void Draw( sf::RenderWindow &Window ); /*!< Print the content on the screen */

        void AddScreen( GameScreen *screen ); /*!< Add a new screen */

        float GetAlpha(); /*!< Get the alpha value for transitions */
        /*!<void GetFrameTime(); // Catch the timer clock
        /*!
         * Protected section
        */

    /*!
     * Protected section
    */
    protected:

    /*!
     * Private section
    */
    private:

        /*! Operators */
        const ScreenManager & operator=( const ScreenManager & ); // operator equal

        /*! Attributes */
        void Transition( sf::RenderWindow &Window ); // handle screen transition
        bool transition;

        /*! Classes instances */
        FadeAnimation fade;
        GameScreen *newScreen;
        FileManager file;

        std::vector<std::vector<std::string>> attributes;
        std::vector<std::vector<std::string>> contents;
};

#endif // SCREENMANAGER_H

