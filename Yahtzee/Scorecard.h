#pragma once
#include <ctime>
#include <malloc.h>
#include <iostream>
using namespace std;

class Scorecard
{
private:
	int gameNumber;
	int gameTotal;
	//time_t date;
	int* scores;

public:
	Scorecard(int gameNumber);
	Scorecard();
	~Scorecard();
	void printScorecard();
	void updateTotal(int score);
	int getTotal();
	void updateScorecard(int index, int score);
	void initScores();
};

