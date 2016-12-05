#include"GameState.h"
#include"Token.h"
#include"Spy.h"
#include"Miner.h"

GameState::GameState() {
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++) {
			board[i][j] = nullptr;
		}
	}
}
GameState::~GameState() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j] != nullptr) {
				delete board[i][j];
			}
		}
	}
}

bool GameState::setTokenAt(int x, int y, string name, int ownership, int rank, string path) {
	Token * newT;
	if (rank == 1) {
		newT = new Spy(name, ownership, rank, path);
	}
	else if (rank == 3) {
		newT = new Miner(name, ownership, rank, path);
	}
	else {
		newT = new Token(name, ownership, rank, path);
	}
	board[x][y] = newT;
	if (board[x][y] != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

Token * GameState::getTokenAt(int x, int y) {
	return board[x][y];
}

bool GameState::isGameOver() {
	return gameOver;
}

bool GameState::movePiece(int x, int y, int x2, int y2) {
	if (x <= 10 || y <= 10 || x2 <= 10 || y2 <= 10) {
		Token * temp = board[x][y];
		if (temp != nullptr) {
			int rank = temp->getRank();
			if (rank == 12 || rank == 13) {
				return false;
			}
			else if (rank == 2) {
				if (board[x2][y2] == nullptr) {
					if (x == x2 || y == y2) {
						board[x2][y2] = temp;
						board[x][y] = nullptr;
						return true;
					}
				}
			}
			else {
				if (board[x2][y2] == nullptr) {
					if (x == x2) 
					{
						if (y2 == y + 1 || y2 == y - 1) {
							board[x2][y2] = temp;
							board[x][y] = nullptr;
							return true;
						}
						else {
							return false;
						}
					}
					else if (x2 == x + 1 || x2 == x - 1) {
						if (y == y2) {
							board[x2][y2] = temp;
							board[x][y] = nullptr;
							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return false;
}

bool GameState::attackPiece(int x, int y, int x2, int y2) {
	Token * temp = board[x][y];
	if (temp != nullptr) {
		Token * temp2 = board[x2][y2];
		if (temp2 != nullptr) {
			int rank2;
			rank2 = temp2->getRank();
			int elim;
			elim = temp->isRankHigher(rank2);
			if (elim == 1) {
				board[x2][y2] = board[x][y];
				board[x][y] = nullptr;
				delete temp2;
				return true;
			}
			else if (elim == 2) {
				board[x][y] = nullptr;
				delete temp;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}