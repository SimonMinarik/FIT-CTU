/**
 * @file mapData.hpp
 * @author Simon Minarik
 * @brief header file of MapData class
 * @version 0.1
 * @date 2019-05-27
 * 
 * 
 */
#ifndef map_data
#define map_data
#include <iostream>
#include <ncurses.h>
#include <string>
#include <memory>
#include <vector>
#include "./questData.hpp"

using namespace std;
/**
 * @brief class MapData is used to store every information about the map - position of player, how the map looks, where are the enemies
 * 
 */
class MapData {
    public:
    /**
     * @brief Construct a new Map Data object and initializes 3d vector of chars for storing the map and initializes shared_ptr of QuestData
     * 
     * @param x width of the map
     * @param y height of the map
     */
    MapData ( int x, int y ) {
        myMap.resize(y);
        for ( int i = 0; i < y; i++ ) {
            myMap[i].resize (x);
        }
        height = y;
        width = x;
        quest = make_shared<QuestData> ();
    }
    /**
     * @brief changes symbol on the [y][x] coordinations in map vector
     * 
     */
    void changeMap ( int x, int y, char symbol );
    /**
     * @brief prints out the map
     * 
     */
    void printMap ();
    /**
     * @brief changes color of any special character - enemy, bomb, healthpacks and golden statues
     * 
     */
    void specialChar ( int x, int y, char c );
    /**
     * @brief getter of the map vector
     * 
     * @return vector<vector<char>> 
     */
    vector<vector<char>> getMap () const;
    /**
     * @brief setter of player position
     * 
     */
    void setPlayerPos ( int x, int y );
    /**
     * @brief Getter of player position
     * 
     */
    pair <int, int> getPlayerPos () const;
    /**
     * @brief spawns count of enemies on the map
     * 
     */
    void spawnEnemies ( int count );
    /**
     * @brief getter of map height
     * 
     * @return int 
     */
    int getHeight () const;
    /**
     * @brief setter of map height
     * 
     */
    void setHeight ( int x );
    /**
     * @brief getter of map width
     * 
     * @return int 
     */
    int getWidth () const;
    /**
     * @brief setter of map width
     * 
     */
    void setWidth ( int x );
    /**
     * @brief getter of quest data shared_ptr
     * 
     * @return shared_ptr<QuestData> 
     */
    shared_ptr<QuestData> getQuestData () const;
    /**
     * @brief setter of quest data
     * 
     */
    void setQuestData ( shared_ptr<QuestData> x );
    /**
     * @brief setter of path from which the saved files will be read
     * 
     */
    void setLoadPath ( string path );
    /**
     * @brief getter of path from which the saved files will be read
     * 
     * @return string 
     */
    string getLoadPath () const;
    protected:
    int height;
    int width;
    string welcomeText;
    vector<vector<char>> myMap;
    pair <int, int> playerPos;
    shared_ptr<QuestData> quest;
    string loadPath;
};

#endif // map_data