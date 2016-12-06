#pragma once
#include"Token.h"

class Spy: public Token
{
public:
	Spy(string newName, int newOwnership, int newRank);
	int isRankHigher(int rank2);
};