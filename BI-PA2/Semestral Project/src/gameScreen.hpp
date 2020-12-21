/**
 * @file gameScreen.hpp
 * @author Simon Minarik
 * @brief header file of the GameScreen class
 * @version 0.1
 * @date 2019-05-27
 * 
 * 
 */
#ifndef game_screen
#define game_screen

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <memory>
#include "controller.hpp"
#include "./mapData.hpp"

/**
 * @brief derived class from Controller. It is the "heart" of the operation, because it prints the game screen and controls user's input (moving
 * on the map, using the items from his inventory)
 * 
 */
class GameScreen : public Controller {
    public:
    /**
     * @brief method used for printing and controlling the gameplay
     * 
     * @param map is a shared_ptr of class MapData, which stores the data needed for running the game
     * @param screens is a vector of shared_ptr of Controller base class, and it stores every screen needed for printing and controlling
     * @param player is a shared_ptr of class Player, which stores data of the player, his experience, inventory etc.
     */
    void printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) override;
    /**
     * @brief a goodbye message is printed when user decides to exit the game
     * 
     */
    void byeBye () const;
    /**
     * @brief method used to print player's inventory
     * 
     */
    void printInventory ( shared_ptr<MapData> map, shared_ptr<Player> player, vector<int> items ) const;
    /**
     * @brief method used to print the current active quest (or a message prompting the player to start a new quest)
     * 
     */
    void printQuest ( shared_ptr<MapData> map, shared_ptr<Player> player );
    /**
     * @brief method used to print the reward user gets upon finishing the given quest
     * 
     */
    void printReward ( shared_ptr<MapData> map, shared_ptr<Player> player, shared_ptr<QuestData> quest );
    /**
     * @brief death message is printed and the game is exited
     * 
     */
    void death () const;
    protected:
    int shownReward = 0;
    bool saved = false;
};

#endif // game_screen