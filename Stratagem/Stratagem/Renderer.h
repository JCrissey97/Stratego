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
	~Renderer();
	Renderer();
	void game();
	void rules();
	void renderGrid();
	void menu();
	void loadTextures(Texture * textures[27]);
	RectangleShape * getSquareAt(int x, int y);
	bool isSquareAt(int x, int y);
	
private:
	Texture * mTextures[28];
	GameState * mGame;
	bool creator();
	RectangleShape * mGrid[10][10];
	RectangleShape * mSidebar;
	RenderWindow * mWindow;
};