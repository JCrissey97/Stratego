#include "miner.h"

Miner::Miner(string newName, int newOwnership, int newRank) : Token(newName, newOwnership, newRank)
{
}

int Miner::isRankHigher(int rank2)
{
	if (rank2 == 11) {
		return 1;
	}
	else if (rank >= rank2) {
		return 1;
	}
	else if (rank < rank2) {
		return 2;
	}
}