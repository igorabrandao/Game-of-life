#ifndef GAME_HPP
#define GAME_HPP

/** SFML includes */
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>

/** Includes */
#include <iostream> //! std::cout
#include <vector>   //! std::vector
#include <fstream>  //! std::ifstream, std::ofstream
#include <sstream>  //! std::istringstream, std::ostringstream
#include <string>   //! std::string

using namespace std;

class Game : private sf::NonCopyable
{
	public:
								Game();
		void					run();

	private:
		void					processEvents();
		void					update(sf::Time elapsedTime);
		void					render();

		void					updateStatistics(sf::Time elapsedTime);
		void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        void                    setTabuleiroPosition();
        void                    updateGrid();

        // Metodos do logica do jogo
        void                    readFile();
        void                    updateGeneration();
        char                    setAlive(char _cellState, int _liveNeighbors, char _cLive);
        bool                    isStabe();
        bool                    isExtinct();

	private:
		static const float		PlayerSpeed;
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		sf::Texture				mVirusTexture;
		sf::Texture             mEmptyCellTexture;
		sf::Sprite				mVirus;
		sf::Sprite              mEmptyCell;
		sf::Font				mFont;
		sf::Font                mTittleFont;
		sf::Text				mStatisticsText;
		sf::Text                mTittleText;
		sf::Text                mGameStatus;
		sf::Time				mStatisticsUpdateTime;

		std::size_t				mStatisticsNumFrames;
		bool					mIsMovingUp;
		bool					mIsMovingDown;
		bool					mIsMovingRight;
		bool					mIsMovingLeft;
		vector< sf::Sprite >    mTabuleiro;
		sf::Music               mSoundTheme;

		// Variaveis da logica do jogo
		vector< char >          mMatriz;
		vector< char >          mMatrizAux;
		string                  fileName;
		int                     nRows;
		int                     nCols;
		char                    cLive;
		int                     numChanges;
		bool                    flag;
};

#endif // GAME_HPP
