//! Life class
/*! Implements the structure to the life game
*/
#ifndef LIFE_HPP
#define LIFE_HPP

//! Includes */
#include <iostream> //! std::cout
#include <vector>   //! std::vector
#include <fstream>  //! std::ifstream, std::ofstream
#include <sstream>  //! std::istringstream, std::ostringstream
#include <string>   //! std::string

class Life
{
    //! Public members */
    public:
                Life();

        void    readFile();
        void    saveFile();
        void    printGrid();
        void    showInitialMensage();
        void    run();
        int     update();
        bool    isStabe();
        bool    isExtinct();
        void    updateGeneration();
        char    setAlive(char _cellState, int _liveNeighbors, char _cLive);
        int     endGame();

    private:
        std::vector<char>   mMatriz;
        std::vector<char>   mMatrizAux;
        int                 nRows;
        int                 nCols;
        char                cLive;
        int                 numChanges;
};

#endif // LIFE_HPP
