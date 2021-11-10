#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

class Player
{
private:
//int accScore;
//int gamesPlayed;
//int avgScore;
	
	char* name;
	char* password;
	int hScore;
	int* gameHistory;

public:
	Player(const char* name, const char* password, int hScore);
	~Player();
	//void setPlayer(char* name, char* password, int hScore);
	void loadPlayerHistory();
	void displayPlayerStats() const;
	void displayPlayer() const;
	bool isPlayerName(const char* search) const;
	bool isPassword(const char* search) const;
	bool compareNames(const Player* rhs) const;
	bool compareScores(const Player* rhs) const;
	bool operator < (const Player* rhs) const;
	
	//static void loadPlayers(fstream &playerfile, string filename, vector<Player*> playerlist);
	//char* encryptPassword(char* plainTextPw);
	//char* decryptPassword(char* encryptedPw);
	//int getAvgScore();
	//char* getName() const;

};

