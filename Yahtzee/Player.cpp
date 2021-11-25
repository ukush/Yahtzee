#include "Player.h"
#include <iostream>
#include <iomanip>

//constructors/destructor
Player::Player(char* name, char* password, int hScore) :

	name(_strdup(name)),			// dynamically allocates memory using malloc
	password(_strdup(password)),	// dynamically allocates memory using malloc
	hScore(hScore),
	totalGames(0),
	totalScore(0),
	avgScore(0),
	scorecardCapacity(INITIAL_SCORECARD_SIZE),
	numberOfScorecards(0),
	historyLoaded(false)
{
	scorecards = (Scorecard**)malloc(sizeof(Scorecard*) * scorecardCapacity);
}
Player::Player() :
name((char*)malloc(sizeof(char*)*INPUT_BUFFER_SIZE)),
password((char*)malloc(sizeof(char*)* INPUT_BUFFER_SIZE)),
hScore(0),
totalGames(0),
totalScore(0),
avgScore(0),
scorecardCapacity(INITIAL_SCORECARD_SIZE),
numberOfScorecards(0),
historyLoaded(false)
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

// accessor methods
int Player::getAvgScore()
{
	return avgScore;
}
int Player::getTotalScore()
{
	return totalScore;
}
char* Player::getName()
{
	return name;
}
int Player::getTotalGames()
{
	return totalGames;
}
Scorecard* Player::getScorecard(int index)
{
	return scorecards[index];
}
int Player::getNumberOfScorecards()
{
	return numberOfScorecards;
}
bool Player::isHistoryLoaded()
{
	return historyLoaded;
}


// display methods
void Player::displayPlayerDetails() const
{
	cout << name << "\t\t\t" << hScore;
	cout << "\n";
}
void Player::displayPlayerStats() const
{
	cout << "High Score: " << "\t\t\t" << hScore << "\n";
	cout << "Total Games: " << "\t\t\t" << totalGames << "\n";
	cout << "Accumulated Score: " << "\t\t" << totalScore << "\n";
	cout << "Average Score: " << "\t\t\t" << avgScore << "\n";
	cout << "\n";
}
void Player::displayScorecards()
{
	//load the first scorecard
	//get index of last scorecard
	int indexOfLast = numberOfScorecards - 1;
	int currentScorecard = 0;

	scorecards[currentScorecard]->displayHistoricScorecard();

	int choice;

	do {
		cout << "\n1) View the Previous Scorecard\n";
		cout << "2) View the Next Scorecard\n";
		cout << "9) Return To Main Menu\n";

		cout << "Choose option: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			// if current scorecard is 0 aka the first scorecard, cannot go back
			if (currentScorecard == 0)
			{
				cout << "\nERROR: Cannot view previous scorecard\n\n";
			}
			else
			{
				currentScorecard -= 1;
				scorecards[currentScorecard]->displayHistoricScorecard();
			}
			break;
		}
		case 2:
		{
			// if current scorecard the last scorecard, cannot go forward
			if (currentScorecard < indexOfLast)
			{
				currentScorecard += 1;
				scorecards[currentScorecard]->displayHistoricScorecard();
			}
			else
				cout << "\nERROR: Cannot view next scorecard\n\n";

			break;
		}
		case 9:
		{
			break;
		}
		default:
		{
			cout << "ERROR: Invalid option\n";
			break;
		}

		}

		while (choice < MENU_VIEW_PREV_SCORECARD || choice > MENU_RETURN)
		{
			cout << "Invalid option\nChoose option: ";
			cin >> choice;
		}
	} while (choice != MENU_RETURN);
}


// player validation methods
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


// updating player record methods (set methods)
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

		if (numberOfScorecards == 0)
		{
			scorecards[0] = sc;
		}
		else
		{
			scorecards[numberOfScorecards] = sc;

		}

		numberOfScorecards++;
	}
	else
	{
		// increase the capacity
		// add scorecard to end

		increaseScorecardCapacity();
		Scorecard** newScorecards = (Scorecard**)realloc(scorecards, (sizeof(Scorecard*) * scorecardCapacity)); // create a new pointer to an array of scorecards
		if (newScorecards == NULL)																				// if realloc is unsuccessful, the old pointer remains intact	
		{
			cout << "ERROR: Memory Allocation for " << sizeof(Scorecard*) * scorecardCapacity << " bytes failed\n";
			cout << "You've run out of memory, your games will not be saved\n\n";
			//free(scorecards);
		}

		scorecards = newScorecards;

	}
}


// encryption/decryption methods
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


// I/O method
void Player::loadHistory()
{
	string filename(name);
	filename = filename + ".txt";

	ifstream in(filename);
	if (in.is_open())
	{
		in >> totalScore >> totalGames >> avgScore;

		for (int i = 1; i <= totalGames; i++)
		{
			Scorecard* sc = new Scorecard(i);				// create new scorecard
			in >> *sc;										// load scorecard history
			addScorecard(sc);								// add scorecard to player's scorecard history
		}
		in.close();
	}
	else
	{
		cout << "ERROR: Unable to retireve player history\n\n";
	}

	historyLoaded = true;
}

//operator overloads
ostream& operator<<(std::ostream& os, Player& player)
{
	os << "\n" << player.name << "\n" << player.encryptPassword((player.password), 3) << "\n" << player.hScore;
	return os;
}
istream& operator>>(std::istream& is, Player& player)
{

	is >> player.name >> player.password >> player.hScore; // set the details
	player.password = player.decryptPassword(player.password, 3); // decrypt the password and store in memory

	return is;
}
bool Player::operator < (const Player* rhs) const
{
	// sort in desending order
	return hScore > rhs->hScore;
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
