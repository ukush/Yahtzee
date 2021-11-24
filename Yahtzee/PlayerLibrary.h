#pragma once
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class PlayerLibrary
{

private:
	vector<Player*> playerList;

	static const int BUFFER_SIZE = 11;
	static const char* MAIN_FILENAME;

public:
	//constructor/destructor
	PlayerLibrary();
	~PlayerLibrary();

	// adding, removing searching methods
	vector<Player*>::const_iterator searchPlayer();
	void addPlayer();
	void removePlayer();
	Player* choosePlayer();
	void displayPlayerDetails() const;

	// I/O method
	void savePlayers();

	//sort methods
	void sortAlphabetically();
	void sortByHighestScore();

};