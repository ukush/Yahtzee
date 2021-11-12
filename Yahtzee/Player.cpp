#include "Player.h"
#include <iostream>
#include <iomanip>

Player::Player(const char* name, const char* password, int hScore) : 

	name(_strdup(name)),			// dynamically allocates memory using malloc
	password(_strdup(password)),	// dynamically allocates memory using malloc
	hScore(hScore)
{}

Player::~Player()
{
	// 'delete' calls this and releases the memory
	free(name);
	free(password);
}

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
	cout << "Accumulated Score: " << "\t\t" << "\n";
	cout << "Total Games: " << "\t\t\t"  << "\n";
	cout << "Average Score: " << "\t\t\t"  << "\n";
	cout << "\n";
}

void Player::displayPlayer() const
{
	cout << name << "\t\t\t" << hScore;
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

bool Player::compareNames(const Player* rhs) const // for sorting
{
	//compare c-strings using strcmp() - > returns -1 if lhs is less than
	if (strcmp(name, rhs->name) < 0)
		return true;
	else return false;
}

bool Player::operator<(const Player* rhs) const
{
	// sort in desending order
	return hScore > rhs->hScore;
}


