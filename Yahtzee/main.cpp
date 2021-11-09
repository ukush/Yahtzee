#include <iostream>
#include "Player.h"
#include <iomanip>
#include <algorithm>
#include <functional>

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
void printList(const vector<Player*> &players);
void initlist(vector<Player*>& players);

//vector<Player*>::const_iterator searchName(const vector<Player*>& players);
//vector<Player*>::const_iterator searchPassword(const vector<Player*>& players);
//void choosePlayer(const vector<Player*>& players);
void addPlayer(vector<Player*>& players);
void removePlayer(vector<Player*>& players);
void sortAlphabetically(vector<Player*>& players);
void sortByHighestScore(vector<Player*>& players);

vector<Player*>::const_iterator searchPlayer(const vector<Player*>& players);

void playMenu(const Player* currentPlayer);


void freeMemory(vector<Player*> players);


int main()
{
     
#ifdef _DEBUG
//_CrtSetBreakAlloc(193);
    _onexit(_CrtDumpMemoryLeaks);
#endif

    cout << "Weclome to Yahtzee\n------------------\n";
    

    vector<Player*> players;
    // load in players from file
    // load name, password, hscore
    // decrypt the password
    // add players to STL vector/list
    initlist(players);

    vector<Player*>::const_iterator it = players.begin();

    int choice;
    do
    {
        displayMenu();
        choice = getMenuChoice(MENU_CHOOSE_PLAYER, MENU_EXIT);
    
        switch (choice)
        {
            case MENU_CHOOSE_PLAYER: 
            {   
                auto it = searchPlayer(players); // search for name and password match

                if (it != players.end())
                {
                    cout << "\nPlayer validated successfully\n\n";
                    Player* currentPlayer = (*it);
                    // set game history
                    // currentPlayer->displayGameHistory
                    playMenu(currentPlayer);
                }
                else
                {
                    cout << "\nERROR: CANNOT FIND PLAYER\n\n";
                }
                break;
            }
            case MENU_ADD_PLAYER:
            {
                addPlayer(players);
                break;
            }
            case MENU_REMOVE_PLAYER:
            {
                removePlayer(players);
                break;
            };
            case MENU_SORT_ALPHABETICALLY:
            {
                //instead of compareNames(), overload the '<' operator
                sortAlphabetically(players);
                break;
            }
            case MENU_SORT_HIGHEST_SCORE:
            {
                //instead of compareScores(), overload the '>' operator
                sortByHighestScore(players);
                break;
            }
            case MENU_EXIT:
            {
                // save all information to disk
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
    freeMemory(players);
    
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

void playMenu(const Player* currentPlayer)
{
    const int MENU_PLAY_GAME = 1;
    const int MENU_VIEW_SCORECARD = 2;
    const int MENU_RETURN = 9;


    cout << "Weclome to Yahtzee Play Arena\n------------------------------\n\n";
    currentPlayer->displayPlayerStats();
    int choice;

    do {

        cout << "\n1) Play Game\n";
        cout << "2) View Score Cards\n";
        cout << "9) Return To Main Menu\n";

        choice = getMenuChoice(MENU_PLAY_GAME, MENU_RETURN);

        switch (choice)
        {
        case 1:
        {
            // load game
            cout << "Loading game...\n\n";
            break;
        }
        case 2:
        {
            cout << "Loading Scorecards...\n\n";
            // load scorecards

            
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

void printList(const vector<Player*> &players)
{
    cout << "\nPlayer Name:\t Highest Score:\n";
    cout << "------------\t --------------\n";
    for_each(players.cbegin(), players.cend(), [](const Player* player)
        {
            player->displayPlayer();
        });
    cout << "\n";
}

vector<Player*>::const_iterator searchPlayer(const vector<Player*>& players)
{
    char name[BUFFER_SIZE];
    cout << "\nEnter player name:\n";
    cin >> setw(BUFFER_SIZE - 1) >> name;
    cin.clear();
    cin.ignore(1000, '\n');

    // take in user input for password
    char Pw[BUFFER_SIZE];
    cout << "Enter the password:\n";
    cin >> setw(BUFFER_SIZE - 1) >> Pw;
    cin.clear();
    cin.ignore(1000, '\n');


    // search through list for a match for BOTH name and Password
    auto it = find_if(players.begin(), players.end(), [&name, &Pw](Player* player) -> bool
        {
            if ((player->isPlayerName(name)) && (player->isPassword(Pw)))
            {
                return true;
            }
            else
            {
                return false;
            }

        });

    return it;

}

void addPlayer(vector<Player*>& players)
{
    cout << "\nAdd Player\n----------\n";
    char name[BUFFER_SIZE];
    cout << "\nEnter a name for your player: (Cannot exceed 10 characters)\n";
    cin >> setw(BUFFER_SIZE - 1) >> name;
    cin.clear();
    cin.ignore(1000, '\n');

    // search through list for name match
    auto it = find_if(players.begin(), players.end(), [&name](const Player* player) -> bool
        {
            // return player.getname() == search (overload)
            return player->isPlayerName(name);
        });

    //auto it = searchName(players); // how to retrive the name? -> getter method??

    if (it != players.end())
    {
        // the name matches so cannot create new player with same name
        cout << "\nERROR: NAME ALREADY IN USE\n\n";
    }
    else
    {
        // name hasn't been taken so ask to set password now
        // no need to search, just ensure it is of the correctt length->prompt user
        char password[BUFFER_SIZE];
        cout << "Choose a password for your player. (Cannot exceed 10 characters)\n";
        cin >> setw(BUFFER_SIZE - 1) >> password;
        cin.clear();
        cin.ignore(1000, '\n');
        
        
        // create a new player object with this name and password, and set all others to 0/null
        Player* player = new Player();
        player->setPlayer(name, password, 0);


        players.push_back(player); // add player to list 
        cout << "\nPlayer added successfully\n";

        printList(players);
    }
}

void removePlayer(vector<Player*>& players)
{
    cout << "\nRemove Player Player\n----------\n";

    auto it = searchPlayer(players);

    if (it != players.end())
    {
        players.erase(it);
        cout << "Player Removed\n";

    }
    else
    {
        cout << "\nERROR: CANNOT FIND PLAYER\n";
    }
    printList(players);
}

void sortAlphabetically(vector<Player*> &players)
{
    cout << "\nSorting Player Alphabetically...\n";
    sort(players.begin(), players.end(), [](const Player* lhs, const Player* rhs)
        {
            // cannot overload '<' for c strings
            return lhs->compareNames(rhs);
            
        });
    printList(players);
}

void sortByHighestScore(vector<Player*> &players)
{
   cout << "\nSorting by Highest Score...\n";
   sort(players.begin(), players.end(), [](const Player* lhs, const Player* rhs)
       {
           //overload the '<' operator to perform sort
           return (*lhs) < rhs;
       });
   printList(players);
}

void freeMemory(vector<Player*> players)
{
    // call the destructor for each player pointer
    // It is the Player class' responsibility to free the memory it dynamically allocated (for name and password)
    for (Player* player : players)
    {
        delete player;
    }

    // vector will delete itself when it goes out of scope?
    //players.erase(players.begin(), players.end());
}

void initlist(vector<Player*>& players)
{
    int score1 = 50;
    int score2 = 10;
    int score3 = 9;
    int score4 = 100;


    char name1[] = "uwais";
    char password1[] = "u12345";
    
    Player* p1 = new Player();
    p1->setPlayer(name1, password1, 100);

    players.push_back(p1);


    char name2[] = "jay";
    char password2[] = "j12345";

    Player* p2 = new Player();
    p2->setPlayer(name2, password2, 199);;

    players.push_back(p2);

    char name3[] = "harry";
    char password3[] = "h12345";

    Player* p3 = new Player();
    p3->setPlayer(name3, password3, 99);

    players.push_back(p3);

    char name4[] = "kayla";
    char password4[] = "k12345";

    Player* p4 = new Player();
    p4->setPlayer(name4, password4, 50);


    players.push_back(p4);

    printList(players);
}

//vector<Player*>::const_iterator searchName(const vector<Player*>& players)
//{
//    char name[BUFFER_SIZE];
//    cout << "\nEnter a name for your player:\n";
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
//    return it;
//}

//vector<Player*>::const_iterator searchPassword(const vector<Player*>& players)
//{
//    // take in user input for password
//    char searchPw[BUFFER_SIZE];
//    cout << "Enter the player password:\n";
//    cin >> setw(BUFFER_SIZE - 1) >> searchPw;
//    cin.clear();
//    cin.ignore(1000, '\n');
//
//    // search through list for password match
//    auto pw_it = find_if(players.begin(), players.end(), [&searchPw](const Player* player) -> bool
//        {
//        return player->isPassword(searchPw);
//        });
//
//    return pw_it;
//}
//void choosePlayer(const vector<Player*> &players)
//{  
//
//    auto it = searchPlayer(players);
//
//    if (it != players.end())
//    {
//        cout << "\nPlayer validated successfully\n";
//        Player* currentPlayer = (*it);
//
//        playMenu(currentPlayer);
//
//        // display game menu
//    }       
//    else
//    {
//        cout << "Incorrect name or password\n";
//    }
//    cout << "\n";
//}
