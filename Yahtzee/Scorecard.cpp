#include "Scorecard.h"

Scorecard::Scorecard(int gameNumber) : gameNumber(gameNumber), scores((int*)malloc(sizeof(int) * 6)), gameTotal(0)
{	
	/*
	* got the code for date here: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
	*/
	//const time_t now = time(0);
	//date = ctime_s(&now);
	
	for (int i = 0; i < 6; i++)
	{
		scores[i] = 0;
	}
	

}

Scorecard::~Scorecard()
{
	free(scores);
}


void Scorecard::printScorecard()
{
	cout << "\n\n------SCORECARD------\n";
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

void Scorecard::updateTotal(int score)
{
	gameTotal += score;
}

int Scorecard::getTotal()
{
	return gameTotal;
}

void Scorecard::updateScorecard(int index, int score)
{
	scores[index] += score;
}

