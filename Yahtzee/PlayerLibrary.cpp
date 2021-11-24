#include "PlayerLibrary.h"


const char* PlayerLibrary::MAIN_FILENAME = "Yahtzee.txt";


//constructor/destructor
PlayerLibrary::PlayerLibrary()
{

    // creates objects using the info in the yahtzee.txt file
    // adds them object to the list

    ifstream in (MAIN_FILENAME); // open file
    if (in.is_open())
    {

        string str;
        while (getline(in, str))         // issue here
        {
            Player* temp = new Player(); // create new player object
            in >> *temp;                 // load in player details from file
            playerList.push_back(temp);  // add to vector
        }

        in.close();
    }
    else
    {
        cout << "There are no Players to load\n";
    }

}
PlayerLibrary::~PlayerLibrary()
{
    // release memory for each player in the vector
    for (Player* player : playerList)
    {
        delete(player);
    }

        
}

// adding, removing searching methods
vector<Player*>::const_iterator PlayerLibrary::searchPlayer()
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
    auto it = find_if(playerList.begin(), playerList.end(), [&name, &Pw](Player* player) -> bool
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
void PlayerLibrary::addPlayer()
{
    cout << "\nAdd Player\n----------\n";
    char name[BUFFER_SIZE];
    cout << "\nEnter a name for your player: (Cannot exceed 10 characters)\n";
    cin >> setw(BUFFER_SIZE - 1) >> name;
    cin.clear();
    cin.ignore(1000, '\n');

    // search through list for name match
    auto it = find_if(playerList.begin(), playerList.end(), [&name](const Player* player) -> bool
        {
            // return player.getname() == search (overload)
            return player->isPlayerName(name);
        });

    if (it != playerList.end())
    {
        // the name matches so cannot create new player with same name
        cout << "\nERROR: That name is already in use\n\n";
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
        Player* player = new Player(name, password, 0);
        //player->setPlayer(name, password, 0);

        playerList.push_back(player); // add player to list 
        cout << "\nPlayer added successfully\n";

        //display updated list
        //displayPlayerDetails();
    }
}
void PlayerLibrary::removePlayer()
{
    cout << "\nRemove Player Player\n----------\n";

    auto it = searchPlayer();

    if (it != playerList.end())
    {
        delete* it; // delete object from memory
        playerList.erase(it); // remove the pointer from the list
        // delete file?
        cout << "Player Removed\n";

    }
    else
    {
        cout << "\nERROR: Cannot find player\n";
    }

    //display updated list
    //displayPlayerDetails();
}
Player* PlayerLibrary::choosePlayer()
{
    auto it = searchPlayer();
    if (it != playerList.end())
        return *it;
    else
    {
        cout << "ERROR: INCORRECT USERNAME OR PASSWORD\n";
        return nullptr;
    }
}
void PlayerLibrary::displayPlayerDetails() const
{
    cout << "\nPlayer Name:\tHighest Score:\n";
    cout << "------------\t--------------\n";

    for_each(playerList.cbegin(), playerList.cend(), [](const Player* player)
        {
            player->displayPlayerDetails();
        });
    cout << "\n";
}

// I/O method
void PlayerLibrary::savePlayers()
{
    // save player details to main txt file
    ofstream out(MAIN_FILENAME);
   if (out.is_open())
   {
       // write player details to text file
       for_each(playerList.begin(), playerList.end(), [&out](Player* player)
           {
               out << (*player); 
           });
       out.close();
   }
   else
   {
       cout << "ERROR: Cannot write to file\n";
   }

    // save player history to specific player file
   for (auto it = playerList.begin(); it != playerList.end(); ++it) // use a for loop because we need to the index of the scorecard
   {
       // track the player object
       auto position = it - playerList.begin();

       // name of file is the name of the player
       string filename(playerList[position]->getName());
       filename = filename + ".txt";
       ofstream out2(filename);

       if (out2.is_open())
       {
           //write total score, games and avg score to text file
           out2 << "\n"
               << playerList[position]->getTotalScore() << "\n"
               << playerList[position]->getTotalGames() << "\n"
               << playerList[position]->getAvgScore();

           for (int i = 0; i < playerList[position]->getNumberOfScorecards(); i++)
           {
               // write timestamped scorecards to text file (overload)
               out2 << *playerList[position]->getScorecard(i);
           }
       }
       else
       {
           cout << "ERROR: Cannot write to file\n";
       }
   }

}

//sort methods
void PlayerLibrary::sortAlphabetically()
{
    cout << "\nSorting Player Alphabetically...\n";
    sort(playerList.begin(), playerList.end(), [](const Player* lhs, const Player* rhs)
        {
            // cannot overload '<' for c strings
            return lhs->compareNames(rhs);

        });
}
void PlayerLibrary::sortByHighestScore()
{
    cout << "\nSorting by Highest Score...\n";
    sort(playerList.begin(), playerList.end(), [](const Player* lhs, const Player* rhs)
        {
            //overload the '<' operator to perform sort
            return (*lhs) < rhs;
        });
}

