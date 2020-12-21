#include <iostream>
#include <curses.h> 
#include <fstream>
#include "game.hpp"

using namespace std;

int main ( int argc, char **argv ) {
    try {
    if ( argc != 4 )
        throw runtime_error("Hint: make run MAP=examples/map.txt QUESTS=examples/quests.txt SAVES=examples/Saves/");
    }
    catch (runtime_error e)
    {
        cout << e.what() << endl;
        return 1;
    }
    
    fstream mapFile (argv[1]);
    fstream questsFile (argv[2]);
    try {
    if ( ( ! mapFile.good () || ! questsFile.good () || strncmp ( argv[1], "examples/map.txt", 19 ) || strncmp ( argv[2], "examples/quests.txt", 22 ) ) && ( strncmp ( argv[3], "examples/Saves/", 16 ) || strncmp ( argv[3], "./examples/Saves", 17 ) ) )
        throw runtime_error("An error occured.. check if the files/arguments are okay");
    }
    catch (runtime_error e)
    {
        cout << e.what() << endl;
        return 1;
    }
    mapFile.close ();
    questsFile.close ();

    auto newGame = make_shared<Game>( argv );
    newGame -> run();
    return 0;
}