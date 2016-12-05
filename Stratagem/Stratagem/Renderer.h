#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>
#include <iostream>
#include <string>
#include "GameState.h"

using sf::Vector2;
using sf::RenderWindow;
using sf::RectangleShape;
using sf::VideoMode;
using sf::Texture;
using sf::Mouse;
using std::cout;
using std::endl;

class Renderer
{
public:
	Renderer();
	void game();
	void rules();
	void renderGrid();
	void menu();
	void loadTextures(Texture * textures[27]);
	
private:
	Texture * mTextures[27];
	GameState * mGame;
	void creator();
	RectangleShape grid[10][10];
	RenderWindow * mWindow;
};