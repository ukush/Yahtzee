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
	int scores[numberOfLines];			 // stores aces through to sixes
	bool categoryStates[numberOfLines];  // whether the category has been used before

	// for the date
	time_t now;
	struct tm newTime;
	char timestamp[26];


public:
	//constructor/destructor
	Scorecard(int gameNumber);
	~Scorecard();

	// getters
	int getTotal();
	int getGameNumber();

	// display methods
	void printScorecard();
	void displayTimestamp();
	void displayHistoricScorecard();

	// update(set) methods
	void updateTotal(int score);
	void updateScorecard(int index, int score);
	void updateCategoryStates(int category);
	void resetCategoryStates();

	// Operator overloads
	friend ostream& operator<< (std::ostream& os, Scorecard& sc);
	friend istream& operator>> (std::istream& is, Scorecard& sc);

	bool checkCategoryState(int category);

};

