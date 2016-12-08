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
	//instantiate member objects
	Texture * t = new Texture();
	t->loadFromFile("sidebar.png");
	Vector2<float> size(200, 740); //sidebar size
	mSidebar = new RectangleShape(size);
	mSidebar->setTexture(t);
	mSidebar->setPosition(600, 0);
	VideoMode mode(800, 740); //window size
	RenderWindow * window = new RenderWindow(mode, "Stratagem");
	mWindow = window;
	Texture * textures[27];
	for (int i = 0; i < 27; i++) //instantiate textures
	{
		textures[i] = new Texture();
	}
	this->loadTextures(textures);
	for (int i = 0; i < 27; i++)
	{
		mTextures[i] = textures[i]; //load textures to member
	}
	mGame = new GameState();
	this->renderGrid(); //name self-explanatory
}
void Renderer::game()
{
	bool keepGoing = creator(); //true if ready to continue to game
	if (keepGoing) for (int i = 0; i < 4; i++) //initializes p2 grid squares to unknown (question marks)
	{
		for (int j = 0; j < 10; j++)
		{
			mGrid[j][i]->setTexture(mTextures[25]);
		}
	}
	bool p1Turn = true; //keeps track of turns
	bool tokenSelected = false; //whether a token is selected
	int moveCount = 0; //scout can move twice, this keeps track so he can't move more (boolean int)
	Token * selectedToken = nullptr; //token that is selected, nullptr if not selected
	//create quit-to-menu button
	Vector2<float> size1(60, 60);
	Texture * buttonT = new Texture();
	buttonT->loadFromFile("closeout.png");
	RectangleShape button(size1);
	button.setTexture(buttonT);
	button.setOrigin(button.getGlobalBounds().width, 0);
	button.setPosition(800, 0);
	bool breakLoop = false;
	if (keepGoing)
	{
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
					if (mouseX <= 600 && mouseY <= 600)
					{
						if (p1Turn)
						{
							Token * t = mGame->getTokenAt(mouseX / 60, mouseY / 60); //returns square clicked, nullptr if empty
							if (selectedToken != nullptr) //if a token is already selected
							{
								Token * token = nullptr;
								int fromX = -1;
								int fromY = -1;
								bool found = false;
								for (int i = 0; i < 10; i++) //gets location in grid coords of selected token
								{
									for (int j = 0; j < 10; j++)
									{
										token = mGame->getTokenAt(i, j);
										if (token != nullptr)
										{
											if (token->getSelected())
											{
												fromX = i;
												fromY = j;
												found = true;
												break;
											}
										}
									}
									if (found) break;
								}
								if (t == selectedToken) //if the token clicked is the token selected
								{
									//deselect token and update relevent variables
									mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[12]);
									tokenSelected = false;
									token->switchSelected();
									selectedToken = nullptr;
									if (moveCount > 0)
									{
										p1Turn = false;
										moveCount = 0;
									}
								}
								else //if selected token is different from token clicked
								{
									int operation = 0; //stores type of operation performed
									//scout can move & attack in same turn, but must move first
									bool scoutAttacked = false; // keeps track of whether scout attacked
									if (moveCount < 1) operation = mGame->operate(fromX, fromY, mouseX / 60, mouseY / 60, selectedToken->getOwnership());
									else if (token->getRank() == 2) scoutAttacked = mGame->attackPiece(fromX, fromY, mouseX / 60, mouseY / 60);
									if (operation > 0 || scoutAttacked) //scoutAttacked == true & operation == false handled
									{
										//updates rendering
										mGrid[fromX][fromY]->setTexture(mTextures[26]);
										Token * newToken = mGame->getTokenAt(mouseX / 60, mouseY / 60);
										int rank = newToken->getRank();
										mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[(rank - 1)]); //access violation 
										if (!(operation == 1 && newToken->getRank() == 2)) //if not scout first move
										{
											//end turn
											p1Turn = false;
											moveCount = 0;
										}
										else //if scout first move
										{
											if (moveCount < 1) moveCount++; //increment, but check first just in case
										}
										if (!(operation == 1 && newToken->getRank() == 2) || scoutAttacked) //if anything but scout first move
										{
											//performe deselect, update rendering
											selectedToken->switchSelected();
											selectedToken = nullptr;
											tokenSelected = false;
											if (mGame->getTokenAt(mouseX / 60, mouseY / 60)->isRevealed()) //if revealed after attack, set to constantly visible
												mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[
													mGame->getTokenAt(mouseX / 60, mouseY / 60)->getRank() - 1]);
											else mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[12]); //if not revealed, return to "?"
										}
									}
									//		else if (moveCount > 0) unused
								}
							}
							else if (t != nullptr && t->getOwnership() == 1) //if no token selected & clicked square a valid token
							{
								//select token
								int rank = t->getRank();
								mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[(rank - 1)]);
								tokenSelected = true;
								selectedToken = t;
								t->switchSelected();
							}
						}
						else //if p2's turn, perform same operations
						{
							Token * t = mGame->getTokenAt(mouseX / 60, mouseY / 60);
							if (selectedToken != nullptr)
							{
								Token * token = nullptr;
								int fromX = -1;
								int fromY = -1;
								bool found = false;
								for (int i = 0; i < 10; i++)
								{
									for (int j = 0; j < 10; j++)
									{
										token = mGame->getTokenAt(i, j);
										if (token != nullptr)
										{
											if (token->getSelected())
											{
												fromX = i;
												fromY = j;
												found = true;
												break;
											}
										}
									}
									if (found) break;
								}
								if (t == selectedToken)
								{
									mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[25]);
									tokenSelected = false;
									token->switchSelected();
									selectedToken = nullptr;
									if (moveCount > 0)
									{
										moveCount = 0;
										p1Turn = true;
									}
								}
								else
								{
									int operation = 0;
									bool scoutAttacked = false;
									if (moveCount < 1) operation = mGame->operate(fromX, fromY, mouseX / 60, mouseY / 60, selectedToken->getOwnership());
									else if (token->getRank() == 2) scoutAttacked = mGame->attackPiece(fromX, fromY, mouseX / 60, mouseY / 60);
									if (operation > 0 || scoutAttacked)
									{
										mGrid[fromX][fromY]->setTexture(mTextures[26]);
										Token * newToken = mGame->getTokenAt(mouseX / 60, mouseY / 60);
										int rank = newToken->getRank();
										mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[rank + 12]);
										if (!(operation == 1 && token->getRank() == 2))
										{
											p1Turn = true;
											moveCount = 0;
										}
										else moveCount++;
										if (!(operation == 1 && token->getRank() == 2) || scoutAttacked)
										{
											if (mGame->getTokenAt(mouseX / 60, mouseY / 60)->isRevealed())
												mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[
													mGame->getTokenAt(mouseX / 60, mouseY / 60)->getRank() + 12]);
											else mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[25]);
											selectedToken->switchSelected();
											selectedToken = nullptr;
											tokenSelected = false;
										}
									}

								}
							}
							else if (t != nullptr && t->getOwnership() == 2) 
							{
								int rank = t->getRank();
								mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[rank + 12]);
								tokenSelected = true;
								selectedToken = t;
								t->switchSelected();
							}
						}
					}
					else if (button.getGlobalBounds().contains(mouseX, mouseY)) breakLoop = true;
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
			mWindow->draw(*mSidebar);
			mWindow->draw(button);
			mWindow->display();
			if (breakLoop) break;
			if (mGame->isGameOver())
			{

				//Prompt for user name

				string name = "PLAYER";
				cout << "Thanks for playing!" << endl << "Please enter your name here: ";
				cin >> name;

				bool success = false;

				//May need to change this depending on where you host your server

				sf::IpAddress rec = "sawtoothservers.ddns.net";
				unsigned short port = 4200;

				//This should be taken from the user
				char data[10];
				strcpy_s(data, name.c_str());
				sf::UdpSocket socket;
				if (socket.bind(4200) != sf::Socket::Done) {
					cout << "SOCKET BIND FAILED!" << endl;
				}
				char scores[50];

				//Send the player name to the server
				sf::Text * t0 = new sf::Text;
				sf::Text * t1 = new sf::Text;
				sf::Text * t2 = new sf::Text;
				sf::Text * t3 = new sf::Text;
				sf::Text * t4 = new sf::Text;
				sf::Text * t5 = new sf::Text;
				if (socket.send(data, 10, rec, port) == sf::Socket::Done)
				{
					//Again, change this if you host this elsewhere.

					sf::IpAddress sender = "sawtoothservers.ddns.net";
					unsigned short port = 4200;
					std::size_t recieved;
					socket.receive(scores, 50, recieved, sender, port);
					success = true;

					//REALLY BAD BUT FUNCTIONAL PART

					char a[10];
					memset(a, 0, 10);
					for (int i = 0; i < 10; i++) {
						a[i] = scores[i];
					}
					string s1(a);
					memset(a, 0, 10);
					for (int j = 10; j < 20; j++) {
						a[j - 10] = scores[j];
					}
					string s2(a);
					memset(a, 0, 10);
					for (int k = 20; k < 30; k++) {
						a[k - 20] = scores[k];
					}
					string s3(a);
					memset(a, 0, 10);
					for (int l = 30; l < 40; l++) {
						a[l - 30] = scores[l];
					}
					string s4(a);
					memset(a, 0, 10);
					for (int m = 40; m < 50; m++) {
						a[m - 40] = scores[m];
					}
					string s5(a);
					cout << endl << "Past 5 Players: " << endl << endl;
					cout << s1 << endl;
					cout << s2 << endl;
					cout << s3 << endl;
					cout << s4 << endl;
					cout << s5 << endl;
					//END REALLY BAD PART
					//Prints to console; this is where we should print to screen.

					//You're welcome to take a look at what we were trying to do here;
					//for some reason the font wouldn't display onscreen no matter what
					//position we fed it, text we set, or color we chose. I have no idea.

					//cout << "RECIEVED PLAYER LIST :" << endl;
					//sf::Font * f = new sf::Font;
					//sf::Color c = sf::Color::Yellow;
					//bool status = f->loadFromFile("Seagramtfb.ttf");
					//cout << status << endl;
					//t0->setString("RECENT PLAYERS:");
					//t0->setFont(*f);
					//t0->setFillColor(sf::Color::Yellow);
					////t0->setPosition(300, 300);
					//int x0 = t0->getGlobalBounds().width / 2;
					//int height = t0->getGlobalBounds().height;
					//t0->setOrigin(x0, 0);
					//cout << s1 << endl;

					//t1->setString(s1);
					//t1->setFont(*f);
					//t1->setFillColor(c);
					//t0->setPosition(0, 0);
					//int x1 = t1->getGlobalBounds().width / 2;
					//int height1 = t1->getGlobalBounds().height;
					//t1->setOrigin(x1, 0);
					//cout << s2 << endl;

					//t2->setString(s2);
					//t2->setFont(*f);
					//t2->setFillColor(c);
					//t0->setPosition(400, 300);
					//int x2 = t2->getGlobalBounds().width / 2;
					//int height2 = t2->getGlobalBounds().height;
					//t2->setOrigin(x2, 0);
					//cout << s3 << endl;

					//t3->setString(s3);
					//t3->setFont(*f);
					//t3->setFillColor(c);
					//t0->setPosition(400, 400);
					//int x3 = t3->getGlobalBounds().width / 2;
					//int height3 = t3->getGlobalBounds().height;
					//t3->setOrigin(x3, 0);
					//cout << s4 << endl;

					//t4->setString(s4);
					//t4->setFont(*f);
					//t4->setFillColor(c);
					//t0->setPosition(400, 500);
					//int x4 = t4->getGlobalBounds().width / 2;
					//int height4 = t4->getGlobalBounds().height;
					//t4->setOrigin(x4, 0);
					//cout << s5 << endl;

					//t5->setString(s5);
					//t5->setFont(*f);
					//t5->setFillColor(c);
					//t0->setPosition(-400, 600);
					//int x5 = t5->getGlobalBounds().width / 2;
					//int height5 = t5->getGlobalBounds().height;
					//t5->setOrigin(x5, 0);
					mWindow->close();
				}
				//while (mWindow->isOpen())
				//{
				//	Event e;
				//	while (mWindow->pollEvent(e))
				//	{
				//		if (e.type == Event::Closed) mWindow->close();
				//	}
				//	mWindow->clear();
				//	//mWindow->draw(...);
				//	mWindow->draw(*t0);
				//	mWindow->draw(*t1);
				//	mWindow->draw(*t2);
				//	mWindow->draw(*t3);
				//	mWindow->draw(*t4);
				//	mWindow->draw(*t5);
				//	mWindow->display();
				//}

			}
		}
	}
}

void Renderer::rules()
{
	Vector2<float> size(800, 740);
	Texture * bgT = new Texture();
	bgT->loadFromFile("rules.png"); //load rules texture
	RectangleShape bg(size);
	bg.setTexture(bgT);
	size.x = 60;
	size.y = 60;
	Texture * buttonT = new Texture();
	buttonT->loadFromFile("closeout.png"); //load return-to-menu button
	RectangleShape button(size);
	button.setTexture(buttonT);
	button.setOrigin(button.getGlobalBounds().width, 0);
	button.setPosition(800, 0);
	bool breakLoop = false;
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
				//if click return to menu, break the loop
				if (button.getGlobalBounds().contains(mouseX, mouseY)) breakLoop = true;
			}
		}
		mWindow->clear();
		mWindow->draw(bg);
		mWindow->draw(button);
		mWindow->display();
		if (breakLoop) break;
	}
}
// renders the main menu
void Renderer::menu()
{
	Texture * bgT = new Texture();
	bgT->loadFromFile("MENU.png"); // render menu background
	Vector2<float> size(400, 350);
	RectangleShape bg(size);
	bg.scale(2.0f, 2.0f);
	bg.setTexture(bgT);
	// render buttons
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
				if (playButton.getGlobalBounds().contains(mouseX, mouseY)) //if clicked on play button
				{
					this->game(); //start game
				}
				if (rulesButton.getGlobalBounds().contains(mouseX, mouseY)) //if clicked on rules button
				{
					this->rules(); // go to rules game
				}
			}
		}
		mWindow->clear();
		mWindow->draw(bg); //draw background
		//draw buttons
		mWindow->draw(playButton);
		mWindow->draw(rulesButton);
		mWindow->display();

	}
}

bool Renderer::creator()
{
	//load return-to-menu button (Yellow "X")
	Vector2<float> size1(60, 60);
	Texture * buttonT = new Texture();
	buttonT->loadFromFile("closeout.png");
	RectangleShape button(size1);
	button.setTexture(buttonT);

	//sets the origin to the upper right corner to make placement easier
	button.setOrigin(button.getGlobalBounds().width, 0);
	button.setPosition(800, 0); //sets position to upper right corner
	bool breakLoop = false; //represents player's desire to return to menu
	//holds max number of each rank
	int maxRanks[] = { 1, 8, 5, 4, 4, 4, 3, 2, 1, 1, 6, 1 };
	int pieces[10][4]; //represents rank at location x, y within bounds of current player's placeable area
	for (int i = 0; i < 10; i++) //initialize pieces
	{
		for (int j = 0; j < 4; j++)
		{
			pieces[i][j] = -1;
		}
	}
	bool toNext = false; //true if piece placement is complete
	while (mWindow->isOpen())
	{
		int currRanks[12]; //represents current number of each rank on field
		for (int i = 0; i < 12; i++)
		{
			currRanks[i] = 0;
		}
		for (int i = 0; i < 10; i++) //loads currRanks
		{
			for (int j = 0; j < 4; j++)
			{
				if (pieces[i][j] > -1) currRanks[pieces[i][j]]++;
			}
		}
		Event e;
		while (mWindow->pollEvent(e))
		{
			if (e.type == Event::Closed) mWindow->close();
			if (e.type == Event::MouseButtonReleased)
			{
				int mouseX = Mouse::getPosition(*mWindow).x;
				int mouseY = Mouse::getPosition(*mWindow).y;
				if (mouseY >= 360 && isSquareAt(mouseX, mouseY)) //if mouse is within legal bounds to click
				{
					int row = (mouseY - 360) / 60;
					int column = mouseX / 60;
					if (pieces[column][row] >= 11) pieces[column][row] = 0;
					else pieces[column][row] += 1;

					//cycles through ranks until it finds one that has not been maxed out
					while (currRanks[pieces[column][row]] >= maxRanks[pieces[column][row]])
					{
						if (pieces[column][row] >= 11) pieces[column][row] = 0;
						else pieces[column][row] += 1;
					}

					//set the texture
					mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[pieces[column][row]]);


				}
				if (button.getGlobalBounds().contains(mouseX, mouseY)) return false; //return to menu
			}
		}
		mWindow->clear();
		for (int i = 0; i < 10; i++) //draw game board
		{
			for (int j = 0; j < 10; j++)
			{
				mWindow->draw(*mGrid[i][j]);
			}
		}
		//draw extra elements
		mWindow->draw(*mSidebar); //legend
		mWindow->draw(button); //return-to-menu button
		mWindow->display();
		toNext = true;
		for (int i = 0; i < 12; i++)
		{
			if (!(maxRanks[i] == currRanks[i]))
			{
				toNext = false;
				break;
			}
		}
		if (toNext) break; //breaks loop if all ranks are maxed out (all spaces are filled)
	}

	//rinse & repeat for player 2
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
	if (!breakLoop);
	{
		while (mWindow->isOpen())
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
					if (pieces2[i][j] > -1) currRanks[pieces2[i][j]]++;
				}
			}
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

						if (pieces2[column][row] >= 11) pieces2[column][row] = 0;
						else pieces2[column][row] += 1;

						while (currRanks[pieces2[column][row]] >= maxRanks[pieces2[column][row]])
						{
							if (pieces2[column][row] >= 11) pieces2[column][row] = 0;
							else pieces2[column][row] += 1;
						}
						mGrid[mouseX / 60][mouseY / 60]->setTexture(mTextures[pieces2[column][row] + 13]);
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
			mWindow->draw(*mSidebar);
			mWindow->draw(button);
			mWindow->display();
			toNext = true;
			for (int i = 0; i < 12; i++)
			{
				if (!(maxRanks[i] == currRanks[i]))
				{
					toNext = false;
					break;
				}
			}
			if (toNext) break;
			if (breakLoop) return false;
		}
	}

	//unused
	/*
	RectangleShape * rectangles[10][10];

	for (int i = 0; i <= 9; i++)
	{
	for (int j = 0; j <= 9; j++)
	{

	}
	}*/
	int * pPieces[10][4];
	int * pPieces2[10][4];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pPieces[i][j] = &pieces[i][j];
			pPieces2[i][j] = &pieces2[i][j];
		}
	}
	mGame->convert(pPieces, pPieces2); //update GameState, loads tokens
	return toNext; //returns whether ready to coninue
}
void Renderer::renderGrid()
{
	Vector2<float> size(60, 60);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//render grid square at (i,j)
			mGrid[i][j] = new RectangleShape(size);
			mGrid[i][j]->setTexture(mTextures[26]);
			Vector2<float> pos(i * 60, (j * 60)); //calculate real position in window coords
			mGrid[i][j]->setPosition(pos);
		}
	}
}
void Renderer::loadTextures(Texture * textures[27])
{
	//since pointers, changes are retained
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

//Following functions were written, but then went unused
//Useful, but unnecessary.
//RectangleShape * Renderer::getSquareAt(int x, int y)
//{
//	return mGrid[x / 60][y / 60];
//}
//
bool Renderer::isSquareAt(int x, int y)
{
	bool result = false;
	for (int i = 0; i < 10; i++) //iterate through grid squares
	{
		for (int j = 0; j < 10; j++)
		{
			if (mGrid[i][j]->getGlobalBounds().contains(x, y)) result = true; //if grid contains supplied point, return true
		}
	}
	return result;
}
