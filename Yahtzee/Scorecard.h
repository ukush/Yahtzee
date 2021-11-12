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
	//char* date;
	int* scores;

public:
	Scorecard(int gameNumber);
	~Scorecard();
	void printScorecard();
	void updateTotal(int score);
	int getTotal();
	void updateScorecard(int index, int score);
};

