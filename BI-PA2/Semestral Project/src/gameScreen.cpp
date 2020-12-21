#include "gameScreen.hpp"

void GameScreen::printAndRun ( shared_ptr<MapData> map, vector<shared_ptr<Controller>> & screens, shared_ptr<Player> player ) {
    clear ();
    string test;
    vector<int> items;
    shared_ptr<Inventory> playerInv = player -> getInv ();
    map -> printMap ();
    printInventory ( map, player, playerInv -> getItemList () );
    printQuest ( map, player );
    mvprintw ( map -> getHeight() + 3, 6, "Health: %d, Experience: %d", player -> getHealth (), player -> getExp () );
    int c;
    while ( (c = getch ()) != 27 ) {
        playerInv = player -> getInv ();
        items = playerInv -> getItemList ();

        switch ( c ) {
        case KEY_RIGHT:
            player -> move (map, 4);
            break;
        case KEY_UP:
            player -> move (map, 3);
            break;
        case KEY_DOWN:
            player -> move (map, 2);
            break;
        case KEY_LEFT:
            player -> move (map, 1);
            break;
        case 'h':
            if ( items[0] ) {
                playerInv -> useItem (0);
                player -> setHealth ( player -> getHealth () + 25 );
            }
            break;
        case 'g':
            if ( items[1] ) {
                playerInv -> useItem (1);
                player -> setExp ( player -> getExp () + 50 );
            }
            break;
        case 's':
            saved = true;
            screens[4] -> printAndRun ( map, screens, player );
            break;
        }
        if ( player -> getHealth () <= 0 ) {
            death ();
            break;
        }
        if ( saved ) {
            break;
        }
        clear ();
        map -> printMap ();
        printInventory ( map, player, playerInv -> getItemList () );
        printQuest ( map, player );
        mvprintw( map -> getHeight () + 3, 6, "Health: %d, Experience: %d", player -> getHealth (), player -> getExp () );
    }
    if ( ! ( player -> getHealth () <= 0 ) && ! saved ) {
        byeBye ();
    }
}

void GameScreen::byeBye () const {
    clear ();
    mvprintw ( 0, 6, "---- %s ----", "BYE" );
    mvprintw ( 6, 6, "-----===-----" );
    mvprintw ( 3, 0, "Thank you for playing, bye!" );
    getch();
    endwin ();
}

void GameScreen::death () const {
    clear ();
    mvprintw ( 0, 6, "---- %s ----", "DEAD" );
    mvprintw ( 6, 6, "-----====-----" );
    mvprintw ( 2, 0, "Great attempt, but you died :(" );
    mvprintw ( 5, 0, "Thank you for playing, bye!" );
    getch ();
    endwin ();
}

void GameScreen::printInventory ( shared_ptr<MapData> map, shared_ptr<Player> player, vector<int> items ) const {
    
    mvprintw ( 2, 7 + map -> getWidth (), "%s's inventory:", (player -> getName ()).c_str () );
    mvprintw ( 3, 7 + map -> getWidth (), "Healthpacks: %d", items[0] );
    mvprintw ( 4, 7 + map -> getWidth (), "Golden statues: %d", items[1] );
}

void GameScreen::printQuest ( shared_ptr<MapData> map, shared_ptr<Player> player ) {
    shared_ptr<QuestData> quest = map -> getQuestData ();
    mvprintw ( 7, 7 + map -> getWidth (), "Current quest:" );
if ( quest -> getDone () && quest -> getCurrentQuestIndex () != ( quest -> getSize () - 1 ) && quest -> getKillCount ( quest -> getCurrentQuestIndex () ) != 0 && ! shownReward ) {
        mvprintw ( 8, 7 + map -> getWidth (), "%s", "Check (Q)uestbook for a new quest!" );
    } else if ( quest -> getCurrentQuestIndex () == ( quest -> getSize () ) - 1 && quest -> getDone () && ! shownReward ) {
        mvprintw ( 8, 7 + map -> getWidth (), "%s", "Sorry, there're no more available quests" );
        } else if ( (quest -> getKillCount ( quest -> getCurrentQuestIndex () )) <= 0 && shownReward ) {
            mvprintw ( 8, 7 + map -> getWidth (), "Thank you for helping me!" );
            printReward ( map, player, quest );
            shownReward--;
            quest -> setDone ( true );
            map -> setQuestData ( quest );
            quest -> changeKillCount ( quest -> getCurrentQuestIndex (), -1 );
            } else {
                shownReward = 3;
                mvprintw ( 8, 7 + map -> getWidth (), "%s", ( quest -> getBrief ( quest -> getCurrentQuestIndex () ) ).c_str () );
                mvprintw ( 9, 7 + map -> getWidth (), "Remaining: %d", quest -> getKillCount ( quest -> getCurrentQuestIndex () ) );
    }
}

void GameScreen::printReward ( shared_ptr<MapData> map, shared_ptr<Player> player, shared_ptr<QuestData> quest ) {
    string healtPacks, goldenStatues, experience, reward = (quest -> getReward ( quest -> getCurrentQuestIndex () ));
    healtPacks = reward.substr ( 0, reward.find ( ' ' ) );
    goldenStatues = reward.substr ( 0 + healtPacks.size () + 1, reward.find ( ' ', healtPacks.size () ) );
    experience = reward.substr ( healtPacks.size () + goldenStatues.size () + 2, reward.find ( ' ', healtPacks.size () + goldenStatues.size () + 1 ) );
    if ( ! quest -> getDone () ){
        player -> addReward ( stoi ( healtPacks ), stoi ( goldenStatues ), stoi ( experience ) );
    }
    mvprintw ( 9, 7 + map -> getWidth (), "Your received %s healtpacks", healtPacks.c_str () );
    mvprintw ( 10, 7 + map -> getWidth (), "Your received %s golden statues", goldenStatues.c_str () );
    mvprintw ( 11, 7 + map -> getWidth (), "Your received %s experience", experience.c_str () );
}