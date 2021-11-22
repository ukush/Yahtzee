#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Player
{
	// member fields
private:
	
	char* name;
	char* password;

	int hScore;
	int accScore;
	int gamesPlayed;


public:
	// constructor and destructor
	Player(const char* name, const char* password, int hScore, int accScore, int gamesPlayed);
	Player(const char* name, const char* password);
	~Player();
	int getAvgScore();
	void displayPlayerStats() const;
	static void loadPlayers(fstream &playerfile, string filename, vector<Player*> playerlist);

	//char* encryptPassword(char* plainTextPw);
	//char* decryptPassword(char* encryptedPw);
	
	const bool isPlayerName(const string search) const;
	const bool isPassword(const string search) const;

	//static void sortAlphabetically(vector<Player*> &players);
	//static void sortByScore(vector<Player*> &players);

	//overload > method
	//bool operator>(const Player& rhs) const; // sort in ascending order
	//bool operator<(const Player& rhs) const; // sort in decending orer

	
	const bool compareNames(const Player& rhs) const;

};

