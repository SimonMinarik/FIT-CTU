#include "createPlayerScreen.hpp"

void CreatePlayerScreen::printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) {
    char name[25];
    string test;
    clear ();
    echo ();
    curs_set (1);
    mvprintw ( 0, 5, "---- %s ----", "CREATE" );
    mvprintw ( 4, 0, "...press RETURN to continue..." );
    mvprintw ( 5, 5, "-----======-----" );
    mvprintw ( 1, 0, "Enter you name (25 chars max): " );
    getnstr ( name, 25 );
    player = make_shared<Player> ();
    player -> setName ( name );
    noecho ();
    curs_set (0);
    setAttributes ( map, screens, player );
}

void CreatePlayerScreen::setAttributes ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) {
    clear ();
    mvprintw ( 0, 5, "---- %s ----", "CREATE" );
    mvprintw ( 8, 5, "-----======-----" );
    string name = player -> getName ();
    mvprintw ( 1, 0, "Hello, %s, change your skill points by", name.c_str() );
    mvprintw ( 2, 0,  "pressing LEFT/RIGHT arrow key" );
    char list[4][8] = { "Health", "Attack", "Defense" };
    char item[15];
    int attributes[3] = {75, 25, 10};
    int defaultAtt[3] = {75, 25, 10};
    int points = 20;

    mvprintw ( 4, 5, "Points left: %d", points );
    for ( int i = 0; i < 3; i++ ) {
        if ( ! i ) {
            attron ( A_STANDOUT );
        } else
            attroff ( A_STANDOUT );
            sprintf (item, "%-9s %d",  list[i], attributes[i]);
            mvprintw ( i + 5, 7, "%s", item );
    }
    int ch, i = 0;
    while ( (ch = getch()) != 10 ) {
        mvprintw ( 4, 5, "%20s", " " );
        mvprintw ( 4, 5, "Points left: %d", points );
        sprintf ( item, "%-9s %d", list[i], attributes[i] ); 
        mvprintw ( i + 5, 7, "%s", item );
        switch ( ch ) {
        case KEY_UP:
            i--;
            i = ( i < 0 ) ? 2 : i;
            break;
        case KEY_DOWN:
            i++;
            i = ( i > 2 ) ? 0 : i;
            break;
        case KEY_RIGHT:
            if ( points ) {
                attributes[i]++;
                points--;
            }
            break;
        case KEY_LEFT:
            if ( points != 20 && attributes[i] != defaultAtt[i]) {
                points++;
                attributes[i]--;
            }
            break;
        case 27:
            screens[0] -> printAndRun ( map, screens, player );
            break;
        }

        attron ( A_STANDOUT );

        sprintf ( item, "%-9s %d",  list[i], attributes[i] );
        mvprintw ( i+5, 7, "%s", item );
        attroff ( A_STANDOUT );
        mvprintw ( 4, 5, "%20s", " " );
        mvprintw ( 4, 5, "Points left: %d", points );
    }
    clear ();
    player -> setHealth ( attributes[0] );
    player -> setAttack ( attributes[1] );
    player -> setDefense ( attributes[2] );
    
    screens[2] -> printAndRun ( map, screens, player );
}