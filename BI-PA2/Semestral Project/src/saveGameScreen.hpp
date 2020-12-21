/**
 * @file saveGameScreen.hpp
 * @author Simon Minarik
 * @brief header file of SaveGameScreen class
 * @version 0.1
 * @date 2019-05-27
 * 
 * 
 */
#ifndef save_game_screen
#define save_game_screen

#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <vector>
#include <memory>
#include "controller.hpp"
#include "./mapData.hpp"
/**
 * @brief class SaveGameScreen handles printing the save game screen and saving the game itself
 * 
 */
class SaveGameScreen : public Controller {
    public:
    /**
     * @brief prints the save game screen and saves the game into a file named after the player
     * 
     * @param map is a shared_ptr of class MapData, which stores the data needed for running the game
     * @param screens is a vector of shared_ptr of Controller base class, and it stores every screen needed for printing and controlling
     * @param player is a shared_ptr of class Player, which stores data of the player, his experience, inventory etc.
     */
    void printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) override;
    protected:
};

#endif // save_game_screen