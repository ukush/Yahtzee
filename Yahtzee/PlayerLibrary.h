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
	//static const char* MAIN_FILENAME;

public:
	PlayerLibrary();
	~PlayerLibrary();
	void addPlayer();
	void removePlayer();
	Player* choosePlayer();
	void savePlayers();

	void displayPlayerDetails() const
	{
		cout << "\nPlayer Name:\tHighest Score:\n";
		cout << "------------\t--------------\n";

		for_each(playerList.cbegin(), playerList.cend(), [](const Player* player)
			{
				player->displayPlayerDetails();
			});
		cout << "\n";
	}


	vector<Player*>::const_iterator searchPlayer();

	void sortAlphabetically()
	{
		cout << "\nSorting Player Alphabetically...\n";
		sort(playerList.begin(), playerList.end(), [](const Player* lhs, const Player* rhs)
			{
				// cannot overload '<' for c strings
				return lhs->compareNames(rhs);

			});
	}

	void sortByHighestScore()
	{
		cout << "\nSorting by Highest Score...\n";
		sort(playerList.begin(), playerList.end(), [](const Player* lhs, const Player* rhs)
			{
				//overload the '<' operator to perform sort
				return (*lhs) < rhs;
			});
	}

};