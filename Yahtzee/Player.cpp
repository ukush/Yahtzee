#include "Player.h"
#include <iostream>
#include <iomanip>



Player::Player(char* name, char* password, int hScore) :

	name(_strdup(name)),			// dynamically allocates memory using malloc
	password(_strdup(password)),	// dynamically allocates memory using malloc
	//name(new char[INPUT_BUFFER_SIZE]),
	//password(new char[INPUT_BUFFER_SIZE]),
	//name((char*)malloc(sizeof(char*)*INPUT_BUFFER_SIZE)),
	//password((char*)malloc(sizeof(char*)* INPUT_BUFFER_SIZE)),
	hScore(hScore),
	totalGames(0),
	totalScore(0),
	avgScore(0),
	scorecardCapacity(INITIAL_SCORECARD_SIZE),
	numberOfScorecards(0)
{
	scorecards = (Scorecard**)malloc(sizeof(Scorecard*) * scorecardCapacity);
}

Player::Player() :	
//name(new char[INPUT_BUFFER_SIZE]),
//password(new char[INPUT_BUFFER_SIZE]),
name((char*)malloc(sizeof(char*)*INPUT_BUFFER_SIZE)),
password((char*)malloc(sizeof(char*)* INPUT_BUFFER_SIZE)),
hScore(0),
totalGames(0),
totalScore(0),
avgScore(0),
scorecardCapacity(INITIAL_SCORECARD_SIZE),
numberOfScorecards(0)
{
	
	scorecards = (Scorecard**)malloc(sizeof(Scorecard*) * scorecardCapacity);
}

Player::~Player()
{
	// 'delete' calls this and releases the memory
	free(name);
	free(password);

	//free memory for each scorecard object in the array
	for (int i = 0; i < numberOfScorecards; i++)
	{
		delete scorecards[i];
	}

	free(scorecards); // release memory for array of pointers
}

void Player::displayPlayerStats() const
{
	cout << "High Score: " << "\t\t\t" << hScore << "\n";
	cout << "Total Games: " << "\t\t\t" << totalGames << "\n";
	cout << "Accumulated Score: " << "\t\t" << totalScore << "\n";
	cout << "Average Score: " << "\t\t\t" << avgScore << "\n";
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

void Player::updateHighscore(int score)
{
	if (score > hScore)
	{
		hScore = score;
		cout << "Congratulations, you've got a new high score!\n";
	}
	else
	{
		cout << "Unlucky, you didn't get a high score this time\n";
	}
}

Scorecard* Player::getScorecard(int index)
{
	return scorecards[index];
}

int Player::getScorecardCapacity()
{
	return scorecardCapacity;
}

int Player::getNumberOfScorecards()
{
	return numberOfScorecards;
}

char* Player::encryptPassword(char* plaintextPw, int key)
{
	/*
	* Caesar Cipher routine found here - changed slightly
	* https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
	*/

	char c;
	for (int i = 0; plaintextPw[i] != '\0'; i++)
	{
		c = plaintextPw[i];
		if (c >= 97 && c <= 122)            // if between lower case a-z inclusive
		{
			c += key;                       // shift 3 letters up 
			if (c > 122)
			{
				c = c - 122 + 97 - 1;       // if non-letter, wrap around the aplhabet to a letter
			}
			plaintextPw[i] = c;
		}
		else if (c >= 65 && c <= 90)       //  if between upper case A-Z inclusive 
		{
			c += key;                      // shift 3 letters up
			if (c > 90)
			{
				c = c - 90 + 65 - 1;     // wrap around
			}
			plaintextPw[i] = c;
		}
	}

	return plaintextPw;
}

char* Player::decryptPassword(char* ciphertextPw, int key)
{

	/*
	* Caesar Cipher routine found here - changed slightly
	* https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
	*/

	char c;
	for (int i = 0; ciphertextPw[i] != '\0'; i++)
	{
		c = ciphertextPw[i];

		if (c >= 97 && c <= 122)            // if between lower case a-z inclusive
		{
			c -= key;                       // shift 3 letters down 
			if (c < 97)
			{
				c = c + 122 - 97 + 1;       // if non-letter, wrap around the aplhabet to a letter
			}
			ciphertextPw[i] = c;
		}
		else if (c >= 65 && c <= 90)       //  if between upper case A-Z inclusive 
		{
			c -= key;                      // shift 3 letters down
			if (c < 65)
			{
				c = c + 90 - 65 + 1;     // wrap around
			}
			ciphertextPw[i] = c;
		}
	}

	return ciphertextPw;
}


bool Player::operator < (const Player* rhs) const
{
	// sort in desending order
	return hScore > rhs->hScore;
}

void Player::displayPlayerDetails() const
{
	cout << name << "\t\t\t" << hScore;
	cout << "\n";
}

void Player::updatePlayerStats(int gameScore)
{
	totalGames += 1;
	totalScore += gameScore;
	avgScore = totalScore / totalGames;
}

void Player::increaseScorecardCapacity()
{
	scorecardCapacity *= 2; // double the capacity each time
}

void Player::setNumberOfScorecards()
{
	numberOfScorecards += 1;
}

void Player::addScorecard(Scorecard* sc)
{
	// check if capacity is full
	if (numberOfScorecards <= scorecardCapacity)
	{
		// not full so add
		scorecards[numberOfScorecards - 1] = sc;
	}
	else
	{
		// increase the capacity
		// add scorecard to end

		increaseScorecardCapacity();
		Scorecard** newScorecards = (Scorecard**)realloc(scorecards, (sizeof(Scorecard*) * scorecardCapacity)); // create a new pointer to an array of scorecards
		if (newScorecards == NULL)																				// if realloc is unsuccessful, the old pointer remains intact	
		{
			cout << "ERROR: MEMORY REALLOCATION FOR " << sizeof(Scorecard*) *scorecardCapacity << "FAILED\n";
			cout << "You've run out of memory, your games will not be saved\n\n";
			//free(scorecards);
		}

		scorecards = newScorecards;
																		
	}
}

int Player::getTotalGames()
{
	return totalGames;
}

bool Player::noScorecards()
{
	if (numberOfScorecards == 0)
	{
		cout << "\nERROR: There are no scorecards to display\n";
		return true;
	}
	else return false;

}




