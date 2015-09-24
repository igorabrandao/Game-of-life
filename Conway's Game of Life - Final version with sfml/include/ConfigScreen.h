#ifndef CONFIGSCREEN_H
#define CONFIGSCREEN_H

#include <string>
#include <iostream>
#include "GameScreen.h"
#include "InputManager.h"
#include "LifeScreen.h"
#include "ScreenManager.h"
#include <sstream>

class ConfigScreen : public GameScreen
{
    public:
        ConfigScreen();
        ~ConfigScreen();

        void LoadContent();
        void UnloadContent();
        void Update(sf::RenderWindow& window, sf::Event event);
        void Draw(sf::RenderWindow& window);
        void HandleInput(sf::RenderWindow& window, sf::Event event);

        void SaveFilename();
    protected:
    private:
        /** Background */
        sf::Texture bgTexture;
        sf::Sprite  bgSprite;

        sf::Text text;
        sf::Font font;

        std::string tempString;
        bool flag;

        InputManager input;

};

#endif // CONFIGSCREEN_H
