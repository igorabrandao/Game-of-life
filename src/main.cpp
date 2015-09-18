#include <iostream>
#include <vector>
#include "life.hpp"

using namespace std;

//! Main (receive the fileName argument from command line)
/*! The program starts here!
*/
int main( int argc, char* argv[] )
{
	//! Check the arguments */
	if ( argc < 2 )
	{
		// Inform how to use the program
		cout << endl << "****************************************************************" << endl;
        cout << endl << "Use: life <input_cfg_file> [<output_cfg_evolution_file>]" << endl;
        cout << endl << "****************************************************************" << endl << endl;

        //! Program's earlier end */
        return 0;
    }
    else
    {
		//! Life class instance */
	    Life life;

	    //! Set the file name */
	    life.setFileName(argv[1]);

	    //! Start the simulation */
	    life.run();
    }

    //! Program's end */
    return 0;
}