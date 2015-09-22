#include "LevelScreen.h"

/*! Direction enum */
enum Direction { Down, Left, Right, Up };
sf::Vector2i source(1, Down);
int firstImageX = 280, firstImageY = 38;
float frameCounter = 0, switchFrame = 100, frameSpeed = 1000;

float moveSpeed = 10000.0f;

/* Parallax */
sf::View view;
sf::Vector2f position(screenWidth/2, screenHeight/2);

/* Enemies */
std::list<sf::Sprite> enemy;
std::list<sf::Sprite>::iterator enemyit = enemy.begin(), next;
sf::Texture enemytex;
int erasedEnemies = 0;

/********************************************//**
* \class constructor
***********************************************/
LevelScreen::LevelScreen()
{
	/* Empty */
}

/********************************************//**
* \class destructor
***********************************************/
LevelScreen::~LevelScreen()
{
	/* Empty */
}

/********************************************//**
* \load content on screen
***********************************************/
void LevelScreen::LoadContent()
{
	keys.push_back( sf::Keyboard::Z );
	keys.push_back( sf::Keyboard::Return );

	/* Set initial screen bounds */
	view.reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	//if ( !pTexture.loadFromFile("assets/sprites/player.png", sf::IntRect(0, 0, 100, 85)) )
	if ( !pTexture.loadFromFile("assets/sprites/player.png") )
	{
		std::cout << "Could not load PlayerManager image" << std::endl;
	}
	else
	{
		playerImage.setTexture(pTexture);
		//playerImage.setPosition(100, 100);
	}

	/*! Load screen music */
	if ( !buffer.loadFromFile("assets/sounds/level_theme.ogg") )
	{
		std::cout << "Could not find the menu music" << std::endl;
	}
	else
	{
		/* Initialize and play the sound */
		sound.setBuffer(buffer);
		sound.setLoop(true);
		sound.play();
	}

	/*! Load background image */
	if ( !background.loadFromFile("assets/images/level/level01.png") )
	{
		std::cout << "Could not find the background image" << std::endl;
	}
	else
	{
		image.setTexture(background);
	}

	this->GenerateEnemies();
}

/********************************************//**
* \unload screen's content
***********************************************/
void LevelScreen::UnloadContent()
{
	GameScreen::UnloadContent();
}

/********************************************//**
* \update screen content
***********************************************/
void LevelScreen::Update( sf::RenderWindow &Window, sf::Event event )
{
	input.Update( event );

	/* Catch window event */
	switch ( event.type )
	{
		case sf::Event::Closed:
			Window.close();
			break;
	}

	if ( input.KeyDown(Window, sf::Keyboard::Up) )
	{
		source.y = Up;
		playerImage.move(0, -7);
	}
	else if ( input.KeyDown(Window, sf::Keyboard::Down) )
	{
		source.y = Down;
		playerImage.move(0, 7);
	}
	else if ( input.KeyDown(Window, sf::Keyboard::Right) )
	{
		source.y = Right;
		playerImage.move(7, 0);
	}
	else if ( input.KeyDown(Window, sf::Keyboard::Left) )
	{
		source.y = Left;
		playerImage.move(-7, 0);
	}

	// Change the sprites
	frameCounter += frameSpeed * clock.restart().asSeconds();
	if ( frameCounter >= switchFrame )
	{
		frameCounter = 0;
		source.x++;

		if( firstImageX > 272 )
			firstImageX = 272;
		else
			firstImageX = 400;
	}

	// Parallax effect update
	if ( playerImage.getPosition().x + 10 > (screenWidth / 2) )
		position.x = playerImage.getPosition().x + 10;
	else
		position.x = (screenWidth / 2);
}

/********************************************//**
* \enemie's generation
***********************************************/
void LevelScreen::GenerateEnemies()
{
	while( enemyit != enemy.end() )
	{std::cout << "AAAAAAAA" << std::endl;
	    next = enemyit;
	    next++;
	    if ( enemyit->getGlobalBounds().intersects(playerImage.getGlobalBounds()) )
	    {
	        enemy.erase(enemyit);
	        ++erasedEnemies;
	    }
	    enemyit = next;
	}

	if ( !enemytex.loadFromFile("assets/sprites/enemy.png") )
	{
		std::cout << "Could not load PlayerManager image" << std::endl;
	}
	else
	{
		for( int i = 0; i < erasedEnemies; ++i )
		{std::cout << "BBBBBBBB" << std::endl;
		    sf::Sprite tempSprite(enemytex);
		    srand(time(NULL));
		    float y = -200;
		    float x = rand() % 20 + 30;
		    tempSprite.setPosition(x, y);
		    y = y - tempSprite.getGlobalBounds().height * 2;
		    enemy.push_back(tempSprite);
		}
	}
}

/********************************************//**
* \print the screen content
***********************************************/
void LevelScreen::Draw( sf::RenderWindow &Window )
{
	/*! Sets parallax */
	view.setCenter(position);
	Window.setView(view);

	/*! Draw background */
	Window.draw(image);

	/*! Draw player sprite */
	playerImage.setTextureRect(sf::IntRect( firstImageX, firstImageY, 120, 50));
	Window.draw( playerImage );

	for ( enemyit=enemy.begin(); enemyit!=enemy.end(); ++enemyit )
	{std::cout << "CCCCCCCCC" << std::endl;
        Window.draw(*enemyit);
    }
}
