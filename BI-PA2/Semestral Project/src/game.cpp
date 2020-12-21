#include "game.hpp"

using namespace std;

Game::Game ( char **argv ) {
    paths.push_back ( argv[1] );
    paths.push_back ( argv[2] );
    paths.push_back ( argv[3] );
}

int Game::run () {
    parseMap ();
    parseQuest ();
    vector<vector<char>> x;
    string test;
    initGame ();

    screens[0] -> printAndRun ( mymap, screens, player );
    return 1;
}

void Game::parseMap () {
    ifstream mapFile;
    mapFile.open ( paths[0], ios::in );
    int x = 0, y = 0;
    char c;
    mapFile >> y >> x;
    mymap = make_shared<MapData> ( x, y );
    mymap -> setLoadPath ( paths[2] );
    x = 0;
    y = 0;
    mapFile.get(c);
    while ( mapFile.get(c) ) {
        if ( c == '\n' ) {
            x = 0;
            y++;
        }
        else {
            if ( c == '>' ) {
                mymap -> setPlayerPos ( x, y );
            }
            
            mymap -> changeMap ( x, y, c );
            x++;
        }
    }
    mapFile.close ();
}

void Game::parseQuest () {
    ifstream questFile;
    shared_ptr<QuestData> quest = mymap -> getQuestData ();
    questFile.open ( paths[1], ios::in );
    string qString;
    int killCount;
    while ( getline ( questFile, qString ) ) {
        quest -> setQuest ( qString );
        getline ( questFile, qString );
        quest -> setBrief ( qString );
        questFile >> killCount;
        questFile.get ();
        quest -> setKillCount ( killCount );
        getline ( questFile, qString );
        quest -> setReward ( qString );
    }
    
} 

void Game::initGame () {
    initscr ();
    cbreak ();
    noecho ();
    curs_set (0);
    keypad (stdscr, TRUE);
    start_color ();
    srand (time(NULL));
    init_pair (1, COLOR_RED, COLOR_BLACK);
    init_pair (3, COLOR_GREEN, COLOR_BLACK);
    init_pair (4, COLOR_YELLOW, COLOR_BLACK);
    screens.push_back ( shared_ptr<Controller> ( new StartScreen () ) );
    screens.push_back ( shared_ptr<Controller> ( new CreatePlayerScreen () ) );
    screens.push_back ( shared_ptr<Controller> ( new GameScreen () ) );
    screens.push_back ( shared_ptr<Controller> ( new LoadGameScreen () ) );
    screens.push_back ( shared_ptr<Controller> ( new SaveGameScreen () ) );
    player = make_shared<Player> ();
}