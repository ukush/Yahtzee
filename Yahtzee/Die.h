#pragma once
#include <cstdlib>
#include <iostream>

using namespace std;

class Die
{
private:
	int value;
	bool held;

public:
	Die();
	~Die();
	void rollDie()
	{
		const int MAX_RANGE = 6;
		const int MIN_RANGE = 1;

		// randomly generate number between 1 and 6
		if (!held)
		{
			value = (rand() % MAX_RANGE) + MIN_RANGE;
		}

		value = value; // value remains the same
	}

	int getDie()
	{
		return value;
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

	void UnholdDie()
	{
		held = false;
	}

	void displayDie()
	{
		cout << " " << value;
		if (held)
			cout << "\t*held*\n";
		else
			cout << "\t\n";
	}

	bool isHeld()
	{
		if (held)
			return true;
		else return false;
	}

};
