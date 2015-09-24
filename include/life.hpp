//! Life class
/*! Implements the structure of The Game of Life
*/
#ifndef LIFE_HPP
#define LIFE_HPP

//! Includes */
#include <iostream> //! std::cout
#include <vector>   //! std::vector
#include <fstream>  //! std::ifstream, std::ofstream
#include <sstream>  //! std::istringstream, std::ostringstream
#include <string>   //! std::string

using namespace std;

class Life
{
    //! Public members */
    public:

        //! Class constructor */
        Life();

        //! Display welcome message */
        void showInitialMensage();

        //! Starts the simulation itself */
        void run();

        //! Function to read an input file
        /*! _fileName -> the input file name
        */
        void    readFile();

        //! Get's and set's */
        string  getFileName() const { return fileName; } 
        void    setFileName( const string& _fileName ) { fileName = _fileName; } 

        void    saveFile();
        void    printGrid();
        int     update();
        bool    isStabe();
        bool    isExtinct();
        void    updateGeneration();
        char    setAlive(char _cellState, int _liveNeighbors, char _cLive);
        int     endGame();

    private:
        vector<char>    mMatriz;
        vector<char>    mMatrizAux;
        string          fileName;
        int             nRows;
        int             nCols;
        char            cLive;
        int             numChanges;
};

#endif // LIFE_HPP