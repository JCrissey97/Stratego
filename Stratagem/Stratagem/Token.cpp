#include"Token.h"

Token::Token(string newName, int newOwnership, int newRank) {
	name = newName;
	rank = newRank;
	ownership = newOwnership;
}
Token::Token() {
	name = "UNINITIALIZED!";
	rank = 0;
	ownership = 1;
}
Token::~Token() {

}

string Token::getName() {
	return name;
}
int Token::getOwnership() {
	return ownership;
}
int Token::getRank() {
	return rank;
}
int Token::isRankHigher(int rank2) {
	if (rank >= rank2) {
		return 1;
	}
	else if (rank < rank2) {
		return 2;
	}
}
