#pragma once
#include"Token.h"
#include<string>

using std::string;

class GameState {
public:
	GameState();
	~GameState();

	bool setTokenAt(int x, int y, string name, int ownership, int rank, string path);
	Token * getTokenAt(int x, int y);

	bool isGameOver();
	bool movePiece(int x, int y, int x2, int y2);
	bool attackPiece(int x, int y, int x2, int y2);
private:

	int remainingP1;
	int remainingP2;

	bool gameOver;
	Token * board[10][10];
};