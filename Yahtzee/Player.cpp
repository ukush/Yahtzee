#include "Player.h"
#include <iostream>
#include <iomanip>

const int BUFFER_SIZE = 11;


Player::Player(const char* name, const char* password, int hScore) : 
	name(_strdup(name)),			// dynamically allocates memory using malloc
	password(_strdup(password)),	// dynamically allocates memory using malloc
	hScore(hScore)
{	
	gameHistory = (int*)malloc(sizeof(int) * 4);
}

Player::~Player()
{
	// 'delete' calls this and releases the memory
	free(name);
	free(password);
	free(gameHistory);
}

//void Player::setPlayer(char* name, char* password, int hScore)
//{
//	this->name = _strdup(name);
//	this->password = _strdup(password);
//	this->hScore = hScore;
//}

void Player::loadPlayerHistory()
{
	// load in player history from file using cin <<
	// set the history array to the values
	// 
	// for (int i = 0; i<4; i++)
	// {
	//		gameHistory[i] = ...
	// }
	// now all of the player's attributes will be full

}

void Player::displayPlayerStats() const
{
	cout << "High Score: " << "\t\t\t" << hScore << "\n";
	cout << "Accumulated Score: " << "\t\t" << gameHistory[0] << "\n";
	cout << "Total Games: " << "\t\t\t" << gameHistory[1] << "\n";
	cout << "Average Score: " << "\t\t\t" << gameHistory[2] << "\n";
	cout << "\n";
}

void Player::displayPlayer() const
{
	cout << name << "\t\t\t" << hScore;
	cout << "\n";
}

bool Player::isPlayerName(const char* search) const
{
	//return strcmp()
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

bool Player::compareNames(const Player* rhs) const // for sorting
{
	//compare c-strings using strcmp() - > returns -1 if lhs is less than
	if (strcmp(name, rhs->name) < 0)
		return true;
	else return false;
}

bool Player::compareScores(const Player* rhs) const // for sorting
{
	return (hScore > rhs->hScore);
}

bool Player::operator<(const Player* rhs) const
{
	// sort in desending order
	return hScore > rhs->hScore;
}

//int Player::getAvgScore()
//{
//	return accScore / gamesPlayed;
//}

//char* Player::getName() const
//{
//	return name;
//}

//void Player::loadPlayers(fstream &playerfile, string filename, vector<Player*> playerlist)
//{
//
//}
//Player::Player(const char* name, const char* password, int hScore, int accScore, int gamesPlayed, int avgScore)
//	:hScore(hScore),
//	accScore(accScore),
//	gamesPlayed(gamesPlayed),
//	avgScore(avgScore)
//{
//	// this constructor is used to create objects for players that are being loaded from the disk
//	this->name = _strdup(name);
//	this->password = _strdup(password);
//}

//Player::Player(const char* name, const char* password)
//	:
//	hScore(0),
//	accScore(0),
//	gamesPlayed(0),
//	avgScore(0)
//{
//	this->name = _strdup(name);
//	this->password = _strdup(password);
//}

