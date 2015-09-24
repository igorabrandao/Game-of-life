#include "LifeScreen.h"

LifeScreen::LifeScreen()
{
    //ctor
}

LifeScreen::~LifeScreen()
{
    //dtor
}


void
LifeScreen::LoadContent()
{
    /** Load Resources */
    if(!emptyCellTexture.loadFromFile("assets/images/life/emptyCell20x20.png"))
        throw "Cound not find emptyCell20x20.png!!!";
    else
        emptyCellSprite.setTexture(emptyCellTexture);

    if(!virusTexture.loadFromFile("assets/images/life/virus20x20.png"))
        throw "Could not find virus20x20.png!!!";
    else
        virusSprite.setTexture(virusTexture);

    if(!buffer.loadFromFile("assets/sounds/wallpaper.ogg"))
        throw "Could not find wallpaper.ogg";
    else
        sound.setBuffer(buffer);

    if(!font.loadFromFile("assets/fonts/lora.ttf"))
    {
        // Handle error.
    }
    else
    {
        mGameStatus.setFont(font);
        mGameStatus.setString("");
        mGameStatus.setCharacterSize(30);
        mGameStatus.setPosition( (screenWidth / 2) , screenHeight / 2 );
    }
    LoadConfig();
    sound.play();

    /** Preenche o tabuleiro com os sprites iniciais */
	for ( auto i(0); i < ( nRows * nCols ) ; ++i )
    {
        if ( mMatriz[ i ] == cLive )
            grid.push_back(virusSprite);
        else
            grid.push_back(emptyCellSprite);
    }
    // Insere a primeira geração da matriz;
    generations.push_back(mMatriz);

    SetGridPosition();

    isExtinct   = false;
    isStable    = false;
    /** Setando o textbox*/
    textbox.setFillColor(sf::Color::White);
    textbox.setSize(sf::Vector2f(0,0));
    textbox.setOutlineColor(sf::Color::Yellow);
    textbox.setOutlineThickness(5);

    saveMessage.setFont(font);
    saveMessage.setString("");
    saveMessage.setColor(sf::Color::Red);
    saveMessage.setStyle(sf::Text::Bold | sf::Text::Underlined);
    saveMessage.setCharacterSize(20);

}


void
LifeScreen::UnloadContent()
{

}


void
LifeScreen::Update(sf::RenderWindow& window, sf::Event event)
{

    switch(event.type)
    {


        case sf::Event::KeyPressed:
            if((!isExtinct || isStable) ^ (isExtinct || !isStable) ^ (!isExtinct || !isStable))
            {

                UpdateGeneration();
                isStable = IsStabe();
                /** Insere a nova geração no vetor de gerações */
                generations.push_back(mMatriz);

                isExtinct = IsExtinct();
                std::cout << "isStable = " << isStable << "isExtinct = "<< isExtinct << std::endl;
            }
            else
            {
                SavingGame();

            }
            break;
    }

}


void
LifeScreen::Draw(sf::RenderWindow& window)
{
    /** Print the grid on the screen */
	for( auto i(0); i < grid.size() ; ++i )
    {
        window.draw( grid[i]);
    }
    window.draw(mGameStatus);
    window.draw(textbox);
    window.draw(saveMessage);
}


void
LifeScreen::LoadConfig()
{
    //! Input stream do arquivo de entrada gravado na tela de configuracao .
    std::ifstream ifstreamConfig("config.txt");

    /** Usado para extrair dados da string lida do arquivo de entrada. */
    std::istringstream issstring;
    //std::string strLine;                   //! Armazena uma linha do arquivo de entrada.

     if(!ifstreamConfig.is_open())
    {
        /** Show message error */
        std::cout << "Erro opening file" << std::endl;
    }
    else
    {
        /** Read the filename */
        ifstreamConfig >> filename;
    }

    //! Input stream do arquivo de entrada.
    std::ifstream ifsIn("assets/data/" + filename);

    /** Usado para extrair dados da string lida do arquivo de entrada. */
    std::istringstream iss;
    std::string sLine;                   //! Armazena uma linha do arquivo de entrada.
    char cTemp;                     //! Char temporario para fazer o preencimento da matriz.

     if(!ifsIn.is_open())
    {
        /** Show message error */
        std::cout << "Erro opening file" << std::endl;
    }
    else
    {
        /** Read the number of rows ands cols */
        ifsIn >> nRows;
        ifsIn >> nCols;

        /** Lê o caractere usado como simbolo de celula viva */
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
LifeScreen::SetGridPosition()
{
    /** Set the position of the grid */
    gridPosition.x = (screenWidth  / 2) - ((nCols/2) * 20);
    gridPosition.y = (screenHeight / 2) - ((nRows/2) * 20);
    for ( auto i(0); i < nRows; ++i )
    {
        for ( auto j(0); j < nCols; ++j )
        {
            grid[ i * nCols + j ].setPosition(gridPosition);        // Seta a posição que sera imprimida na tela.
            gridPosition.x = gridPosition.x + 20.f;                 // Atualiza a cordenada do x
        }

        gridPosition.x = (screenWidth  / 2) - ((nCols/2) * 20);     // X volta a coordenada original a cada pulo de linha
        gridPosition.y = gridPosition.y + 20.f;                     // Atualiza a cordenada do x

    }
}


void
LifeScreen::LoadFilename()
{
    //! Input stream do arquivo de entrada.
    std::ifstream ifsIn("config.txt");

    /** Usado para extrair dados da string lida do arquivo de entrada. */
    std::istringstream iss;
    std::string sLine;                   //! Armazena uma linha do arquivo de entrada.

     if(!ifsIn.is_open())
    {
        /** Show message error */
        std::cout << "Erro opening file" << std::endl;
    }
    else
    {
        /** Read the number of rows ands cols */
        ifsIn >> filename;
        std::cout << filename << std::endl;
    }
}


void
LifeScreen::UpdateGeneration()
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
                    mMatrizAux[ linha * nCols + coluna ] = SetAlive(cellState, liveNeighbors, cLive);
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
                    mMatrizAux[ linha * nCols + coluna ] = SetAlive( cellState, liveNeighbors, cLive );
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
                    mMatrizAux[ linha * nCols + coluna ] = SetAlive( cellState, liveNeighbors, cLive );
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
                mMatrizAux[ linha * nCols + coluna ] = SetAlive( cellState, liveNeighbors, cLive );
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
                mMatrizAux[ linha * nCols + coluna ] = SetAlive( cellState, liveNeighbors, cLive );
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
                    mMatrizAux[ linha * nCols + coluna ] = SetAlive( cellState, liveNeighbors, cLive );
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
                    mMatrizAux[ linha * nCols + coluna ] = SetAlive( cellState, liveNeighbors, cLive );
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
                    mMatrizAux[ linha * nCols + coluna ] = SetAlive( cellState, liveNeighbors, cLive );
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
                mMatrizAux[ linha * nCols + coluna ] = SetAlive( cellState, liveNeighbors, cLive );
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
    UpdateGridSprites();

}


char
LifeScreen::SetAlive(char _cellState, int _liveNeighbors, char _cLive)
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
LifeScreen::UpdateGridSprites()
{
    for ( auto i(0); i < ( nRows * nCols ) ; ++i )
    {
        if ( mMatriz[ i ] == cLive )
            grid[ i ] = virusSprite;
        else
            grid[ i ] = emptyCellSprite;
    }
    SetGridPosition();
}


bool
LifeScreen::IsStabe()
{
    for( auto i(0); i < generations.size(); ++i )
    {
        std::cout << "Entrei dentro do is stabe" << generations.size() <<std::endl;
        if( CompareVectors(mMatriz, generations[i]))
        {
            mGameStatus.setString("Generation Estabilized!!!");
            mGameStatus.setPosition( (screenWidth / 2) - (mGameStatus.getGlobalBounds().width / 2) , screenHeight / 2 );
            mGameStatus.setColor(sf::Color::Red);
            return true;
        }
    }
    return false;
    /*
    if(numChanges == 0)
    {
        mGameStatus.setString("Generation Estabilized!!!");
        mGameStatus.setPosition( (screenWidth / 2) - (mGameStatus.getGlobalBounds().width / 2) , screenHeight / 2 );
        mGameStatus.setColor(sf::Color::Red);
        return true;
    }
    else
    {
        numChanges = 0;
        return false;
    }
    */
}


bool
LifeScreen::IsExtinct()
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
    mGameStatus.setColor(sf::Color::Blue);
    mGameStatus.setPosition( (screenWidth / 2) - (mGameStatus.getGlobalBounds().width / 2) , screenHeight / 2 );
    return isExtinct;
}


void
LifeScreen::SavingGame()
{
    textbox.setSize(sf::Vector2f(400,30));
    textbox.setPosition(sf::Vector2f((screenWidth / 2) - ( textbox.getGlobalBounds().width / 2) , 450));
    saveMessage.setString("Digite o nome do arquivo de saida e digite enter:");
    saveMessage.setPosition(sf::Vector2f((screenWidth / 2) - ( saveMessage.getGlobalBounds().width / 2) , 410));
}


bool
LifeScreen::CompareVectors(std::vector<char> _vectorA, std::vector<char> _vectorB)
{
    // Se o tamanho dos vetores forem iguais;
    if(_vectorA.size() == _vectorB.size())
    {
        for(auto i(0); i < _vectorA.size(); ++i )
        {
            // Se houver ao menos 1 elemento diferente o vetor será diferente.
            if(_vectorA[i] != _vectorB[i] )
                return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}
