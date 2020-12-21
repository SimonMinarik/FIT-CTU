/**
 * @file questData.hpp
 * @author Simon Minarik
 * @brief header file of QuestData class
 * @version 0.1
 * @date 2019-05-27
 * 
 * 
 */
#ifndef quest_data
#define quest_data

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <memory>

using namespace std;
/**
 * @brief class QuestData stores the information about quests (their description, goal, reward)
 * 
 */
class QuestData {
    public:
    /**
     * @brief Construct a new Quest Data object and initializes quest vectors
     * 
     */
    QuestData () {
        questList.push_back ( "" );
        questBrief.push_back ( "" );
        questReward.push_back ( "" );
        killCount.push_back ( -1 );
        currentQuest = 0;
        winShow = 3;
    }
    /**
     * @brief getter of the x-th quest description
     * 
     */
    string getQuest ( int x ) const;
    /**
     * @brief setter of quest description
     * 
     * @param x 
     */
    void setQuest ( string x );
    /**
     * @brief getter of brief description of the quest
     * 
     */
    string getBrief ( int x ) const;
    /**
     * @brief setter of brief description of the quest
     * 
     */
    void setBrief ( string x );
    /**
     * @brief getter of reward of the quest
     * 
     */
    string getReward ( int x ) const;
    /**
     * @brief setter of the quests reward
     * 
     */
    void setReward ( string x );
    /**
     * @brief setter of current quest index
     * 
     */
    void setCurrentQuest ( int x );
    /**
     * @brief getter of current quest index
     * 
     * @return int 
     */
    int getCurrentQuestIndex () const;
    /**
     * @brief sets the state of the quest
     * 
     */
    void setDone ( bool x );
    /**
     * @brief getter of the quest state
     * 
     */
    bool getDone () const;
    /**
     * @brief getter of the number of quest
     * 
     * @return int 
     */
    int getSize () const ;
    /**
     * @brief setter of the quest objective
     * 
     */
    void setKillCount ( int x );
    /**
     * @brief getter of the quest objective
     * 
     */
    int getKillCount ( int x ) const ;
    /**
     * @brief changes the state of the objective
     * 
     */
    void changeKillCount ( int x, int count );
    /**
     * @brief setter of the number of how many times the reward message is supposed to be shown for
     * 
     */
    void setWinShow ( int x );
    /**
     * @brief getter of the number of how many times the reward message is supposed to be shown for
     * 
     */
    int getWinShow () const;
    protected:
    vector<string> questList;
    vector<string> questBrief;
    vector<string> questReward;
    vector<int> killCount;
    int currentQuest;
    bool done = true;
    int winShow;
};

#endif // quest_data