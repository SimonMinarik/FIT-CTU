/**
 * @file startScreen.hpp
 * @author Simon Minarik
 * @brief header file of StartScreen class
 * @version 0.1
 * @date 2019-05-27
 * 
 * 
 */
#ifndef start_screen
#define start_screen

#include <iostream>
#include <ncurses.h>
#include <memory>
#include "controller.hpp"
#include "./mapData.hpp"

using namespace std;
/**
 * @brief class StartScreen is derived from Controller class and handels printing the main menu and controls user input
 * 
 */
class StartScreen : public Controller {
    public:
    /**
     * @brief prints the main menu and handles users input (moving through the menu items)
     * 
     * @param map is a shared_ptr of class MapData, which stores the data needed for running the game
     * @param screens is a vector of shared_ptr of Controller base class, and it stores every screen needed for printing and controlling
     * @param player is a shared_ptr of class Player, which stores data of the player, his experience, inventory etc.
     */
    void printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) override;
    /**
     * @brief based on the item user chose from the menu, controller method calls for the screen needed to continue
     * 
     * @param x index of item user chose
     */
    void controller ( int x, shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player );
    /**
     * @brief prints a goodbye message if user chooses to exit the game
     * 
     */
    void byeBye () const;
    /**
     * @brief prints basic information about the game, the different controls and how to play
     * 
     */
    void about ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player );

    protected:

};

#endif // start_screen