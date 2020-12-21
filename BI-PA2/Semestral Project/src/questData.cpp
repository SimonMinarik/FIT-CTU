#include "questData.hpp"

string QuestData::getBrief ( int x ) const {
    return questBrief[x];
}

void QuestData::setBrief ( string x ) {
    questBrief.push_back ( x );
}

string QuestData::getQuest ( int x ) const {
    return questList[x];
}

void QuestData::setQuest ( string x ) {
    questList.push_back ( x );
}

string QuestData::getReward ( int x ) const {
    return questReward[x];
}

void QuestData::setReward ( string x ) {
    questReward.push_back ( x );
}

int QuestData::getCurrentQuestIndex () const {
    return currentQuest;
}

void QuestData::setCurrentQuest ( int x ) {
    if ( currentQuest != questList.size () ) {
        currentQuest = x;
    }
}

bool QuestData::getDone () const {
    return done;
}

void QuestData::setDone ( bool x ) {
    done = x;
}

int QuestData::getSize () const {
    return questList.size();
}

void QuestData::setKillCount ( int x ) {
    killCount.push_back ( x );
}

int QuestData::getKillCount ( int x ) const {
    return killCount[x];
}

void QuestData::changeKillCount ( int x, int count ) {
    killCount[x] = count;
}

void QuestData::setWinShow ( int x ) {
    winShow = x;
}

int QuestData::getWinShow () const {
    return winShow;
}