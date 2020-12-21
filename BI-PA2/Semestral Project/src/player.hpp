/**
 * @file player.hpp
 * @author Simon Minarik
 * @brief header file of Player class
 * @version 0.1
 * @date 2019-05-27
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef player_d
#define player_d

#include <iostream>
#include <ncurses.h>
#include <string>
#include <memory>
#include "./inventory.hpp"
#include "./mapData.hpp"

using namespace std;
/**
 * @brief Player class stores information about the player (his name, inventory, experience)
 * 
 */
class Player {
    public:
    /**
     * @brief Construct a new Player object, initialize inventory
     * 
     */
    Player ( ) : experience ( 0 ) {
        inv = make_shared<Inventory> ();
    }
    /**
     * @brief moves the player on the map according to the pressed arrow key
     * 
     * @param map shared_ptr of class MapData, which stores the information about the map
     * @param direction direction in which the player wants to move (predefined values)
     */
    void move ( shared_ptr<MapData> map, int direction );
    /**
     * @brief checks for collision with special characters (items, enemies/bombs, questbook)
     * 
     */
    void collision ( shared_ptr<MapData> map, char c );
    /**
     * @brief setter of player's name
     * 
     */
    void setName ( string x );
    /**
     * @brief getter of player's name
     * 
     * @return string 
     */
    string getName () const;
    /**
     * @brief setter of player's health
     * 
     */
    void setHealth ( int x );
    /**
     * @brief getter of player's health
     * 
     * @return int 
     */
    int getHealth () const;
    /**
     * @brief setter of player's attack
     * 
     */
    void setAttack ( int x );
    /**
     * @brief getter of player's attack
     * 
     * @return int 
     */
    int getAttack () const;
    /**
     * @brief setter of player's defense
     * 
     */
    void setDefense ( int x );
    /**
     * @brief getter of player's defense
     * 
     * @return int 
     */
    int getDefense () const;
    /**
     * @brief setter of player's experience
     * 
     */
    void setExp ( int x );
    /**
     * @brief getter of players experience
     * 
     * @return int 
     */
    int getExp () const;
    /**
     * @brief setter of players inventory
     * 
     */
    void setInv ( shared_ptr<Inventory> x );
    /**
     * @brief getter of players inventory
     * 
     * @return shared_ptr<Inventory> 
     */
    shared_ptr<Inventory> getInv () const;
    /**
     * @brief adds rewards gotten from finished quests
     * 
     * @param healthPack number of healthpacks added
     * @param goldenStatue number of goldenstatues added
     * @param expe number of experience points added
     */
    void addReward ( int healthPack, int goldenStatue, int expe );
    protected:
    string name;
    int health;
    int attack;
    int defense;
    int experience;
    shared_ptr<Inventory> inv;
};

#endif // player_d