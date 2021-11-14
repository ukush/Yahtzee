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

	char* name;
	char* password;
	int hScore;

	

public:
	Player(const char* name, const char* password, int hScore);
	~Player();
	void loadPlayerHistory();
	void displayPlayerStats() const;
	void displayPlayer() const;
	bool isPlayerName(const char* search) const;
	bool isPassword(const char* search) const;
	bool compareNames(const Player* rhs) const;
	bool operator < (const Player* rhs) const;


	char* getName()
	{
		return name;
	}


	friend ostream& operator << (ostream& os, const Player& rhs);
	friend ostream& operator >> (ostream& os, const Player& rhs);

};

