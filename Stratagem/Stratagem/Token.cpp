#include"Token.h"

Token::Token(string newName, int newOwnership, int newRank) {
	name = newName;
	rank = newRank;
	ownership = newOwnership;
	selected = false;
	revealed = false;
}
Token::Token() {
	name = "UNINITIALIZED!";
	rank = 0;
	ownership = 0;
	selected = false;
	revealed = false;
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
bool Token::getSelected()
{
	return this->selected;
}

bool Token::switchSelected()
{
	if (selected) selected = false;
	else selected = true;
	return selected;
}

bool Token::isRevealed()
{
	return revealed;
}

bool Token::switchRevealed()
{
	if (revealed) revealed = false;
	else revealed = true;
	return revealed;
}