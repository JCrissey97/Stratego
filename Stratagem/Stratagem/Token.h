#pragma once

#include<stdio.h>
#include<string>
#include <SFML\Graphics.hpp>
using std::string;

class Token : public sf::Sprite {
	friend class Miner;
	friend class Spy;
public:
	Token(string newName, int newOwnership, int newRank, string newPath);
	Token();
	~Token();

	string getName();
	int getOwnership();
	int getRank();
	virtual int isRankHigher(int rank2);

private:
	string name;
	int rank;
	int ownership;
	string path;
};