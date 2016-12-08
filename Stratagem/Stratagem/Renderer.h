#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>
#include <iostream>
#include <string>
#include "GameState.h"
#include "SFML\Network.hpp"

using sf::Vector2;
using sf::RenderWindow;
using sf::RectangleShape;
using sf::VideoMode;
using sf::Texture;
using sf::Mouse;
using sf::Event;
using std::cout;
using std::endl;
using std::cin;

class Renderer
{
public:
	~Renderer(); //destroys all the member pointers
	Renderer(); //instantiates the member objects required to display the game

	/*	JC:
	*	This function renders the core game, displays it on the screen, and manages the GameState
	*	Requires that all member objects are instantiated
	*	NG:
	*	
	*/
	void game();

	/*	JC:
	*	This function renders a simple rules/how-to-play screen
	*	Requires only a RenderWindow to run
	*	Uses member mWindow
	*/
	void rules();

	/*	JC:
	*	This function loads the game board as a grid, which initializes with empty squares
	*/
	void renderGrid();

	/*	JC:
	*	Loads main menu, and all necessary components that weren't member objects
	*/
	void menu();

	/*	JC:
	*	Loads all grid square textures into an array of size 27
	*	Allows random access of all reused textures for the game board
	*/
	void loadTextures(Texture * textures[27]);

	// This function went unused
//	RectangleShape * getSquareAt(int x, int y);

	/*	JC:
	*	Takes a location within the window and returns true if it is within the bounds of the board	
	*/
	bool isSquareAt(int x, int y);
	
private:
	Texture * mTextures[28];
	GameState * mGame;

	/*	JC:
	*	Loads the game state where the players choose the locations of their pieces
	*	Requires that all member objects be instantiated
	*	Returns false if the player wishes to return to menu
	*	Else returns true
	*/
	bool creator();
	RectangleShape * mGrid[10][10];
	RectangleShape * mSidebar;
	RenderWindow * mWindow;
};