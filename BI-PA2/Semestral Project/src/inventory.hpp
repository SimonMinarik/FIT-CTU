/**
 * @file inventory.hpp
 * @author Simon Minarik
 * @brief header file of Inventory class
 * @version 0.1
 * @date 2019-05-27
 * 
 * 
 */
#ifndef inventory
#define inventory

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <memory>
using namespace std;
/**
 * @brief class Inventory stores the number of items player's got in his inventory, and is able to get/set the items
 * 
 */
class Inventory {
    public:
    /**
     * @brief Construct a new Inventory object and push_backs zeros in order to initialize the number of items in the inventory
     * 
     */
    Inventory() {
        listOfItems.push_back(0);
        listOfItems.push_back(0);
    }
    /**
     * @brief adds the numberOf items of the indexOfItem-th item
     * 
     * @param indexOfItem index in the listOfItems vector
     * @param numberOf number of items to be added
     */
    void addItem ( int indexOfItem, int numberOf );
    /**
     * @brief getter method for returning the list of items player has
     * 
     * @return vector<int> 
     */
    vector<int> getItemList ();
    /**
     * @brief method, which is called when user wants to use an item in his inventory and it's effect are applied and the count decreased
     * 
     * @param indexOfItem 
     */
    void useItem ( int indexOfItem );

    protected:
    vector<int> listOfItems; 
};

#endif // inventory