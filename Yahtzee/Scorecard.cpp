#include "Scorecard.h"

Scorecard::Scorecard(int gameNumber) : 
	gameNumber(gameNumber),
	gameTotal(0),
	now(time(0))
{
	localtime_s(&newTime, &now); 
	asctime_s(timestamp, sizeof timestamp, &newTime);
	memset(scores, 0, sizeof(int) * numberOfLines);				// set default values to 0
	memset(categoryStates, 0, sizeof(bool) * numberOfLines); 	// set default values to 0 which means false
}


Scorecard::~Scorecard()
{
}


void Scorecard::printScorecard()
{
	cout << "\n\n------SCORECARD------\n";
	cout << "Game: " << gameNumber << "\n";
	cout << "\tAces:\t" << scores[0] << "\n";
	cout << "\tTwos:\t" << scores[1] << "\n";
	cout << "\tThrees:\t" << scores[2] << "\n";
	cout << "\tFours:\t" << scores[3] << "\n";
	cout << "\tFives:\t" << scores[4] << "\n";
	cout << "\tSixes:\t" << scores[5] << "\n";
	cout << "---------------------\n";
	cout << "Total: " << gameTotal << "\n";
	cout << "---------------------\n";

}

void Scorecard::displayHistoricScorecard()
{
	cout << "\n\n------SCORECARD------\n";
	cout << "Date: " << timestamp << "\n";
	cout << "Game: " << gameNumber << "\n";
	cout << "\tAces:\t" << scores[0] << "\n";
	cout << "\tTwos:\t" << scores[1] << "\n";
	cout << "\tThrees:\t" << scores[2] << "\n";
	cout << "\tFours:\t" << scores[3] << "\n";
	cout << "\tFives:\t" << scores[4] << "\n";
	cout << "\tSixes:\t" << scores[5] << "\n";
	cout << "---------------------\n";
	cout << "Total: " << gameTotal << "\n";
	cout << "---------------------\n";
}

bool Scorecard::checkCategoryState(int category)
{
	if (categoryStates[category - 1] == false)
		return false;
	else return true;
}

void Scorecard::updateCategoryStates(int category)
{
	categoryStates[category - 1] = true;
}

void Scorecard::resetCategoryStates()
{
	// resets all states back to false
	memset(categoryStates, 0, sizeof(bool) * numberOfLines);
}



void Scorecard::updateTotal(int score)
{
	gameTotal += score;
}

int Scorecard::getTotal()
{
	return gameTotal;
}

int Scorecard::getGameNumber()
{
	return gameNumber;
}

void Scorecard::updateScorecard(int index, int score)
{
	scores[index] += score;
}

void Scorecard::displayTimestamp()
{
	cout << timestamp;
}
