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

	void convert(int player1[4][10], int player2[4][10]);
	bool isGameOver();
	bool movePiece(int x, int y, int x2, int y2);
	bool attackPiece(int x, int y, int x2, int y2);
private:

	int remainingP1;
	int remainingP2;

	bool gameOver;
	Token * board[10][10];
};