#ifndef LIFESCREEN_H
#define LIFESCREEN_H

#include "GameScreen.h"
#include "ScreenManager.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>

class LifeScreen : public GameScreen
{
    public:
        LifeScreen();
        ~LifeScreen();

        void LoadContent();
        void UnloadContent();
        void Update(sf::RenderWindow& window, sf::Event event);
        void Draw(sf::RenderWindow& window);

        void LoadFilename();
        void LoadConfig();
        void SetGridPosition();
        void UpdateGeneration();
        void UpdateGridSprites();
        char SetAlive(char _cellState, int _liveNeighbors, char _cLive);

        bool IsStabe();
        bool IsExtinct();
        bool CompareVectors(std::vector<char> _vectorA, std::vector<char> _vectorB);
        void SavingGame();

    private:
        sf::Font font;
        sf::Text mGameStatus;
        sf::Text textTyped;
        sf::Text saveMessage;

        sf::Texture emptyCellTexture;
        sf::Texture virusTexture;
        sf::Sprite  emptyCellSprite;
        sf::Sprite  virusSprite;

        std::vector<sf::Sprite> grid;
        sf::SoundBuffer         buffer;
        sf::Sound               sound;
        sf::Vector2f            gridPosition;

        std::vector<char>       mMatriz;
        std::vector<char>       mMatrizAux;
        std::string             filename;
        int                     nRows;
        int                     nCols;
        char                    cLive;
        int                     numChanges;
        bool                    isExtinct;
        bool                    isStable;
        sf::RectangleShape      textbox;

        std::vector<std::vector<char>> generations;

};

#endif // LIFESCREEN_H
