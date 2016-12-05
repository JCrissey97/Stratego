#include"Token.h"

Token::Token(string newName, int newOwnership, int newRank, string newPath) {
	name = newName;
	rank = newRank;
	ownership = newOwnership;
	path = newPath;
}
Token::Token() {
	name = "UNINITIALIZED!";
	rank = 0;
	ownership = 1;
	path = "";
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
