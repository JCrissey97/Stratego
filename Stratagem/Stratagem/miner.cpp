#include "miner.h"

Miner::Miner(string newName, int newOwnership, int newRank, string newPath) : Token(newName, newOwnership, newRank, newPath)
{
}

int Miner::isRankHigher(int rank2)
{
	if (rank2 == 13) {
		return 1;
	}
	else if (rank >= rank2) {
		return 1;
	}
	else if (rank < rank2) {
		return 2;
	}
}