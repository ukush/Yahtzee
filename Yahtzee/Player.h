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

	int playerid;
	char* name;
	char* password;
	int hScore;
	Scorecard* scorecards;
	int* history;
	static int counter;
	

public:
	Player(const char* name, const char* password, int hScore);
	Player();
	~Player();
	void displayPlayerStats() const;
	void displayPlayer() const;
	bool isPlayerName(const char* search) const;
	bool isPassword(const char* search) const;
	bool compareNames(const Player* rhs) const;
	bool operator < (const Player* rhs) const;
	int getPlayerId();
	void updateHighscore(int score);
	friend ostream& operator << (ostream& os, const Player& rhs);
	friend istream& operator >> (istream& is, const Player& rhs);
	void initHistory();
	void setHistory(int tGames, int Tscore, int avgScore);
	//void setPlayer(char* name, char* password, int highscore)
	//{
	//	this->name = name;
	//	this->password = password;
	//	hScore = highscore;
	//}
	void updatePlayerHistory(int gameScore);
	//void addScorecard(Scorecard* sc, int size);
	int getTotalGames();
};

