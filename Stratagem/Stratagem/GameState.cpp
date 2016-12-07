#include"GameState.h"
#include"Token.h"
#include"Spy.h"
#include"Miner.h"
#include <iostream>
using std::cout;
using std::endl;

GameState::GameState() {
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++) {
			board[i][j] = nullptr;
		}
	}
	gameOver = false;
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

int GameState::operate(int x, int y, int x2, int y2, int owner)
{
	if (board[x][y] == nullptr)
	{
		return 0;
	}
	else if (board[x][y] != nullptr)
	{
		if (board[x][y]->getOwnership() != owner) 
		{
			return 0;
		}
		if (board[x][y]->getRank() == 12 || board[x][y]->getRank() == 11) 
		{
			return 0;
		}
		else if (board[x2][y2] == nullptr) 
		{
			bool check = false;
			check = movePiece(x, y, x2, y2);

			if (check == true)
			{
				return 1;
			}
			else if (check == false)
			{
				return 0;
			}
			
		}
		else if (board[x2][y2] != nullptr) 
		{
			if (board[x2][y2]->getOwnership() == owner) 
			{
				return 0;
			}
			else 
			{
				if ((x == x2 && y + 1 == y2) || (x == x2 && y - 1 == y2) || 
					(x + 1 == x2 && y  == y2) || (x - 1 == x2 && y == y2)) 
				{
					bool check = false;
					check = attackPiece(x, y, x2, y2);

					if (check == true)
					{
						return 1;
					}
					else if (check == false)
					{
						return 0;
					}
				}
				else 
				{
					return 0;
				}
			}
		}
	}
}

//column-row
void GameState::convert(int * player1[10][4], int * player2[10][4])
{
	//Create tokens for player 2
	for (int x=0; x <= 9; x++)
	{
		for (int y = 0; y <= 3; y++)
		{
			int temp = 0;
			temp = *player2[x][y];
			cout << temp << endl;
			setTokenAt(x, y, 2, temp + 1);
		}
	}

	//Create tokens for player 1
	for (int x2 = 0; x2 <= 9; x2++)
	{
		for (int y2 = 6; y2 <= 9; y2++)
		{
			int temp = 0;
			temp = *player1[x2][y2-6];
			cout << temp << endl;
			setTokenAt(x2, y2, 1, temp + 1);
		}
	}
}

bool GameState::setTokenAt(int x, int y, int ownership, int rank)
{
	std::string name = " ";

	switch (rank)
	{
	case 1: name = "Spy"; break;
	case 2: name = "Scout"; break;
	case 3: name = "Miner"; break;
	case 4: name = "Sergeants"; break;
	case 5: name = "Lieutenants"; break;
	case 6: name = "Captains"; break;
	case 7: name = "Majors"; break;
	case 8: name = "Colonels"; break;
	case 9: name = "General"; break;
	case 10: name = "Marshal"; break;
	case 11: name = "Bomb"; break;
	case 12: name = "Gem"; break;
	default: cout << "ERROR"; break;
	}

	Token * newT;
    if (rank == 1) 
	{
		newT = new Spy(name, ownership, rank);
	}
	else if (rank == 3) 
	{
		newT = new Miner(name, ownership, rank);
	}
	else {
		newT = new Token(name, ownership, rank);
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
	if (x < 10 && y < 10 && x2 < 10 && y2 < 10) {
		Token * temp = board[x][y];
		if (temp != nullptr) {
			int rank = temp->getRank();
			if (rank == 12 || rank == 11) {
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
		if ((x == x2 && y + 1 == y2) || (x == x2 && y - 1 == y2) ||
			(x + 1 == x2 && y == y2) || (x - 1 == x2 && y == y2))
		{
			Token * temp2 = board[x2][y2];
			if (temp2 != nullptr) {
				int rank2;
				rank2 = temp2->getRank();
				int elim;
				elim = temp->isRankHigher(rank2);
				if (rank2 == 12)
				{
					gameOver = true;
					cout << "GAME OVER! " << "Player " << temp->getOwnership() << " won the match!" << endl;
				}
				else if (elim == 1) {
					board[x2][y2] = board[x][y];
					board[x2][y2]->setRevealed(true);
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
			else return false;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}