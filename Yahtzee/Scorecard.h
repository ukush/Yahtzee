#pragma once
#include <ctime>
#include <malloc.h>
#include <iostream>

using namespace std;

class Scorecard
{
private:
	static const int numberOfLines = 6;
	
	int gameNumber;
	int gameTotal;
	time_t now;
	struct tm newTime;
	char timestamp[26];
	int scores[numberOfLines];

public:
	Scorecard(int gameNumber);
	~Scorecard();
	void printScorecard();
	void updateTotal(int score);
	int getTotal();
	int getGameNumber();
	void updateScorecard(int index, int score);
	void displayTimestamp();
	void displayHistoricScorecard();

	friend ostream& operator<< (std::ostream& os, Scorecard& sc)
	{
		os << sc.timestamp;
		for (int i = 0; i < sc.numberOfLines; i++)
		{
			os << sc.scores[i] << "\n";
		}
		return os;
	}

	//void printDateTime()
	//{
	//	cout << nowLocal.tm_wday << " " << nowLocal.tm_mday << " " << nowLocal.tm_year << "\n";
	//}

	//void displayPlayerStats() const;
	//void updateGameNumber()
	//{
	//	gameNumber = totalGames + 1;
	//}
	//void updatePlayerStats(int gameScore);
	//int getTotalGames();
};

