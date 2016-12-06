#include "Renderer.h"

Renderer::~Renderer()
{
	for (int i = 0; i < 27; i++)
	{
		delete mTextures[i];

	}
	delete mGame;
	delete mWindow;
}
Renderer::Renderer()
{
	VideoMode mode(800, 728);
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
	creator();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			mGrid[j][i]->setTexture(mTextures[25]);
		}
	}
	while (mWindow->isOpen())
	{
		Event e;
		while (mWindow->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				mWindow->close();
			}
		}
		mWindow->clear();
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				mWindow->draw(*mGrid[i][j]);
			}
		}
		mWindow->display();
	}
}

void Renderer::rules()
{

}

void Renderer::menu()
{
	Texture * bgT = new Texture();
	bgT->loadFromFile("MENU.png");
	Vector2<float> size(400, 350);
	RectangleShape bg(size);
	bg.scale(2.0f, 2.0f);
	bg.setTexture(bgT);

	Texture * play = new Texture();
	play->loadFromFile("PLAYBUTTON.png");
	Texture * rules = new Texture();
	rules->loadFromFile("RULESBUTTON.png");
	size.x = 300;
	size.y = 100;
	RectangleShape playButton(size);
	RectangleShape rulesButton(size);
	playButton.setTexture(play);
	rulesButton.setTexture(rules);
	rulesButton.setOrigin(rulesButton.getGlobalBounds().width, 0);
	playButton.setPosition(35, 320);
	rulesButton.setPosition(765, 320);
	while (mWindow->isOpen())
	{
		Event e;
		while (mWindow->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				mWindow->close();
			}
			if (e.type == Event::MouseButtonReleased)
			{
				int mouseX = Mouse::getPosition(*mWindow).x;
				int mouseY = Mouse::getPosition(*mWindow).y;
				if (playButton.getGlobalBounds().contains(mouseX, mouseY))
				{
					this->game();
				}
				if (rulesButton.getGlobalBounds().contains(mouseX, mouseY))
				{
					this->rules();
				}
			}
		}
		mWindow->clear();
		mWindow->draw(bg);
		mWindow->draw(playButton);
		mWindow->draw(rulesButton);
		mWindow->display();

	}
}

bool Renderer::creator()
{
	int numRank[] = { 1, 8, 5, 4, 4, 4, 3, 2, 1, 1, 6, 1 };
	int pieces[10][4];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pieces[i][j] = -1;
		}
	}
	bool toNext = false;
	while (mWindow->isOpen())
	{

		Event e;
		while (mWindow->pollEvent(e))
		{
			if (e.type == Event::Closed) mWindow->close();
			if (e.type == Event::MouseButtonReleased)
			{
				int mouseX = Mouse::getPosition(*mWindow).x;
				int mouseY = Mouse::getPosition(*mWindow).y;
				if (mouseY >= 360 && isSquareAt(mouseX, mouseY))
				{
					int currRanks[12];
					for (int i = 0; i < 12; i++)
					{
						currRanks[i] = 0;
					}
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (pieces[i][j] > -1) currRanks[pieces[i][j]]++;
						}
					}
					int row = (mouseY - 360) / 60;
					int column = mouseX / 60;
					int piece = pieces[column][row];
					if (pieces[column][row] < 0)
					{
						pieces[column][row] = 0;
					}

					while (currRanks[pieces[column][row]] >= numRank[pieces[column][row]])
					{
						if (pieces[column][row] >= 11) pieces[column][row] = 0;
						else pieces[column][row] += 1;
					}

					mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[piece]);
					if (piece >= 11) pieces[column][row] = 0;
					else pieces[column][row] += 1;

				}
			}
		}
		mWindow->clear();
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				mWindow->draw(*mGrid[i][j]);
			}
		}
		mWindow->display();
		for (int i = 0; i < 12; i++)
		{
			if (toNext)
			{
				break;
			}
		}
	}

	int pieces2[10][4];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pieces2[i][j] = -1;
		}
	}
	toNext = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			mGrid[j][i + 6]->setTexture(mTextures[12]);
		}
	}
	while (mWindow->isOpen())
	{

		Event e;
		while (mWindow->pollEvent(e))
		{
			if (e.type == Event::Closed) mWindow->close();
			if (e.type == Event::MouseButtonReleased)
			{
				int mouseX = Mouse::getPosition(*mWindow).x;
				int mouseY = Mouse::getPosition(*mWindow).y;
				if (mouseY <= 240 && isSquareAt(mouseX, mouseY))
				{
					int row = mouseY / 60;
					int column = mouseX / 60;
					int currRanks[12];
					for (int i = 0; i < 12; i++)
					{
						currRanks[i] = 0;
					}
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (pieces2[i][j] > -1)currRanks[pieces2[i][j]]++;
						}
					}
					if (pieces2[column][row] > -1) //fix - see line 162
					{
						while (currRanks[pieces2[column][row]] >= numRank[pieces2[column][row]])
						{
							if (pieces2[column][row] >= 11) pieces2[column][row] = 0;
							else pieces2[column][row] += 1;
						}
					}
					int piece = pieces2[column][row];
					mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[piece]);
					if (piece >= 11) pieces2[column][row] = 0;
					else pieces2[column][row] += 1;

				}
			}
		}
		mWindow->clear();
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				mWindow->draw(*mGrid[i][j]);
			}
		}
		mWindow->display();

		if (toNext)
		{
			//send data
			break;
		}
	}
	/*
	RectangleShape * rectangles[10][10];

	for (int i = 0; i <= 9; i++)
	{
	for (int j = 0; j <= 9; j++)
	{

	}
	}*/
	return toNext;
}
void Renderer::renderGrid()
{
	Vector2<float> size(60, 60);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{

			mGrid[i][j] = new RectangleShape(size);
			mGrid[i][j]->setTexture(mTextures[26]);
			Vector2<float> pos(i * 60, (j * 60));
			mGrid[i][j]->setPosition(pos);
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
	textures[10]->loadFromFile("bomb.png");
	textures[11]->loadFromFile("gem.png");
	textures[12]->loadFromFile("blankp1.png");
	textures[13]->loadFromFile("spy2.png");
	textures[14]->loadFromFile("scout2.png");
	textures[15]->loadFromFile("miner2.png");
	textures[16]->loadFromFile("sergeant2.png");
	textures[17]->loadFromFile("lieutenant2.png");
	textures[18]->loadFromFile("captain2.png");
	textures[19]->loadFromFile("major2.png");
	textures[20]->loadFromFile("colonel2.png");
	textures[21]->loadFromFile("general2.png");
	textures[22]->loadFromFile("marshall2.png");
	textures[23]->loadFromFile("bomb2.png");
	textures[24]->loadFromFile("gem2.png");
	textures[25]->loadFromFile("blankp2.png");
	textures[26]->loadFromFile("blanksquare.png");
}

RectangleShape * Renderer::getSquareAt(int x, int y)
{
	return mGrid[x / 60][y / 60];
}

bool Renderer::isSquareAt(int x, int y)
{
	bool result = false;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (mGrid[i][j]->getGlobalBounds().contains(x, y)) result = true;
		}
	}
	return result;
}
