/*! \brief Class LifeScreen.h.
 *
 *  Handle with the game's engine.
*/
#ifndef LIFESCREEN_H
#define LIFESCREEN_H

#include "GameScreen.h"
#include "ScreenManager.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>

/*! LifeScreen class */
class LifeScreen : public GameScreen
{
    /*!
     * Public section
    */
    public:

        /*! Functions */
        LifeScreen();   /*!< Constructor */
        ~LifeScreen();  /*!< Destructor */

        /*! Screen and game methods */
        void LoadContent(); /*!< Load the content on the screen */
        void UnloadContent(); /*!< Unload the content on the screen */
        void Update(sf::RenderWindow& window, sf::Event event); /*!< Update the screen content */
        void Draw(sf::RenderWindow &Window); /*!< Print the content on the screen */

        /*! Support methods */
        void LoadFilename(); /*!< Load the filename from config file */
        void LoadConfig(); /*!< Load the setting from config file */
        void SetGridPosition(); /*!< Set the grud's location on the screen */
        void UpdateGridSprites(); /*!< Update the grid's visual elements */

        /*! Engine methods */
        bool IsStabe(); /*!< Check if the generation is stable */
        bool IsExtinct(); /*!< Check if the generation is extinct */
        void SavingGame(); /*!< Save the game */
        void UpdateGeneration(); /*!< Update the generation */
        void SaveOutputFile(sf::RenderWindow& window); /*!< Export the result to an output file */
        char SetAlive(char _cellState, int _liveNeighbors, char _cLive); /*!< Define the cells status */
        bool CompareVectors(std::vector<char> _vectorA, std::vector<char> _vectorB); /*!< Compare the generations */

    /*!
     * Private section
    */
    private:

        /*! Attributes */

        /*! Clock handle */
        static const sf::Time TimePerFrame;
        static const sf::Time TimePerFrameNormal;

        sf::Time timeSinceLastUpdate;
        sf::Time timeSinceLastUpdateNormal;
        sf::Clock clock;

        /*! Fonts and messages */
        sf::Font font;
        sf::Text mGameStatus;
        sf::Text textTyped;
        sf::Text saveMessage;
        sf::Text outputFilename;

        /*! Grid sprites */
        sf::Texture emptyCellTexture;
        sf::Texture virusTexture;
        sf::Sprite  emptyCellSprite;
        sf::Sprite  virusSprite;

        /*! Sound */
        std::vector<sf::Sprite> grid;
        sf::SoundBuffer         buffer;
        sf::Sound               sound;
        sf::Vector2f            gridPosition;

        /*! Data structure and status */
        std::vector<char>       mMatriz;
        std::vector<char>       mMatrizAux;
        std::string             filename;
        std::string             tempString;
        int                     nRows;
        int                     nCols;
        char                    cLive;
        int                     numChanges;
        bool                    isExtinct;
        bool                    isStable;
        bool                    flag;
        sf::RectangleShape      textbox;

        std::vector<std::vector<char>> generations;

};

#endif // LIFESCREEN_H