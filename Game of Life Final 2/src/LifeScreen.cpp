#include "LifeScreen.h"

const sf::Time LifeScreen::TimePerFrame = sf::seconds(0.5f);
const sf::Time LifeScreen::TimePerFrameNormal = sf::seconds(1);

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

    outputFilename.setFont(font);
    outputFilename.setString("");
    outputFilename.setColor(sf::Color::Black);
    outputFilename.setCharacterSize(20);


    timeSinceLastUpdate = sf::Time::Zero;
    timeSinceLastUpdateNormal = sf::Time::Zero;
}


void
LifeScreen::UnloadContent()
{

}


void
LifeScreen::Update(sf::RenderWindow& window, sf::Event event)
{
    window.setKeyRepeatEnabled(false);
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    timeSinceLastUpdateNormal = timeSinceLastUpdate;
    if((!isExtinct || isStable) ^ (isExtinct || !isStable) ^ (!isExtinct || !isStable))
    {
        while( timeSinceLastUpdate > TimePerFrame )
        {
            timeSinceLastUpdate -= TimePerFrame;
            if(timeSinceLastUpdate.asSeconds() < TimePerFrame.asSeconds() )
            {
                UpdateGeneration();
                isStable = IsStabe();
                isExtinct = IsExtinct();
                /** Insere a nova geração no vetor de gerações */
                generations.push_back(mMatriz);
            }
                std::cout << timeSinceLastUpdate.asSeconds() << std::endl;
        }
    }
    else
    {
        SavingGame();

        switch(event.type)
        {
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    tempString += 'a';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
                    tempString += 'b';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                    tempString += 'c';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    tempString += 'd';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                    tempString += 'e';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                    tempString += 'f';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
                    tempString += 'g';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
                    tempString += 'h';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                    tempString += 'i';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
                    tempString += 'j';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
                    tempString += 'k';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                    tempString += 'l';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                    tempString += 'm';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
                    tempString += 'n';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                    tempString += 'o';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                    tempString += 'p';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                    tempString += 'q';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                    tempString += 'r';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    tempString += 's';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
                    tempString += 't';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
                    tempString += 'u';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
                    tempString += 'v';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    tempString += 'w';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
                    tempString += 'x';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
                    tempString += 'y';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                    tempString += 'z';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
                    tempString += '.';
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                {
                    if( tempString.length() > 0)
                        tempString = tempString.substr(0, tempString.length() - 1 );
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    SaveOutputFile(window);
                    window.close();
                }
                break;
        }
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
    window.draw(outputFilename);
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
    outputFilename.setString(tempString);
    outputFilename.setPosition(sf::Vector2f((screenWidth / 2) - ( outputFilename.getGlobalBounds().width / 2) , 450));

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


void
LifeScreen::SaveOutputFile(sf::RenderWindow& window)
{
    std::ofstream ofs;
    std::ostringstream oss;

    std::string localFile = "assets/data/" + tempString;

    ofs.open(localFile);

    if(!ofs.is_open())
    {
        std::cout << "Error opening out.txt file!!!" << std::endl;
        std::cout << "Closing the program..." << std::endl;
        window.close();
    }
    else
    {
        std::cout << ">>>> Saving file..." << std::endl;

        oss << nRows << " " << nCols << "\n";
        oss << cLive << "\n";

        for( auto i(0); i < nRows; ++i )
        {
            for( auto j(0); j < nCols; ++j)
            {
                oss << mMatriz[ i * nCols + j ];
            }
            oss << "\n";
        }

        std::string s = oss.str();

        ofs << s;
        std::cout << "Output operation successfully performed\n";
        ofs.close();
    }
}
