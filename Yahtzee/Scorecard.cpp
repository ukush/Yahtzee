#include "Scorecard.h"

//constructor/destructor
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

// getters
int Scorecard::getTotal()
{
	return gameTotal;
}
int Scorecard::getGameNumber()
{
	return gameNumber;
}

// display methods
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
void Scorecard::displayTimestamp()
{
	cout << timestamp;
}

// update(set) methods
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
void Scorecard::updateScorecard(int index, int score)
{
	scores[index] += score;
}

// Operator overloads
ostream& operator<<(std::ostream& os, Scorecard& sc)
{
	os << "\n" << sc.timestamp << "\n";
	for (int i = 0; i < sc.numberOfLines; i++)
	{
		os << sc.scores[i] << "\n";
	}
	os << sc.gameTotal;
	return os;
}
istream& operator>>(std::istream& is, Scorecard& sc)
{
	string line;
	getline(is, line);			// skip line
	getline(is, line);
	strcpy_s(sc.timestamp, line.c_str());
	for (int i = 0; i < sc.numberOfLines; i++)
	{
		is >> sc.scores[i];
	}

	is >> sc.gameTotal;
	return is;
}


bool Scorecard::checkCategoryState(int category)
{
	if (categoryStates[category - 1] == false)
		return false;
	else return true;
}
