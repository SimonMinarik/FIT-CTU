/**
 * @file createPlayerScreen.hpp
 * @author Simon Minarik
 * @brief Header file of CreatePlayerScreen derived class (from Controller)
 * @version 0.1
 * @date 2019-05-27
 * 
 * 
 */

#ifndef create_player_screen
#define create_player_screen
#include <iostream>
#include <ncurses.h>
#include <vector>
#include <memory>
#include "controller.hpp"
#include "./mapData.hpp"
/**
 * @brief derived class from Controller, which takes care of creating the player (input handling, printing)
 * 
 */
class CreatePlayerScreen : public Controller {
    public:
    /**
     * @brief printAndRun method takes care of printing screens needed to create new player and controls user's input
     * 
     * @param map is a shared_ptr of class MapData, which stores the data needed for running the game
     * @param screens is a vector of shared_ptr of Controller base class, and it stores every screen needed for printing and controlling
     * @param player is a shared_ptr of class Player, which stores data of the player, his experience, inventory etc.
     */
    void printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) override;

    /**
     * @brief sets players attributes ( health, attack, defense )
     * 
     */
    void setAttributes ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player );
    protected:
    
};

#endif // create_player_screen