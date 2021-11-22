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
    static const int BUFFER_SIZE = 11;
    char* name;
    char* password;
    int hScore;
    int totalGames;
    int totalScore;
    int avgScore;
    Scorecard** scorecards;
    int scorecardCapacity;
    int numberOfScorecards;


public:
    Player(const char* name, const char* password, int hScore);
    //Player();
    ~Player();
    void displayPlayerStats() const;
    void displayPlayerDetails() const;
    bool isPlayerName(const char* search) const;
    bool isPassword(const char* search) const;
    bool compareNames(const Player* rhs) const;
    bool operator < (const Player* rhs) const;
    void updateHighscore(int score);
    Scorecard* getScorecard(int index);
    int getScorecardCapacity();
    int getNumberOfScorecards();
    char* encryptPassword(char* plaintextPw, int key);
    char* decryptPassword(char* ciphertextPw, int key);
    void updatePlayerStats(int gameScore);
    void increaseScorecardCapacity();
    void setNumberOfScorecards();
    void addScorecard(Scorecard* sc);
    int getTotalGames();
    
    int getTotalScore()
    {
        return totalScore;
    }

    char* getName()
    {
        return name;
    }

    friend ostream& operator<< (std::ostream& os, Player& player)
    {
        os << player.name << "\n" << player.encryptPassword((player.password), 3) << "\n" << player.hScore << "\n";
        return os;
    }

    friend istream& operator>> (std::istream& is, Player& player)
    {
        is >> player.name >> player.decryptPassword((player.password), 3) >> player.hScore;
        return is;
    }

    bool noScorecards();
};