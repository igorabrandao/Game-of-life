//! Life class functions implementation
/*! Implements the fucntions of The Game of Life
*/
#include "life.hpp"

using namespace std;

//! Class constructor */
Life::Life()
: mMatriz()
, mMatrizAux()
, nRows()
, nCols()
, cLive()
, numChanges(0)
{
    /* Empty */
}

//! Display welcome message */
void
Life::showInitialMensage()
{
    cout << "****************************************************************" << endl;
    cout << "  Welcome to Conway's Game of Life." << endl;
    cout << "  By defaut this game uses a grid of size 20 by 60 in which" << endl;
    cout << "  each cell can either be occupied by an organism or not." << endl;
    cout << "  the occupied cells change from generation to generation" << endl;
    cout << "  according to the number of neighboring cells which are alive." << endl;
    cout << "****************************************************************" << endl;
}

//! Starts the simulation itself */
void
Life::run()
{
    
    readFile();
    showInitialMensage();
    printGrid();
    update();
}

//! Function to read an input file
/*! _fileName -> the input file name
*/
void
Life::readFile()
{
    //! Input stream do arquivo de entrada.
    ifstream ifsIn(getFileName());    

    //! Usado para extrair dados da string lida do arquivo de entrada.
    istringstream iss;              
    string sLine;                   //! Armazena uma linha do arquivo de entrada.
    //int nRows, nCols;               //! Armazena o numero de linhas e colunas da matriz.
    //char cLive;                     //! Armazena o caracter que significa que a celula esta viva.
    char cTemp;                     //! Char temporario para fazer o preencimento da matriz.
    //vector<char> tempVector;        //! Vetor temporario para fazer o preenchimento da matriz.

    if(!ifsIn.is_open())
    {
        /* Show message error */
        std::cout << "Error opening file" << std::endl;

    }
    else
    {
        // Lẽ o numero de linhas e colunas.
        ifsIn >> nRows;
        ifsIn >> nCols;

        /* initial information message */
        cout << endl;
        cout << ">>>> Trying to open input file [texte.txt]... done!" << endl << endl;
        cout << ">>>> Processing data, please wait..." << endl;
        cout << ">>>> Grid size read from input file: " << nRows << " rows by " << nCols << " cols."<<endl;

        //Lê o caractere usado como simbolo de celula viva.
        ifsIn >> cLive;
        cout << ">>>> Character thar represents a living cell read from input file: " << cLive << endl;

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
Life::saveFile()
{
    std::ofstream ofs;
    std::ostringstream oss;

    ofs.open("out.txt");

    if(!ofs.is_open())
    {
        std::cout << "Error opening out.txt file!!!" << endl;
        std::cout << "Closing the program..." << endl;
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

int
Life::update()
{
    cout << "Estou dentro do update." << endl;
    int n;
    while(cin >> n)
    {
        cout << "Estou dentro do while do update" << endl;
        updateGeneration();
        printGrid();
        if (isExtinct() || isStabe())
        {
            saveFile();
            endGame();
        }
        cout << "Deseja continuar? (s/n): " << endl;
    }
    return EXIT_SUCCESS;
}

int
Life::endGame()
{
    std::cout << "\n>>>> A geração se tornou extinta ou estavel" << std::endl;
    std::cout << ">>>> Finalizando o jogo..." << std::endl;
    return EXIT_SUCCESS;
}

void
Life::printGrid()
{
    system("clear");
    for(auto i(0); i < nRows; ++i)
    {
        cout << "[";
        for(auto j(0); j < nCols; ++j)
        {
            if( mMatriz[ i * nCols + j ] == cLive )
                cout << mMatriz[i * nCols + j] << " ";
            else
                cout << "  ";
        }
        cout << "]";
        cout << endl;
    }
}

bool
Life::isStabe()
{
    if(numChanges == 0)
    {
        cout << "Essa bomba ficou estavel" << endl;
        return true;
    }
    else
    {
        cout << "Existiram " << numChanges << " mudancas na ultima geracao." << endl;
        cout << "A geracoes ainda nao são estaveis." << endl;
        numChanges = 0;
        return false;
    }
}

bool
Life::isExtinct()
{
    bool isExtinct = true;
    for(auto i(0); i < nCols * nRows; ++i)
    {
        if(mMatriz[i] == cLive)
        {
            cout << "não esta extinta" << endl;
            isExtinct = false;
            return  isExtinct;
        }
    }

    // Caso não exista nenhuma celula viva
    cout << "Eu morri carai" << endl;
    return isExtinct;
}

void
Life::updateGeneration()
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
}


char Life::setAlive(char _cellState, int _liveNeighbors, char _cLive)
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

