#include "Renderer.h"

Renderer::Renderer()
{
	VideoMode mode(700, 700);
	RenderWindow * window = new RenderWindow(mode, "Stratagem");
	mWindow = window;
	Texture * textures[27];
	for (int i = 0; i < 27; i++)
	{
		textures[i] = new Texture();
	}
	this->loadTextures(textures);
	for (int i = 0; i < 27; i++)
	{
		mTextures[i] = textures[i];
	}
	mGame = new GameState();
	this->renderGrid();	
}
void Renderer::game()
{
	Texture * textures[27];
	creator();
		/*while (isOpen())
		{

		}*/
}

void Renderer::rules()
{

}

void Renderer::menu()
{
	Texture * bgT = new Texture();
	bgT->loadFromFile("MENU.png");
	Vector2<float> size(350, 300);
	RectangleShape bg(size);
	bg.scale(2.0f, 2.0f);

	Texture * play = new Texture();
	play->loadFromFile("STARTBUTTON.png");
	Texture * rules = new Texture();
	rules->loadFromFile("RULESBUTTON.png");
	size.x = 300;
	size.y = 100;
	RectangleShape playButton(size);
	RectangleShape rulesButton(size);
	playButton.setTexture(play);
	rulesButton.setTexture(rules);
	rulesButton.setOrigin(rulesButton.getGlobalBounds().width, 0);
	playButton.setPosition(10, 320);
	rulesButton.setPosition(690, 320);
	while (mWindow->isOpen())
	{
		mWindow->clear();
		mWindow->draw(bg);
		mWindow->draw(playButton);
		mWindow->draw(rulesButton);
		mWindow->display();
	}
}

void Renderer::creator()
{
	while (mWindow->isOpen())
	{
		mWindow->clear();
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				mWindow->draw(grid[i][j]);
			}
		}
		mWindow->display();
	}
	/*int numRank[] = { 1, 8, 5, 4, 4, 6, 3, 8, 1, 1, 6, 1 };
	RectangleShape * rectangles[10][10];

	for (int i = 0; i <= 9; i++)
	{
	for (int j = 0; j <= 9; j++)
	{

	}
	}*/
}
void Renderer::renderGrid()
{
	Vector2<float> size(50, 50);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{

			grid[i][j] = RectangleShape(size);
			grid[i][j].setTexture(mTextures[26]);
			Vector2<float> pos(i * 50, (j * 50) + 100);
		}
	}
}
void Renderer::loadTextures(Texture * textures[27])
{
	textures[0]->loadFromFile("spy.png");
	textures[1]->loadFromFile("scout.png");
	textures[2]->loadFromFile("miner.png");
	textures[3]->loadFromFile("sergeant.png");
	textures[4]->loadFromFile("lieutenant.png");
	textures[5]->loadFromFile("captain.png");
	textures[6]->loadFromFile("major.png");
	textures[7]->loadFromFile("colonel.png");
	textures[8]->loadFromFile("general.png");
	textures[9]->loadFromFile("marshall.png");
	textures[10]->loadFromFile("gem.png");
	textures[11]->loadFromFile("bomb.png");
	textures[12]->loadFromFile("spy2.png");
	textures[14]->loadFromFile("scout2.png");
	textures[15]->loadFromFile("miner2.png");
	textures[16]->loadFromFile("sergeant2.png");
	textures[17]->loadFromFile("lieutenant2.png");
	textures[18]->loadFromFile("captain2.png");
	textures[19]->loadFromFile("major2.png");
	textures[20]->loadFromFile("colonel2.png");
	textures[21]->loadFromFile("general2.png");
	textures[22]->loadFromFile("marshall2.png");
	textures[23]->loadFromFile("gem2.png");
	textures[24]->loadFromFile("bomb2.png");
	textures[25]->loadFromFile("blankp2.png");
	textures[26]->loadFromFile("blanksquare.png");
}