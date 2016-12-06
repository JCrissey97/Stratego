#pragma once
#include"Token.h"

class Miner: public Token
{
public:
	Miner(string newName, int newOwnership, int newRank);
	int isRankHigher(int rank2);
};