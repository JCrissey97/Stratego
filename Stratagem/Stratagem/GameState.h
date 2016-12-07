#pragma once
#include"Token.h"
#include<string>

using std::string;

class GameState {
public:
	GameState();
	~GameState();

	bool GameState::setTokenAt(int x, int y, int ownership, int rank);
	Token * getTokenAt(int x, int y);

	int operate(int x, int y, int x2, int y2, int owner);
	void convert(int * player1[10][4], int * player2[10][4]);
	bool isGameOver();
	bool movePiece(int x, int y, int x2, int y2);
	bool attackPiece(int x, int y, int x2, int y2);
private:

	int remainingP1;
	int remainingP2;

	bool gameOver;
	Token * board[10][10];
};