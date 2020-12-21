#include "loadGameScreen.hpp"

void LoadGameScreen::printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) {
    clear ();
    string fileName;
    vector<string> savedFiles;
    mvprintw ( 0, 6, "---- %s ----", "LOAD" );
    DIR *dir;
    int i = 0;
    struct dirent *ent;

    if ( (dir = opendir ( (map -> getLoadPath ()).c_str () )) != NULL ) {
        while ( (ent = readdir ( dir )) != NULL ) {
            if ( ! ( ! strcmp(ent -> d_name, ".") || ! strcmp(ent -> d_name, "..") ) ) {
                i++;
                fileName = ent -> d_name;
                savedFiles.push_back ( fileName );
            }
        }
    }
    closedir (dir);

    if ( ! savedFiles.size () ) {
    mvprintw ( 0, 6, "---- %s ----", "LOAD" );
    mvprintw ( 3, 0, "There are no saved games to by loaded" );
    mvprintw ( 6, 6, "-----====-----" );
    getch ();
    screens[0] -> printAndRun ( map, screens, player );
    } else {
        mvprintw ( 3 + i, 6, "-----====-----" );
        printFiles ( map, screens, player, savedFiles );
    }
}

void LoadGameScreen::printFiles ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player, vector<string> savedFiles ) {
    char item[27];
    for ( size_t i = 0; i < savedFiles.size (); i++ ) {
        if ( ! i ) {
            attron ( A_STANDOUT );
        } else
            attroff ( A_STANDOUT );
            sprintf (item, "%s",  savedFiles[i].c_str ());
            mvprintw ( i + 2, 7, "%s", item );
    }
    int ch;
    size_t i = 0;
    while ( (ch = getch()) != 10 ) {
        sprintf ( item, "%s", savedFiles[i].c_str () ); 
        mvprintw ( i + 2, 7, "%s", item );
        switch ( ch ) {
        case KEY_UP:
            i--;
            i = ( i < 0 ) ? savedFiles.size () - 1 : i;
            break;
        case KEY_DOWN:
            i++;
            i = ( i > savedFiles.size () - 1 ) ? 0 : i;
            break;
        }
        attron ( A_STANDOUT );
             
        sprintf ( item, "%s",  savedFiles[i].c_str () );
        mvprintw ( i+2, 7, "%s", item );
        attroff ( A_STANDOUT );
    }
    parseSavedData ( map, screens, player, savedFiles[i] );
}

void LoadGameScreen::parseSavedData ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player, string fileName ) {
    clear ();
    endwin ();
    string path = map -> getLoadPath ();
    path += fileName;
    ifstream savedGame;
    savedGame.open ( path, ios::in );
    int x, y;
    char c;
    savedGame >> y >> x;
    map -> setHeight ( y );
    map -> setWidth ( x );
    savedGame.get ();
    for ( int i = 0; i < map -> getHeight (); i++ ) {
        for ( int j = 0; j < map -> getWidth (); j++ ) {
            savedGame.get ( c );
            map -> changeMap ( j, i, c );
            if ( c == '>' || c == '<' || c == 'v' || c == '^' ) {
                map -> setPlayerPos ( j, i );
            }
        }
        savedGame.get ();
    }
    string name;
    getline ( savedGame, name );
    player = make_shared<Player> ();
    player -> setName ( name );

    int health, attack, defense;
    savedGame >> health >> attack >> defense;
    player -> setHealth ( health );
    player -> setAttack ( attack );
    player -> setDefense ( defense );
    savedGame.get ();

    int healthPacks, goldenStatues, experience;
    savedGame >> healthPacks >> goldenStatues >> experience;
    shared_ptr<Inventory> inv = make_shared<Inventory> ();
    inv -> addItem ( 0, healthPacks );
    inv -> addItem ( 1, goldenStatues );
    player -> setInv ( inv );
    player -> setExp ( experience );
    savedGame.get ();

    shared_ptr<QuestData> quest = map -> getQuestData ();
    int questIndex, killCount, isDone;
    savedGame >> questIndex >> killCount >> isDone;
    quest -> setCurrentQuest ( questIndex );
    quest -> changeKillCount ( questIndex, killCount );
    quest -> setDone ( isDone );
    map -> setQuestData ( quest );

    savedGame.close ();
    screens[2] -> printAndRun ( map, screens, player );
}