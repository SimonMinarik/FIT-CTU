#include "startScreen.hpp"

void StartScreen::printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) {
    erase ();
    char list[4][10] = { "New Game", "Load Game", "About", "Quit" };
    char item[10];
    mvprintw ( 0, 5, "---- %s ----", "RPG" );
    mvprintw ( 5, 5, "-----===-----" );
    for ( int i = 0; i < 4; i++ ) {
        if ( ! i ) {
            attron ( A_STANDOUT );
        } else
            attroff ( A_STANDOUT );
            sprintf (item, "%-9s",  list[i]);
            mvprintw ( i + 1, 7, "%s", item );
    }
    int ch, i = 0;
    while ( (ch = getch()) != 10 ) {
        sprintf ( item, "%-9s", list[i] ); 
        mvprintw ( i + 1, 7, "%s", item );
        switch ( ch ) {
        case KEY_UP:
            i--;
            i = ( i < 0 ) ? 3 : i;
            break;
        case KEY_DOWN:
            i++;
            i = ( i > 3 ) ? 0 : i;
            break;
        }
        attron ( A_STANDOUT );
             
        sprintf ( item, "%-9s",  list[i] );
        mvprintw ( i+1, 7, "%s", item );
        attroff ( A_STANDOUT );
    }
    controller ( i, map, screens, player );
}

void StartScreen::byeBye () const {
    clear ();
    mvprintw ( 0, 6, "---- %s ----", "BYE" );
    mvprintw ( 6, 6, "-----===-----" );
    mvprintw ( 3, 0, "Thank you for playing, bye!" );
    getch();
    endwin ();
}

void StartScreen::about ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) {
    clear ();
    mvprintw ( 0, 12, "---- %s ----", "ABOUT" );
    mvprintw ( 1, 0, "Welcome to the `ALMOST` perfect RPG engine." );
    mvprintw ( 3, 0, "Game controls:" );
    mvprintw ( 4, 0, "»Move - Arrow keys or WASD" );
    mvprintw ( 5, 0, "»Get quests from the (Q)uestbook by approaching it" );
    mvprintw ( 6, 0, "»Save the game - Press the \"S\" key" );
    mvprintw ( 7, 0, "»Close the game/Back to the startin menu - Press ESC key" );
    mvprintw ( 8, 0, "»In order to kill an (e)nemy, you need to move" );
    mvprintw ( 9, 0, " onto the place where he's standing" );
    mvprintw ( 10, 0, "»To increase your health, collect (h)ealthpacks and use them" );
    mvprintw ( 11, 0, " by pressing the \"H\" key" );
    mvprintw ( 12, 0, "»Try to collect every (g)olden statue, which can be used" );
    mvprintw ( 13, 0, " for increasing your experience by pressing the \"E\" key");
    mvprintw ( 14, 0, "»Avoid (b)ombs, they will cause a lot of damage!" );
    mvprintw ( 15, 12, "-----=====-----" );
    mvprintw ( 16, 0, "...press any key to continue..." );
    getch ();
    screens[0] -> printAndRun ( map, screens, player );
}

void StartScreen::controller ( int x, shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) {
    switch ( x ) {
    case 0:
        screens[1] -> printAndRun ( map, screens, player );
        break;
    case 1:
        screens[3] -> printAndRun ( map, screens, player );
        break;
    case 2:
        about ( map, screens, player );
        break;
    case 3:
        byeBye ();
        break;
    }
}