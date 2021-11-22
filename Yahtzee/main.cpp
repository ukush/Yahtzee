#include <iostream>
#include <fstream>
#include "Player.h"
#include <iomanip>
#include <algorithm>
#include <functional>
#include "Die.h"
#include "Scorecard.h"
#include "PlayerLibrary.h"

using namespace std;

const int MENU_CHOOSE_PLAYER = 1;
const int MENU_ADD_PLAYER = 2;
const int MENU_REMOVE_PLAYER = 3;
const int MENU_SORT_ALPHABETICALLY = 4;
const int MENU_SORT_HIGHEST_SCORE = 5;
const int MENU_EXIT = 9;
const int BUFFER_SIZE = 11;

void displayMenu();
int getMenuChoice(const int firstOption, const int lastOption);
void playMenu(Player& currentPlayer);
void playYahtzee(Player& currentPlayer);
bool allDiceHeld(const vector<Die*>& dice);
void displayScorecards(Player& currentPlayer);
void playRound(vector<Die*>& dice, int i);
void calcScore(vector<Die*>& dice, Scorecard& scorecard);

//char* encryptPassword(char* plaintextPw, int key);
//char* decryptPassword(char* ciphertextPw, int key);
//ostream& operator << (ostream& os, const Player& rhs);
//istream& operator >> (istream& is, const Player& rhs);
//istream& operator >> (istream& is, Player& rhs);
//void printList(const vector<Player*> &players);
//void initlist(vector<Player*>& players);
//void addPlayer(vector<Player*>& players);
//void removePlayer(vector<Player*>& players);
//void sortAlphabetically(vector<Player*>& players);
//void sortByHighestScore(vector<Player*>& players);
//vector<Player*>::const_iterator searchPlayer(const vector<Player*>& players);

int main()
{

#ifdef _DEBUG
    //_CrtSetBreakAlloc(290);
    _onexit(_CrtDumpMemoryLeaks);
#endif

    cout << "Weclome to Yahtzee\n------------------\n";
    PlayerLibrary* playerLib = new PlayerLibrary(); // create player library object which loads all players from txt file and adds to vector

    int choice;
    do
    {
        playerLib->displayPlayerDetails();
        displayMenu();
        choice = getMenuChoice(MENU_CHOOSE_PLAYER, MENU_EXIT);

        switch (choice)
        {
        case MENU_CHOOSE_PLAYER:
        {
            Player* currentPlayer = playerLib->choosePlayer();
            if (currentPlayer == nullptr)
                break;
            else
                playMenu(*currentPlayer);
            break;
        }
        case MENU_ADD_PLAYER:
        {
            //addPlayer(players);
            playerLib->addPlayer();
            break;
        }
        case MENU_REMOVE_PLAYER:
        {
            //removePlayer(players);
            playerLib->removePlayer();
            break;
        };
        case MENU_SORT_ALPHABETICALLY:
        {
            //instead of compareNames(), overload the '<' operator
            //sortAlphabetically(players);
            playerLib->sortAlphabetically();
            break;
        }
        case MENU_SORT_HIGHEST_SCORE:
        {
            //instead of compareScores(), overload the '>' operator
            //sortByHighestScore(players);
            playerLib->sortByHighestScore();
            break;
        }
        case MENU_EXIT:
        {
            playerLib->savePlayers();



            // free memory of each player
            delete playerLib;
            cout << "\nThanks for Playing!\n";
            break;
        }
        default:
        {
            cout << "\nERROR: INVALID OPTION\n";
            break;
        }

        }

    } while (choice != MENU_EXIT);


    //free all memory --> the vector was created and players added in this class, therefore it is this class' responsibility to delete and free the memory
    //for (Player* player : players)
    //{
    //    delete player;
    //}

    return 0;
}

void displayMenu()
{

    cout << MENU_CHOOSE_PLAYER << ") Choose Player\n";
    cout << MENU_ADD_PLAYER << ") Add Player\n";
    cout << MENU_REMOVE_PLAYER << ") Remove Player\n";
    cout << MENU_SORT_ALPHABETICALLY << ") Sort Player Alphabetically \n";
    cout << MENU_SORT_HIGHEST_SCORE << ") Sort by Highest Score\n";
    cout << MENU_EXIT << ") Exit\n";
}

int getMenuChoice(const int firstOption, const int lastOption)
{
    int choice;
    cout << "Choose option: ";
    cin >> choice;
    while (choice<firstOption || choice>lastOption)
    {
        cout << "Invalid option\nChoose option: ";
        cin >> choice;
    }
    return choice;
}

void playMenu(Player& currentPlayer)
{
    const int MENU_PLAY_GAME = 1;
    const int MENU_VIEW_SCORECARD = 2;
    const int MENU_RETURN = 9;


    cout << "Weclome to Yahtzee Play Arena\n------------------------------\n\n";
    // load player history from file
    // if no file exists, it is a new player
    // create new scorecard(history) updatePlayerStats()
    // currentPlayer->displayHighscore()
    // scorecard->displayPlayerStats();

    currentPlayer.displayPlayerStats();


    int choice;

    do {
        cout << "\n1) Play Game\n";
        cout << "2) View Scorecards\n";
        cout << "9) Return To Main Menu\n";

choice = getMenuChoice(MENU_PLAY_GAME, MENU_RETURN);

        switch (choice)
        {
        case 1:
        {
            playYahtzee(currentPlayer);
            break;
        }
        case 2:
        {
            if (!currentPlayer.noScorecards())
            {
                displayScorecards(currentPlayer);
            }

            break;
        }
        case 9:
        {
            cout << "\n\n";
            break;
        }
        default:
        {
            cout << "ERROR: INVALID OPTION\n";
            break;
        }
        }

    } while (choice != 9);
}

void playYahtzee(Player& currentPlayer)
{
    int gameNumber = currentPlayer.getTotalGames(); // get the total number of games
    Scorecard* scorecard = new Scorecard(gameNumber + 1); // create a scorecard where the game number starts from where the player left off last time and increment by 1

    currentPlayer.setNumberOfScorecards();

    // display empty scorecard
    scorecard->printScorecard();

    // Hold the dice in a stl vector
    vector<Die*> dice;

    // add all 5 dice to vector
    dice.push_back(new Die());
    dice.push_back(new Die());
    dice.push_back(new Die());
    dice.push_back(new Die());
    dice.push_back(new Die());

    //seed random number
    srand(time(nullptr));

    // each game has 3 rounds
    // each round has 3 rolls
    for (int i = 0; i < 3; i++)
    {
       
        playRound(dice, i);

        calcScore(dice, *scorecard);

        // display the scorecard for this game
        scorecard->printScorecard();
    }

    // check if high score 
    int gameScore = scorecard->getTotal();

     // update high score
    currentPlayer.updateHighscore(gameScore);


    // save total score in player history
    currentPlayer.updatePlayerStats(gameScore);

    // add scorecard
    currentPlayer.addScorecard(scorecard);

    // free memory for dice
    for (Die* d : dice)
    {
        delete(d);
    }
}

bool allDiceHeld(const vector<Die*>& dice)
{
    int held = 0;

    for (Die* d : dice)
    {
        if (d->isHeld())
        {
            held++;
        }
    }

    return (held == 5);
}

void displayScorecards(Player& currentPlayer)
{
    cout << "Loading Scorecards...\n\n";

    //load the first scorecard
    //get index of last scorecard
    int indexOfLast = currentPlayer.getNumberOfScorecards() - 1;
    int currentScorecard = 0;

    currentPlayer.getScorecard(currentScorecard)->displayHistoricScorecard();
    //cout << "Date Played: \t";
    //currentPlayer.getScorecard(currentScorecard)->displayTimestamp();
    //currentPlayer.getScorecard(currentScorecard)->printScorecard();
    


    int scorecardMenuChoice;

    do {
        cout << "\n1) View the Previous Scorecard\n";
        cout << "2) View the Next Scorecard\n";
        cout << "9) Return To Main Menu\n";

        scorecardMenuChoice = getMenuChoice(1, 9);

        switch (scorecardMenuChoice)
        {
        case 1:
        {
            // if current scorecard is 0 aka the first scorecard, cannot go back
            if (currentScorecard == 0)
            {
                cout << "\nERROR: CANNOT VIEW PREVIOUS SCORECARD\n\n";
            }
            else
            {
                currentScorecard -= 1;
                currentPlayer.getScorecard(currentScorecard)->displayHistoricScorecard();

                //cout << "Date Played: \t";
                //currentPlayer.getScorecard(currentScorecard)->displayTimestamp();
                //currentPlayer.getScorecard(currentScorecard)->printScorecard();
            }
            break;
        }
        case 2:
        {
            // if current scorecard is 0 aka the last scorecard, cannot go forward
            if (currentScorecard < indexOfLast)
            {
                currentScorecard += 1;
                currentPlayer.getScorecard(currentScorecard)->displayHistoricScorecard();
                //cout << "Date Played: \t";
                //currentPlayer.getScorecard(currentScorecard)->displayTimestamp();
                //currentPlayer.getScorecard(currentScorecard)->printScorecard();
            }
            else
                cout << "\nERROR: CANNOT VIEW NEXT SCORECARD\n\n";

            break;
        }
        case 9:
        {
            break;
        }
        default:
        {
            cout << "ERROR: INVALID OPTION\n";
            break;
        }

        }
    } while (scorecardMenuChoice != 9);
}

void playRound(vector<Die*>& dice, int i)
{
    // at the beginning of each round, unhold all the dice
    for (Die* d : dice)
    {
        d->UnholdDie();
    }

    int rollCount = 0;
    do
    {
        rollCount++;

        // roll all dice and display them
        cout << "\nRound " << i + 1 << " of 5\n";
        cout << "Roll # " << rollCount << "\n------------------\n";
        cout << "You rolled: \n\n";
        // use for each
        for (Die* d : dice)
        {
            d->rollDie();
            d->displayDie();
        }
        cout << "\n";

        // ask user to hold die
        cout << "Select the dice you want to hold:\n";
        cout << "Enter '6' to hold all dice and score your roll\n";
        cout << "Enter '9' to roll again:\n";
        cout << "Enter '0' when you've finished holding your dice:\n";
        int hold;
        bool holding = true;
        do {
            cin >> hold;
            switch (hold)
            {
            case 0:
            {
                holding = false;
                break;
            }
            case 1:
            {
                dice[0]->holdDie();
                break;
            }
            case 2:
            {
                dice[1]->holdDie();
                break;
            }
            case 3:
            {
                dice[2]->holdDie();
                break;
            }
            case 4:
            {
                dice[3]->holdDie();
                break;
            }
            case 5:
            {
                dice[4]->holdDie();
                break;
            }
            case 6:
            {
                for (Die* d : dice)
                {
                    if (!d->isHeld())
                    {
                        d->holdDie();
                    }
                }
                holding = false;
                break;
            }
            case 9:
            {
                holding = false;
                break;
            }
            default:
            {
                cout << "ERROR: INVALID OPTION\n";
                break;
            }

            }
        } while (holding);

        cout << "\n\n";
    } while (rollCount < 2 && !allDiceHeld(dice));

    // only roll again if they're not all held
    // roll all dice and display them for the last roll

    // check if they're all held don't roll again
    if (allDiceHeld(dice))
    {
        cout << "\nYou've held all your dice...\nHere is your final roll\n";
        // simply display them
        for (Die* d : dice)
        {
            d->displayDie();
        }
        cout << "\n";
    }
    else {
        cout << "\nRound " << i + 1 << " of 5\n";
        cout << "Roll #3\n------------------\n";
        cout << "You rolled: \n\n";

        // use for each
        for (Die* d : dice)
        {
            d->rollDie();
            d->displayDie();
        }
        cout << "\n";
    }
}

void calcScore(vector<Die*>& dice, Scorecard& scorecard)
{
    //prompt user to score against scorecard
    cout << "\nScore your dice against one of the following options: \n";
    cout << "1)\tAces\n";
    cout << "2)\tTwos\n";
    cout << "3)\tThrees\n";
    cout << "4)\tFours\n";
    cout << "5)\tFives\n";
    cout << "6)\tSixes\n";

    int scoreAgainst;
    do {
        cin >> scoreAgainst;
        switch (scoreAgainst)
        {
        case 1:
        {
            // add to aces
            // iterate through each die and see how many are equal to 1

            int aces = 0;
            for (Die* d : dice)
            {
                if (d->getDie() == 1)
                {
                    aces++;
                }
            }
            // add to scorecard
            scorecard.updateScorecard(0, aces);
            scorecard.updateTotal(aces);
            break;
        }
        case 2:
        {
            // add to twos
            int twos = 0;
            for (Die* d : dice)
            {
                if (d->getDie() == 2)
                {
                    twos++;
                }
            }
            twos *= 2;
            // add to scorecard
            scorecard.updateScorecard(1, twos);
            scorecard.updateTotal(twos);
            break;
        }
        case 3:
        {
            // add to threes
            int threes = 0;
            for (Die* d : dice)
            {
                if (d->getDie() == 3)
                {
                    threes++;
                }
            }
            threes *= 3;
            // add to scorecard
            scorecard.updateScorecard(2, threes);
            scorecard.updateTotal(threes);
            break;
        }
        case 4:
        {
            // add to fours
            int fours = 0;
            for (Die* d : dice)
            {
                if (d->getDie() == 4)
                {
                    fours++;
                }
            }
            fours *= 4;
            // add to scorecard
            scorecard.updateScorecard(3, fours);
            scorecard.updateTotal(fours);
            break;
        }
        case 5:
        {
            // add to fives
            int fives = 0;
            for (Die* d : dice)
            {
                if (d->getDie() == 5)
                {
                    fives++;
                }
            }
            fives *= 5;
            // add to scorecard
            scorecard.updateScorecard(4, fives);
            scorecard.updateTotal(fives);
            break;
        }
        case 6:
        {
            // add to sixes
            int sixes = 0;
            for (Die* d : dice)
            {
                if (d->getDie() == 6)
                {
                    sixes++;
                }
            }
            sixes *= 6;
            // add to scorecard
            scorecard.updateScorecard(5, sixes);
            scorecard.updateTotal(sixes);
            break;
        }
        default:
        {
            cout << "ERROR: INVALID OPTION\n";
            break;
        }
        }
    } while (scoreAgainst < 1 || scoreAgainst > 6); // validate input
}

//char* encryptPassword(char* plaintextPw, int key)
//{
//    /*
//    * Caesar Cipher routine found here - changed slightly
//    * https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
//    */
//
//    char c;
//    for (int i = 0; plaintextPw[i] != '\0'; i++)
//    {
//        c = plaintextPw[i]; 
//        if (c >= 97 && c <= 122)            // if between lower case a-z inclusive
//        {
//            c += key;                       // shift 3 letters up 
//            if (c > 122)
//            {   
//                c = c - 122 + 97 - 1;       // if non-letter, wrap around the aplhabet to a letter
//            }               
//            plaintextPw[i] = c;             
//        }
//        else if (c >= 65 && c <= 90)       //  if between upper case A-Z inclusive 
//        {                                  
//            c += key;                      // shift 3 letters up
//            if (c > 90)                   
//            {                              
//                c = c - 90 + 65 - 1;     // wrap around
//            }                              
//            plaintextPw[i] = c;            
//        }
//    }
//
//    return plaintextPw;
//}
//
//char* decryptPassword(char* ciphertextPw, int key)
//
//    /*
//    * Caesar Cipher routine found here - changed slightly
//    * https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
//    */
//{
//    char c;
//    for (int i = 0; ciphertextPw[i] != '\0'; i++)
//    {
//        c = ciphertextPw[i];
//
//        if (c >= 97 && c <= 122)            // if between lower case a-z inclusive
//        {
//            c -= key;                       // shift 3 letters down 
//            if (c < 97)
//            {
//                c = c + 122 - 97 + 1;       // if non-letter, wrap around the aplhabet to a letter
//            }
//            ciphertextPw[i] = c;
//        }
//        else if (c >= 65 && c <= 90)       //  if between upper case A-Z inclusive 
//        {
//            c -= key;                      // shift 3 letters down
//            if (c < 65)
//            {
//                c = c + 90 - 65 + 1;     // wrap around
//            }
//            ciphertextPw[i] = c;
//        }
//    }
//
//    return ciphertextPw;
//}
//
//ostream& operator << (ostream& os, const Player& rhs)
//{
//    string name(rhs.name);
//    string Epass(encryptPassword(rhs.password, 3));
//    os << name << "\n" << Epass << "\n" << rhs.hScore << "\n";
//    
//    return os;
//}
//
//istream& operator >> (istream& is, Player& rhs)
//{
//
//    return is;
//}
//void initlist(vector<Player*>& players)
//{
//    int score1 = 50;
//    int score2 = 10;
//    int score3 = 9;
//    int score4 = 100;
//
//
//    char name1[] = "neil";
//    char password1[] = "neil1";
//
//    Player* p1 = new Player(name1, password1, 100);
//
//    players.push_back(p1);
//
//
//    char name2[] = "jay";
//    char password2[] = "jay1";
//
//    Player* p2 = new Player(name2, password2, 199);
//
//    players.push_back(p2);
//
//    char name3[] = "harry";
//    char password3[] = "harry1";
//
//    Player* p3 = new Player(name3, password3, 99);
//
//    players.push_back(p3);
//
//    char name4[] = "kayla";
//    char password4[] = "kayla1";
//
//    Player* p4 = new Player(name4, password4, 50);
//
//
//    players.push_back(p4);
//}
//void printList(const vector<Player*> &players)
//{
//    cout << "\nPlayer Name:\t Highest Score:\n";
//    cout << "------------\t --------------\n";
//    for_each(players.cbegin(), players.cend(), [](const Player* player)
//        {
//            player->displayPlayerDetails();
//        });
//    cout << "\n";
//}
//
//vector<Player*>::const_iterator searchPlayer(const vector<Player*>& players)
//{
//    char name[BUFFER_SIZE];
//    cout << "\nEnter player name:\n";
//    cin >> setw(BUFFER_SIZE - 1) >> name;
//    cin.clear();
//    cin.ignore(1000, '\n');
//
//    // take in user input for password
//    char Pw[BUFFER_SIZE];
//    cout << "Enter the password:\n";
//    cin >> setw(BUFFER_SIZE - 1) >> Pw;
//    cin.clear();
//    cin.ignore(1000, '\n');
//
//
//    // search through list for a match for BOTH name and Password
//    auto it = find_if(players.begin(), players.end(), [&name, &Pw](Player* player) -> bool
//        {
//            if ((player->isPlayerName(name)) && (player->isPassword(Pw)))
//            {
//                return true;
//            }
//            else
//            {
//                return false;
//            }
//
//        });
//
//    return it;
//
//}
//
//void addPlayer(vector<Player*>& players)
//{
//    cout << "\nAdd Player\n----------\n";
//    char name[BUFFER_SIZE];
//    cout << "\nEnter a name for your player: (Cannot exceed 10 characters)\n";
//    cin >> setw(BUFFER_SIZE - 1) >> name;
//    cin.clear();
//    cin.ignore(1000, '\n');
//
//    // search through list for name match
//    auto it = find_if(players.begin(), players.end(), [&name](const Player* player) -> bool
//        {
//            // return player.getname() == search (overload)
//            return player->isPlayerName(name);
//        });
//
//    //auto it = searchName(players); // how to retrive the name? -> getter method??
//
//    if (it != players.end())
//    {
//        // the name matches so cannot create new player with same name
//        cout << "\nERROR: NAME ALREADY IN USE\n\n";
//    }
//    else
//    {
//        // name hasn't been taken so ask to set password now
//        // no need to search, just ensure it is of the correctt length->prompt user
//        char password[BUFFER_SIZE];
//        cout << "Choose a password for your player. (Cannot exceed 10 characters)\n";
//        cin >> setw(BUFFER_SIZE - 1) >> password;
//        cin.clear();
//        cin.ignore(1000, '\n');
//        
//        
//        // create a new player object with this name and password, and set all others to 0/null
//        Player* player = new Player(name, password, 0);
//        //player->setPlayer(name, password, 0);
//
//        players.push_back(player); // add player to list 
//        cout << "\nPlayer added successfully\n";
//
//        printList(players);
//    }
//}
//
//void removePlayer(vector<Player*>& players)
//{
//    cout << "\nRemove Player Player\n----------\n";
//
//    auto it = searchPlayer(players);
//
//    if (it != players.end())
//    {
//        players.erase(it);
//        // delete file?
//        cout << "Player Removed\n";
//
//    }
//    else
//    {
//        cout << "\nERROR: CANNOT FIND PLAYER\n";
//    }
//    printList(players);
//}
//
//
//void sortAlphabetically(vector<Player*> &players)
//{
//    cout << "\nSorting Player Alphabetically...\n";
//    sort(players.begin(), players.end(), [](const Player* lhs, const Player* rhs)
//        {
//            // cannot overload '<' for c strings
//            return lhs->compareNames(rhs);
//            
//        });
//    printList(players);
//}
//
//void sortByHighestScore(vector<Player*> &players)
//{
//   cout << "\nSorting by Highest Score...\n";
//   sort(players.begin(), players.end(), [](const Player* lhs, const Player* rhs)
//       {
//           //overload the '<' operator to perform sort
//           return (*lhs) < rhs;
//       });
//   printList(players);
//}

