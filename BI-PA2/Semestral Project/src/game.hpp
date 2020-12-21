/**
 * @file game.hpp
 * @author Simon Minarik
 * @brief header file for of Game class
 * @version 0.1
 * @date 2019-05-27
 * 
 * 
 */
#ifndef game
#define game

#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <utility>
#include <memory>
#include "./mapData.hpp"
#include "./player.hpp"

#include "./startScreen.hpp"
#include "./createPlayerScreen.hpp"
#include "./gameScreen.hpp"
#include "./loadGameScreen.hpp"
#include "./saveGameScreen.hpp"

using namespace std;
/**
 * @brief a class through which the game is started. Everything is stored in protected and passed to the other methods for printing/setting/getting
 * 
 */
class Game {
    public:
    /**
     * @brief Construct a new Game object and push_backs the arguments into a vector
     * 
     * @param argv - arguments with path names and file names
     */
    Game ( char **argv );
    /**
     * @brief Destroy the Game object
     * 
     */
    ~Game () {
    }
    /**
     * @brief starts the game, initializes everything needed
     * 
     */
    int run ();
    /**
     * @brief parses map data from a file into the MapData class
     * 
     */
    void parseMap ();
    /**
     * @brief parses quest data from a file into the QuestData class
     * 
     */
    void parseQuest ();
    /**
     * @brief initializes ncurses, sets color_pairs
     * 
     */
    void initGame ();

    protected:
    shared_ptr <MapData> mymap;
    vector <shared_ptr<Controller>> screens;
    shared_ptr <Player> player;
    vector <string> paths;
};

#endif // game