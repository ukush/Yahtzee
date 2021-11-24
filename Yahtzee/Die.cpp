#include "Die.h"

Die::Die() : value(0), held(false)
{}

Die::~Die()
{}

void Die::UnholdDie()
{
	held = false;
}
