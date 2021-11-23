#pragma once
#include <ctime>
#include <malloc.h>
#include <iostream>
#include <string>

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
	//Scorecard();
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
		os << sc.gameTotal << "\n";
		return os;
	}

	friend istream& operator>> (std::istream& is, Scorecard& sc)
	{
		string line;
		(getline(is, line));
		(getline(is, line));
		strcpy_s(sc.timestamp, line.c_str());
		for (int i = 0; i < sc.numberOfLines; i++)
		{
			is >> sc.scores[i];
		}

		is >> sc.gameTotal;
		return is;
	}
};

