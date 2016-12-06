#include "spy.h"

Spy::Spy(string newName, int newOwnership, int newRank) : Token(newName, newOwnership, newRank)
{
}

int Spy::isRankHigher(int rank2)
{
	if (rank2 == 10) 
	{
		return 1;
	}
	else
	{
		return 2;
	}
}