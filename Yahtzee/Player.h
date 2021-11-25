#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "Scorecard.h"

using namespace std;

class Player
{
private:
    static const int INITIAL_SCORECARD_SIZE = 5;
    static const int INPUT_BUFFER_SIZE = 11;
    static const int MENU_VIEW_PREV_SCORECARD = 1;
    static const int MENU_VIEW_NEXT_SCORECARD = 2;
    static const int MENU_RETURN = 9;


    char* name;
    char* password;
    int hScore;
    int totalGames;
    int totalScore;
    int avgScore;
    Scorecard** scorecards;

    int scorecardCapacity;
    int numberOfScorecards;

    bool historyLoaded;


public:
    // constructors & destructor
    Player(char* name, char* password, int hScore);
    Player();
    ~Player();

    // accessor methods
    int getAvgScore();
    int getTotalScore();
    char* getName();
    int getTotalGames();
    Scorecard* getScorecard(int index);
    int getNumberOfScorecards();
    bool isHistoryLoaded();

    // display methods
    void displayPlayerStats() const;
    void displayPlayerDetails() const;
    void displayScorecards();

    // player validation methods
    bool isPlayerName(const char* search) const;
    bool isPassword(const char* search) const;
    bool compareNames(const Player* rhs) const;

    // updating player record methods (set methods)
    void updateHighscore(int score);
    void updatePlayerStats(int gameScore);
    void increaseScorecardCapacity();
    void setNumberOfScorecards();
    void addScorecard(Scorecard* sc); 

    // encryption/decryption methods
    char* encryptPassword(char* plaintextPw, int key);
    char* decryptPassword(char* ciphertextPw, int key);

    // I/O method
    void loadHistory();

    // operator overloads
    bool operator < (const Player* rhs) const;
    friend ostream& operator<< (std::ostream& os, Player& player);
    friend istream& operator>> (std::istream& is, Player& player);

    bool noScorecards();
};