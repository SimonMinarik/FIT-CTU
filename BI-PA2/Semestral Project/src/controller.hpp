/**
 * @file controller.hpp
 * @author Simon Minarik
 * @brief Header file for base class Controller
 * @version 0.1
 * @date 2019-05-27
 * 
 * 
 */

#ifndef controller_d
#define controller_d

#include <iostream>
#include <ncurses.h>
#include <memory>
#include "./mapData.hpp"
#include "./player.hpp"

using namespace std;
/**
 * @brief base class, from which other classes are derived and use method printAndRun
 * 
 */
class Controller {
    public:
    /**
     * @brief Construct a new Controller object
     * 
     */
    Controller () {
    }
    /**
     * @brief Destroy the Controller object
     * 
     */
    virtual ~Controller () {
    }
    /**
     * @brief printAndRun function is a virtual function passed to the derived classes. It's purpose is to print the current screen and control user input
     * 
     * @param map is a shared_ptr of class MapData, which stores the data needed for running the game
     * @param screens is a vector of shared_ptr of Controller base class, and it stores every screen needed for printing and controlling
     * @param player is a shared_ptr of class Player, which stores data of the player, his experience, inventory etc.
     */
    virtual void printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) = 0;
    protected:
};

#endif // controller_d