#include "inventory.hpp"

void Inventory::addItem ( int indexOfItem, int numberOf ) {
    listOfItems[indexOfItem] += numberOf;
}

void Inventory::useItem ( int indexOfItem ) {
    listOfItems[indexOfItem]--;
}

vector<int> Inventory::getItemList () {
    return listOfItems;
}