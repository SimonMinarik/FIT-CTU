#include "mapData.hpp"

void MapData::changeMap ( int x, int y, char symbol ) {
    myMap[y][x] = symbol;
}

void MapData::printMap () {
    for ( int i = 0; i < height; i++ ) {
            for ( int j = 0; j < width; j++ ) {
                if ( myMap[i][j] == 'e' || myMap[i][j] == 'b' || myMap[i][j] == 'h' || myMap[i][j] == 'g' ) {
                    specialChar ( j + 5, i + 2, myMap[i][j] );
                } else {
                mvaddch ( i + 2, j + 5, myMap[i][j] );
                    }
            }
        }
}

void MapData::specialChar ( int x, int y, char c ) {
    switch ( c ) {
    case 'e':
        attron(COLOR_PAIR(1));
        mvaddch(y, x, c);
        attroff(COLOR_PAIR(1));
        break;
    case 'b':
        attron(COLOR_PAIR(1));
        mvaddch(y, x, c);
        attroff(COLOR_PAIR(2));
        break;
    case 'h':
        attron(COLOR_PAIR(3));
        mvaddch(y, x, c);
        attroff(COLOR_PAIR(3));
        break;
    case 'g':
        attron(COLOR_PAIR(4));
        mvaddch(y, x, c);
        attroff(COLOR_PAIR(4));
        break;
    }
}

vector<vector<char>> MapData::getMap () const {
    return myMap;
}

void MapData::setPlayerPos ( int x, int y ) {
    playerPos = make_pair ( x, y );
}

pair <int, int> MapData::getPlayerPos () const {
    return playerPos;
}

void MapData::spawnEnemies ( int count ) {
    int numberOfEnemies = 0, x, y;
    while ( numberOfEnemies != count ) {
        x = rand () % width;
        y = rand () % height;
        if ( myMap[y][x] == '.' ) {
            myMap[y][x] = 'e';
            numberOfEnemies++;
        }
    }
}

void MapData::setHeight ( int x ) {
    height = x;
}

int MapData::getHeight () const {
    return height;
}

void MapData::setWidth ( int x ) {
    width = x;
}

int MapData::getWidth () const {
    return width;
}

shared_ptr<QuestData> MapData::getQuestData () const {
    return quest;
}

void MapData::setQuestData ( shared_ptr<QuestData> x ) {
    quest = x;
}

void MapData::setLoadPath ( string path ) {
    loadPath = path;
}

string MapData::getLoadPath () const {
    return loadPath;
}