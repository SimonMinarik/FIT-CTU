#include "player.hpp"

void Player::move ( shared_ptr<MapData> map, int direction ) {
    vector<vector<char>> x;
    x = map -> getMap ();
    pair <int, int> playerPos = map -> getPlayerPos ();
    switch ( direction )
    {
    case 1:
        if ( x[playerPos.second][playerPos.first - 1] == 'Q' ) {
            collision ( map, x[playerPos.second][playerPos.first - 1] );
        } else if ( x[playerPos.second][playerPos.first - 1] != '#' ) {
                collision ( map, x[playerPos.second][playerPos.first - 1] );
                map -> changeMap ( playerPos.first, playerPos.second, '.' );
                map -> setPlayerPos ( playerPos.first - 1, playerPos.second );
                map -> changeMap ( playerPos.first - 1, playerPos.second, '<' );
            }
        break;
    case 2:
        if ( x[playerPos.second + 1][playerPos.first] == 'Q' ) {
            collision ( map, x[playerPos.second + 1][playerPos.first] );
        } else if ( x[playerPos.second + 1][playerPos.first] != '#' ) {
                collision ( map, x[playerPos.second + 1][playerPos.first] );
                map -> changeMap ( playerPos.first, playerPos.second, '.' );
                map -> setPlayerPos ( playerPos.first, playerPos.second + 1 );
                map -> changeMap ( playerPos.first, playerPos.second + 1, 'v' );
        }
        break;
    case 3:
        if ( x[playerPos.second - 1][playerPos.first] == 'Q' ) {
            collision ( map, x[playerPos.second - 1][playerPos.first] );
        } else if ( x[playerPos.second - 1][playerPos.first] != '#' ) {
                collision ( map, x[playerPos.second - 1][playerPos.first] );
                map -> changeMap ( playerPos.first, playerPos.second, '.' );
                map -> setPlayerPos ( playerPos.first, playerPos.second - 1 );
                map -> changeMap ( playerPos.first, playerPos.second - 1, '^' );
        }
        break;
    case 4:
        if ( x[playerPos.second][playerPos.first + 1] == 'Q' ) {
            collision ( map, x[playerPos.second][playerPos.first + 1] );
        } else if ( x[playerPos.second][playerPos.first + 1] != '#' ) {
                collision ( map, x[playerPos.second][playerPos.first + 1] );
                map -> changeMap ( playerPos.first, playerPos.second, '.' );
                map -> setPlayerPos ( playerPos.first + 1, playerPos.second );
                map -> changeMap ( playerPos.first + 1, playerPos.second, '>' );
        }
        break;
    }
}

void Player::collision ( shared_ptr<MapData> map, char c ) {
    shared_ptr<QuestData> quest = map -> getQuestData ();
    switch ( c ) {
    case 'b':
        health += ( defense - 32 );
        break;
    case 'h':
        inv -> addItem ( 0, 1 );
        break;
    case 'e':
        health += ( defense - ( 35 + ( rand() % 4 ) ) );
        experience += 6;
        quest -> changeKillCount ( quest -> getCurrentQuestIndex (), quest -> getKillCount ( quest -> getCurrentQuestIndex () ) - 1 );
        map -> setQuestData ( quest );
        break;
    case 'g':
        inv -> addItem ( 1, 1 );
        break;
    case 'Q':
        if ( quest -> getDone () && quest -> getCurrentQuestIndex () != quest -> getSize () - 1 ) {
        quest -> setCurrentQuest ( (quest -> getCurrentQuestIndex ()) + 1 );
        quest -> setDone ( false );
        map -> spawnEnemies ( quest -> getKillCount ( quest -> getCurrentQuestIndex () ) );
        }
        break;
    }
}

void Player::setName ( string x ) {
    name = x;
}

string Player::getName () const {
    return name;
}

void Player::setHealth ( int x ) {
    health = x;
}

int Player::getHealth () const {
    return health;
}

void Player::setAttack ( int x ) {
    attack = x;
}

int Player::getAttack () const {
    return attack;
}

void Player::setDefense ( int x ) {
    defense = x;
}

int Player::getDefense () const {
    return defense;
}

void Player::setExp ( int x ) {
    experience = x;
}

int Player::getExp () const {
    return experience;
}

void Player::setInv ( shared_ptr<Inventory> x ) {
    inv = x;
}

shared_ptr<Inventory> Player::getInv () const {
    return inv;
}

void Player::addReward ( int healthPack, int goldenStatue, int expe ) {
    inv -> addItem ( 0, healthPack );
    inv -> addItem ( 1, goldenStatue );
    experience += experience;
}