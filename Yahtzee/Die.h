#pragma once
#include <cstdlib>
#include <iostream>

using namespace std;

class Die
{
private:
	static const int MAX_RANGE = 6;
	static const int MIN_RANGE = 1;

	int value;
	bool held;

public:
	//constructor/destructor
	Die();
	~Die();

	//inlined methods
	void rollDie()
	{
		// randomly generate number between 1 and 6
		if (!held)
		{
			value = (rand() % MAX_RANGE) + MIN_RANGE;
		}
		value = value; // value remains the same if it's already been held
	}
	void holdDie()
	{
		if (held)
		{
			cout << "\nDie is already held. Select another\n";
		}
		else
		{
			held = true;
		}
	}
	void UnholdDie();
	void displayDie()
	{
		cout << " " << value;
		if (held)
			cout << "\t*held*\n";
		else
			cout << "\t\n";
	}
	int getDie()
	{
		return value;
	}
	bool isHeld()
	{
		if (held)
			return true;
		else return false;
	}

};
