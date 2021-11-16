#include "Player.h"
#include <iostream>
#include <iomanip>

const int INITIAL_SIZE = 5;
int Player::counter = 1;

Player::Player()
{
}

Player::Player(const char* name, const char* password, int hScore) :

	playerid(counter++),
	name(_strdup(name)),			// dynamically allocates memory using malloc
	password(_strdup(password)),	// dynamically allocates memory using malloc
	hScore(hScore),
	history((int*)malloc(sizeof(int) * 3))
{
	scorecards = new Scorecard[5];
}

Player::~Player()
{
	// 'delete' calls this and releases the memory
	free(name);
	free(password);
	free(scorecards);
}

void Player::displayPlayerStats() const
{
	cout << "High Score: " << "\t\t\t" << hScore << "\n";
	cout << "Total Games: " << "\t\t\t"  << history[0] <<"\n";
	cout << "Accumulated Score: " << "\t\t" << history[1] << "\n";
	cout << "Average Score: " << "\t\t\t"  << history[2] <<"\n";
	cout << "\n";
}


bool Player::isPlayerName(const char* search) const
{
	if (strcmp(name, search) == 0)
	{
		return true;
	}
	else return false;


}

bool Player::isPassword(const char* search) const
{

	if (strcmp(password, search) == 0)
	{
		return true;
	}
	else return false;
}

bool Player::compareNames(const Player* rhs) const
{
	//compare c-strings using strcmp() - > returns -1 if lhs is less than
	if (strcmp(name, rhs->name) < 0)
		return true;
	else return false;
}

int Player::getPlayerId()
{
	return playerid;
}

void Player::updateHighscore(int score)
{
	if (score > hScore)
		hScore = score;
	else
	{
		cout << "Unlucky, you didn't get a high score this time!\n";
	}
}

void Player::setHistory(int tGames, int tScore, int avgScore)
{
	history[0] = tGames;
	history[1] = tScore;
	history[2] = avgScore;
}

void Player::initHistory()
{
	for (int i = 0; i < 3; i++)
	{
		history[i] = 0;
	}
}

bool Player::operator < (const Player* rhs) const
{
	// sort in desending order
	return hScore > rhs->hScore;
}

void Player::displayPlayer() const
{
	cout << name << "\t\t\t" << hScore;
	cout << "\n";
}

void Player::updatePlayerHistory(int gameScore)
{
	history[0] += 1;
	history[1] += gameScore;
	history[2] = history[1] / history[0];
}

//void Player::addScorecard(Scorecard* sc, int size)
//{
//	// Allocate new temp array with increased size
//	Scorecard* temp = new Scorecard[size + 1];
//
//	// copy everything from current array to temp array
//	for (int i = 0; i < size; i++)
//	{
//		temp[i] = scorecards[i];
//	}
//
//	// delete current array
//	delete[] scorecards;
//
//	// save pointer temp to current array
//	scorecards = temp;
//
//	//increment size;
//	size++;
//
//	scorecards[size - 1] = sc;
//
//
//}


int Player::getTotalGames()
{
	return history[0];
}


