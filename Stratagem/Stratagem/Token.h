#pragma once

#include<stdio.h>
#include<string>
using std::string;

class Token {
	friend class Miner;
	friend class Spy;
public:
	Token(string newName, int newOwnership, int newRank);
	Token();
	~Token();

	string getName();
	int getOwnership();
	int getRank();
	virtual int isRankHigher(int rank2);
	bool getSelected();
	bool switchSelected();
	bool isRevealed();
	void setRevealed(bool b);

private:
	string name;
	int rank;
	int ownership;
	string path;
	bool selected;
	bool revealed;
};