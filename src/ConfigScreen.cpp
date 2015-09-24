#include "ConfigScreen.h"

ConfigScreen::ConfigScreen()
{
    //ctor
}

ConfigScreen::~ConfigScreen()
{
    //dtor
}

void
ConfigScreen::LoadContent()
{
    tempString = "";
    if(!bgTexture.loadFromFile("assets/images/config/background.png"))
    {
        // Handle error
    }
    else
    {
        bgSprite.setTexture(bgTexture);
    }

    if(!font.loadFromFile("assets/fonts/lora.ttf"))
    {
        // Handle error
    }
    else
    {
        text.setFont(font);
        text.setString(tempString);
        text.setCharacterSize(20);
        text.setPosition(40,130);
        text.setColor(sf::Color::Black);
    }

    flag = false;
}

void
ConfigScreen::UnloadContent()
{
}

void
ConfigScreen::Update(sf::RenderWindow& window, sf::Event event)
{
    HandleInput(window,event);
}

void
ConfigScreen::Draw(sf::RenderWindow& window)
{
    window.draw(bgSprite);
    window.draw(text);
}


void
ConfigScreen::HandleInput(sf::RenderWindow& window, sf::Event event)
{
    switch(event.type)
    {
        case sf::Event::TextEntered:
            if(flag == false)
            {
                if( event.text.unicode >= 32 && event.text.unicode < 127 )
                {
                    tempString += (char)event.text.unicode;
                    flag = true;
                }
                else if( event.text.unicode == 8 ) /** Backspace*/
                {
                    if ( tempString.length() > 0)
                        tempString = tempString.substr(0, tempString.length() - 1 );
                        flag = false;
                }
                else if( event.text.unicode == 13) /** Enter key*/
                {
                    SaveFilename();
                    ScreenManager::GetInstance().AddScreen(new LifeScreen);
                }
            }
            break;
        case sf::Event::KeyReleased:
            flag = false;
            break;
    }
    text.setString(tempString);
    filename = tempString;
}


void
ConfigScreen::SaveFilename()
{
    std::ofstream ofs;
    std::ostringstream oss;

    ofs.open("config.txt");

    if(!ofs.is_open())
    {
        std::cout << "Error opening out.txt file!!!" << std::endl;
        std::cout << "Closing the program..." << std::endl;
    }
    else
    {
        oss << tempString;
        std::string s = oss.str();
        ofs << s;
        ofs.close();
    }
}

