#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"

using namespace std;

int main()
{
    try {
        Game app;
        app.run();
    } catch (const char* e ) {
        cerr << "Erro :" << e << endl;
    }

    return EXIT_SUCCESS;
}
