/**
 * @file loadGameScreen.hpp
 * @author Simon Minarik
 * @brief header file of LoadGameScreen class
 * @version 0.1
 * @date 2019-05-27
 * 
 * 
 */
#ifndef load_game_screen
#define load_game_screen

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <dirent.h>
#include <ncurses.h>
#include <string>
#include <string.h>
#include "controller.hpp"
#include "./mapData.hpp"

using namespace std;
/**
 * @brief derived method from Controller, used for printing and controlling the screen, when user wants to load a saved game and parsing
 * the chosen saved file in order to run the game
 * 
 */
class LoadGameScreen : public Controller {
    public:
    /**
     * @brief method for printing and controlling the load game screen 
     * 
     * @param map is a shared_ptr of class MapData, which stores the data needed for running the game
     * @param screens is a vector of shared_ptr of Controller base class, and it stores every screen needed for printing and controlling
     * @param player is a shared_ptr of class Player, which stores data of the player, his experience, inventory etc.
     */
    void printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) override;
    /**
     * @brief prints a menu from user can choose which game he wants to load
     * 
     * @param savedFiles vector of strings - filenames in the Saves directory
     */
    void printFiles ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player, vector<string> savedFiles );
    /**
     * @brief method for parsing the saved game file
     * 
     * @param fileName name of the file user choose to load
     */
    void parseSavedData ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player, string fileName );
    protected:

};

#endif // load_game_screen