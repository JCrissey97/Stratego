#pragma once
#include"Token.h"

class Miner: public Token
{
public:
	Miner(string newName, int newOwnership, int newRank, string newPath);
	int isRankHigher(int rank2);
};