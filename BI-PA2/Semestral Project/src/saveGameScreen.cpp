#include "saveGameScreen.hpp"

void SaveGameScreen::printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) {
    clear ();
    vector<vector<char>> myMap = map -> getMap ();
    string fileName = map -> getLoadPath ();
    fileName += player -> getName ();
    ofstream saveFile ( fileName );
    saveFile << map -> getHeight () << " " << map -> getWidth () << endl;
    for ( int i = 0; i < map -> getHeight (); i++ ) {
        for ( int j = 0; j < map -> getWidth (); j++ ) {
            saveFile << myMap[i][j];
        }
        saveFile << endl;
    }
    saveFile << player -> getName () << endl;
    saveFile << player -> getHealth () << " " << player -> getAttack () << " " << player -> getDefense () << endl;
    shared_ptr<Inventory> inv = player -> getInv ();
    vector<int> invItems = inv -> getItemList ();
    saveFile << invItems[0] << " " << invItems[1] << " " << player -> getExp () << endl;

    shared_ptr<QuestData> quest = map -> getQuestData ();
    saveFile << quest -> getCurrentQuestIndex () << " " << quest -> getKillCount ( quest -> getCurrentQuestIndex () ) << " " << quest -> getDone ();
    saveFile.close ();

    mvprintw ( 0, 6, "---- %s ----", "SAVE" );
    mvprintw ( 5, 6, "-----====-----" );
    mvprintw ( 2, 0, "...your game has been saved..." );
    mvprintw ( 3, 5, "Thanks for playing!" );
    getch ();
    endwin ();
}