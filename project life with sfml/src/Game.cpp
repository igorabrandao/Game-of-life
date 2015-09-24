#include <Game.hpp>
#include <StringHelpers.hpp>

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: mWindow(sf::VideoMode(800, 640), "Game of Life", sf::Style::Close)
, mVirusTexture()
, mEmptyCellTexture()
, mVirus()
, mEmptyCell()
, mFont()
, mTittleFont()
, mStatisticsText()
, mTittleText()
, mGameStatus()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingRight(false)
, mIsMovingLeft(false)
, mTabuleiro()
, mSoundTheme()
, mMatriz()
, mMatrizAux()
, nRows()
, nCols()
, cLive()
, numChanges(0)
, flag(true)
{
    /** Carregando textura da celula vazia */
	if (!mEmptyCellTexture.loadFromFile("assets/textures/original20x20.png"))
		throw "Could not find emptyCellTexture!!!";

    /** Carregando textura do virus */
    if (!mVirusTexture.loadFromFile("assets/textures/virus20x20.png"))
        throw "Could not load virus20x20.png texture!!!";

    /** Carregando sound theme */
    if ( !mSoundTheme.openFromFile("assets/sounds/firstOfTheYear.ogg"))
        throw "Could not open firstOfTheYear.ogg!!!";

    /** Carregando a fonte do titulo */
    if ( !mTittleFont.loadFromFile("assets/fonts/Colleged.ttf"))
        throw "Could not load Collegd.ttf font!!!";

    mSoundTheme.play();

	mEmptyCell.setTexture(mEmptyCellTexture);
	mVirus.setTexture(mVirusTexture);

    /** Carrega o arquivo .dat */
	readFile();

    /** Preenche o tabuleiro com os sprites iniciais */
	for ( auto i(0); i < ( nRows * nCols ) ; ++i )
    {
        if ( mMatriz[ i ] == cLive )
            mTabuleiro.push_back( mVirus );
        else
            mTabuleiro.push_back( mEmptyCell );
    }

    setTabuleiroPosition();

	mFont.loadFromFile("assets/fonts/PoiretOne-Regular.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
	mTittleText.setFont(mTittleFont);
	mTittleText.setPosition(400.f,10.f);
	mTittleText.setString("Game of Life");
	mTittleText.setCharacterSize(40);

	/** Game Status Text */
	mGameStatus.setFont(mTittleFont);
	mGameStatus.setColor(sf::Color::Red);
	mGameStatus.setPosition(mWindow.getView().getCenter().x - 230.f,mWindow.getView().getCenter().y );
	mGameStatus.setString("");
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
    sf::Event event;
	while (mWindow.pollEvent(event))
	{
        switch (event.type)
		{

			case sf::Event::KeyPressed:
                if (flag)
                {
                    updateGeneration();
                    isStabe();
                    isExtinct();
                    flag = false;
                }
                break;
            case sf::Event::KeyReleased:
                flag = true;
                break;

			case sf::Event::Closed:
				mWindow.close();
				break;
		}

	}

}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	mVirus.move(movement * elapsedTime.asSeconds());
}

void Game::render()
{
	/** Clean the screen*/
	mWindow.clear();
	/** Print the grid on the screen */
	for( auto i(0); i < mTabuleiro.size() ; ++i )
    {
        mWindow.draw(mTabuleiro[i]);
    }
    /** Print the statistics text on the screen */
	mWindow.draw(mStatisticsText);
	/** Print the tittle text on the screen */
	mWindow.draw(mTittleText);
	/** draw all componentes on the screen */

	mWindow.draw(mGameStatus);

	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
    else if (key == sf::Keyboard::Return)
        updateGeneration();
}

void
Game::setTabuleiroPosition()
{
    sf::Vector2f mTabPosition(100.f, 100.f);
    float x = 100.f, y = 100.f;
    for ( auto i(0); i < nRows; ++i )
    {
        for ( auto j(0); j < nCols; ++j )
        {
            mTabuleiro[ i * nCols + j ].setPosition(mTabPosition);  // Seta a posição que sera imprimida na tela.
            mTabPosition.x = mTabPosition.x + 20.f;                 // Atualiza a cordenada do x
        }
        mTabPosition.x = 100.f;                     // X volta a coordenada original a cada pulo de linha
        mTabPosition.y = mTabPosition.y + 20.f;     // Atualiza a cordenada do x
    }
}


void
Game::readFile()
{
    //! Input stream do arquivo de entrada.
    ifstream ifsIn("assets/data/virus.dat"); /* trocar depois pelo getFileName()*/

    /** Usado para extrair dados da string lida do arquivo de entrada. */
    istringstream iss;
    string sLine;                   //! Armazena uma linha do arquivo de entrada.
    char cTemp;                     //! Char temporario para fazer o preencimento da matriz.

    if(!ifsIn.is_open())
    {
        /** Show message error */
        throw "Erro opening file";
    }
    else
    {
        // Lẽ o numero de linhas e colunas.
        ifsIn >> nRows;
        ifsIn >> nCols;

        //Lê o caractere usado como simbolo de celula viva.
        ifsIn >> cLive;

        /* Carrega a matriz com seus elementos.*/
        for(auto i(0); i < nRows; ++i)
        {
            for(auto j(0); j < nCols; ++j)
            {
                ifsIn >> cTemp;
                mMatriz.push_back(cTemp);
                // Preenche também a matriz auxiliar de forma que ela contenha os mesmos tamanho da matriz original.
                mMatrizAux.push_back(cTemp);
            }
        }
    }
}



void
Game::updateGeneration()
{
    // Contador de vizinhos vivos.
    int liveNeighbors = 0;
    char cellState;

    for(auto linha(0); linha < nRows; ++linha)
    {
        for(auto coluna(0); coluna < nCols; ++coluna)
        {
            //Se for alguma posição do topo.
            if(linha == 0)
            {
                //se for do top e da esquerda
                if(coluna == 0)
                {
                    // Verifica se a celula esta viva ou morta.
                    cellState = mMatriz[ linha * nCols + coluna];
                    // verifica vizinho da direita
                    if ( mMatriz[ linha * nCols + ( coluna + 1)] == cLive )     { liveNeighbors++; }
                    // verifica vizinho diretamente abaixo.
                    if ( mMatriz[ (linha + 1) * nCols + coluna ] == cLive )     { liveNeighbors++; }
                    // verifica vizinho abaixo a direita.
                    if ( mMatriz[ (linha + 1) * nCols + (coluna + 1) ] == cLive ) { liveNeighbors++; }
                    // Atualiza a matriz auxiliar com a proxima geração
                    mMatrizAux[ linha * nCols + coluna ] = setAlive(cellState, liveNeighbors, cLive);
                    // zera o numero de vizinhos vivos.
                    liveNeighbors = 0;
                }
                //se for do topo e da direita
                else if(coluna == nCols - 1)
                {
                    // Verifica se a celula esta viva ou morta.
                    cellState = mMatriz[ linha * nCols + coluna ];
                    // Verifica o vizinho da esquerda
                    if ( mMatriz[ linha * nCols + ( coluna - 1 ) ] == cLive )           { liveNeighbors++; }
                    // Verifica o vizinho abaixo e a esquerda
                    if ( mMatriz[ ( linha + 1 ) * nCols + ( coluna - 1 ) ] == cLive )   { liveNeighbors++; }
                    // Verifica o vizinho imediatamente abaixo
                    if ( mMatriz[ ( linha + 1 ) * nCols + coluna ] == cLive )           { liveNeighbors++; }
                    // Atualiza a matriz auxiliar com a proxima geração
                    mMatrizAux[ linha * nCols + coluna ] = setAlive( cellState, liveNeighbors, cLive );
                    // zera o numero de vizinhos vivos.
                    liveNeighbors = 0;
                }
                // Se for de cima sem ser das pontas
                else
                {
                    // Verifica se a celula esta viva ou morta.
                    cellState = mMatriz[ linha * nCols + coluna ];
                    // Verifica o vizinho da esquerda
                    if ( mMatriz[ linha * nCols + ( coluna - 1 ) ] == cLive )           { liveNeighbors++; }
                    // verifica o vizinho de baixo da esquerda
                    if ( mMatriz[ ( linha + 1 ) * nCols + ( coluna - 1 ) ] == cLive )   { liveNeighbors++; }
                    // verifica o vizinho de baixo
                    if ( mMatriz[ ( linha + 1 ) * nCols + coluna ] == cLive )           { liveNeighbors++; }
                    // verifica o vizinho de baixo da direita
                    if ( mMatriz[ ( linha + 1 ) * nCols + ( coluna + 1 ) ] == cLive )   { liveNeighbors++; }
                    // Verifica o vizinho da direita
                    if ( mMatriz[ linha * nCols + ( coluna + 1 ) ] == cLive )           { liveNeighbors++; }
                    // Atualiza a matriz auxiliar com a proxima geraço
                    mMatrizAux[ linha * nCols + coluna ] = setAlive( cellState, liveNeighbors, cLive );
                    // zera o numero de vizinhos vivos.
                    liveNeighbors = 0;
                }
            }
            // Se for alguma posição da borda esquerda (menos topo e bottom)
            else if( coluna == 0 && linha != 0 && linha != nRows - 1 )
            {
                // Verifica se a celula esta viva ou morta.
                cellState = mMatriz[ linha * nCols + coluna ];
                // Verifica o vizinho imediatamente acima
                if ( mMatriz[ ( linha - 1 ) * nCols + coluna ] == cLive )           { liveNeighbors++; }
                // Verifica o vizinho acima e a direita
                if ( mMatriz[ ( linha - 1 ) * nCols + ( coluna + 1 ) ] == cLive )   { liveNeighbors++; }
                // Verifica o vizinho da direita
                if ( mMatriz[ ( linha ) * nCols + ( coluna + 1 ) ] == cLive )       { liveNeighbors++; }
                // verifica o vizinho de baixo da direita
                if ( mMatriz[ ( linha + 1 ) * nCols + ( coluna + 1 ) ] == cLive )   { liveNeighbors++; }
                // verifica o vizinho de baixo
                if ( mMatriz[ ( linha + 1 ) * nCols + ( coluna + 1 ) ] == cLive )   { liveNeighbors++; }
                // Atualiza a matriz auxiliar com a proxima geraço
                mMatrizAux[ linha * nCols + coluna ] = setAlive( cellState, liveNeighbors, cLive );
                // zera o numero de vizinhos vivos.
                liveNeighbors = 0;
            }
            // Se for alguma posição da borda direita (menos topo e bottom)
            else if( coluna == nCols - 1 && linha != 0 && linha != nRows - 1)
            {
                // Verifica se a celula esta viva ou morta.
                cellState = mMatriz[ linha * nCols + coluna ];
                // Verifica o vizinho imediatamente acima
                if ( mMatriz[ ( linha - 1 ) * nCols + coluna ] == cLive )           { liveNeighbors++; }
                // Verifica o vizinho acima e a esquerda
                if ( mMatriz[ ( linha - 1 ) * nCols + ( coluna - 1 ) ] == cLive )   { liveNeighbors++; }
                // Verifica o vizinho da esquerda
                if ( mMatriz[ linha * nCols + ( coluna - 1 ) ] == cLive )           { liveNeighbors++; }
                // verifica o vizinho de baixo da esquerda
                if ( mMatriz[ ( linha + 1 ) * nCols + ( coluna - 1 ) ] == cLive )   { liveNeighbors++; }
                // verifica o vizinho de baixo
                if ( mMatriz[ ( linha + 1 ) * nCols + coluna ] == cLive )           { liveNeighbors++; }
                // Atualiza a matriz auxiliar com a proxima geraço
                mMatrizAux[ linha * nCols + coluna ] = setAlive( cellState, liveNeighbors, cLive );
                // zera o numero de vizinhos vivos.
                liveNeighbors = 0;
            }
            // Se for alguma posição do bottom
            else if( linha == nRows - 1)
            {
                // Se for do botorm e da esquerda
                if ( coluna == 0 )
                {
                    // Verifica se a celula esta viva ou morta.
                    cellState = mMatriz[ linha * nCols + coluna ];
                    // Verifica o vizinho imediatamente acima
                    if ( mMatriz[ ( linha - 1 ) * nCols + coluna ] == cLive )           { liveNeighbors++; }
                    // Verifica o vizinho acima e a direita
                    if ( mMatriz[ ( linha - 1 ) * nCols + ( coluna + 1 ) ] == cLive )   { liveNeighbors++; }
                    // Verifica o vizinho da direita
                    if ( mMatriz[ linha * nCols + ( coluna + 1 ) ] == cLive )           { liveNeighbors++; }
                    // Atualiza a matriz auxiliar com a proxima geraço
                    mMatrizAux[ linha * nCols + coluna ] = setAlive( cellState, liveNeighbors, cLive );
                    // zera o numero de vizinhos vivos.
                    liveNeighbors = 0;
                }
                // Se for do bottom e da direita
                else if ( coluna == nCols - 1 )
                {
                    // Verifica se a celula esta viva ou morta.
                    cellState = mMatriz[ linha * nCols + coluna ];
                    // Verifica o vizinho imediatamente acima
                    if ( mMatriz[ ( linha - 1 ) * nCols + coluna ] == cLive )           { liveNeighbors++; }
                    // Verifica o vizinho acima e a esquerda
                    if ( mMatriz[ ( linha - 1 ) * nCols + ( coluna - 1 ) ] == cLive )   { liveNeighbors++; }
                    // Verifica o vizinho da esquerda
                    if ( mMatriz[ linha * nCols + ( coluna - 1 ) ] == cLive )           { liveNeighbors++; }
                    // Atualiza a matriz auxiliar com a proxima geraço
                    mMatrizAux[ linha * nCols + coluna ] = setAlive( cellState, liveNeighbors, cLive );
                    // zera o numero de vizinhos vivos.
                    liveNeighbors = 0;
                }
                // Se for do bottom (mas não for das pontas)
                else
                {
                    // Verifica se a celula esta viva ou morta.
                    cellState = mMatriz[ linha * nCols + coluna ];
                    // Verifica o vizinho da esquerda
                    if ( mMatriz[ linha * nCols + ( coluna - 1 ) ] == cLive )           { liveNeighbors++; }
                    // Verifica o vizinho acima e a esquerda
                    if ( mMatriz[ ( linha - 1 ) * nCols + ( coluna - 1 ) ] == cLive )   { liveNeighbors++; }
                    // Verifica o vizinho imediatamente acima
                    if ( mMatriz[ ( linha - 1 ) * nCols + coluna ] == cLive )           { liveNeighbors++; }
                    // Verifica o vizinho acima e a direita
                    if ( mMatriz[ ( linha - 1 ) * nCols + ( coluna + 1 ) ] == cLive )   { liveNeighbors++; }
                    // Verifica o vizinho da direita
                    if ( mMatriz[ linha * nCols + ( coluna + 1 ) ] == cLive )           { liveNeighbors++; }
                    // Atualiza a matriz auxiliar com a proxima geraço
                    mMatrizAux[ linha * nCols + coluna ] = setAlive( cellState, liveNeighbors, cLive );
                    // zera o numero de vizinhos vivos.
                    liveNeighbors = 0;
                }
            }
            // Se for qualquer posição (menos laterais)
            else
            {
                // Verifica se a celula esta viva ou morta.
                cellState = mMatriz[ linha * nCols + coluna ];
                // Verifica o vizinho da esquerda
                if ( mMatriz[ linha * nCols + ( coluna - 1 ) ] == cLive )           { liveNeighbors++; }
                // Verifica o vizinho acima e a esquerda
                if ( mMatriz[ ( linha - 1 ) * nCols + ( coluna - 1 ) ] == cLive )   { liveNeighbors++; }
                // Verifica o vizinho imediatamente acima
                if ( mMatriz[ ( linha - 1 ) * nCols + coluna ] == cLive )           { liveNeighbors++; }
                // Verifica o vizinho acima e a direita
                if ( mMatriz[ ( linha - 1 ) * nCols + ( coluna + 1 ) ] == cLive )   { liveNeighbors++; }
                // Verifica o vizinho da direita
                if ( mMatriz[ linha * nCols + ( coluna + 1 ) ] == cLive )           { liveNeighbors++; }
                // Verifica o vizinho abaixo e a direita
                if ( mMatriz[ ( linha + 1 ) * nCols + ( coluna + 1 ) ] == cLive )   { liveNeighbors++; }
                // Verifica o vizinho imediatamente abaixo
                if ( mMatriz[ ( linha + 1 ) * nCols + coluna ] == cLive )           { liveNeighbors++; }
                // Verifica o vizinho abaixo e a esquerda
                if ( mMatriz[ ( linha + 1 ) * nCols + ( coluna - 1 ) ] == cLive )   { liveNeighbors++; }
                // Atualiza a matriz auxiliar com a proxima geraço
                mMatrizAux[ linha * nCols + coluna ] = setAlive( cellState, liveNeighbors, cLive );
                // zera o numero de vizinhos vivos.
                liveNeighbors = 0;
            }
        }
    }

    // Copia o conteudo da matriz auxiliar para a matriz original.
    for(auto i(0); i < nRows; ++i)
    {
        for(auto j(0); j < nCols; ++j)
        {
            if(mMatriz[i * nCols + j] != mMatrizAux[i * nCols + j] )
                numChanges++;
            mMatriz[i * nCols + j] = mMatrizAux[i * nCols + j];
        }
    }

    /** Atualiza os sprites do tabuleiro */
    updateGrid();
}



char
Game::setAlive(char _cellState, int _liveNeighbors, char _cLive)
{
    // Rule number 1
    if (_cellState == _cLive && _liveNeighbors <= 1)
        return '.';
    // Rule number 2
    else if (_cellState == _cLive && _liveNeighbors >= 4)
        return '.';
    // Rule number 3
    else if (_cellState == _cLive && (_liveNeighbors == 2 || _liveNeighbors == 3))
        return _cLive;
    // Rule number 4
    else if (_cellState != _cLive && _liveNeighbors == 3)
        return _cLive;

    return 'X';
}


void
Game::updateGrid()
{
    for ( auto i(0); i < ( nRows * nCols ) ; ++i )
    {
        if ( mMatriz[ i ] == cLive )
            mTabuleiro[ i ] = mVirus;
        else
            mTabuleiro[ i ] = mEmptyCell;
    }
    setTabuleiroPosition();
}


bool
Game::isStabe()
{
    if(numChanges == 0)
    {
        mGameStatus.setString("Generation Estabilized!!!");
        return true;
    }
    else
    {
        numChanges = 0;
        return false;
    }

}


bool
Game::isExtinct()
{
    bool isExtinct = true;
    for( auto i(0) ; i < ( nCols * nRows) ; ++i )
    {
        if( mMatriz[ i ] == cLive )
        {
            isExtinct = false;
            return  isExtinct;
        }
    }

    // Caso não exista nenhuma celula viva
    mGameStatus.setString("Generation extinct!!!");
    return isExtinct;
}
