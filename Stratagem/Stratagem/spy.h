#pragma once
#include"Token.h"

class Spy: public Token
{
public:
	Spy(string newName, int newOwnership, int newRank, string newPath);
	int isRankHigher(int rank2);
};