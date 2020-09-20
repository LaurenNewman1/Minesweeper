#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Board.h"
#include "Tile.h"
#include "Icon.h"
#include <map>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
using namespace sf;

void InitializeDebugs(map<string, Icon> &icons, Board *board, sf::RenderWindow &window);
void InitializeBoard(map<string, Icon> &icons, Board *board, sf::RenderWindow &window);
void InitializeSmile(map<string, Icon> &icons, Board *board, sf::RenderWindow &window);
void InitializeCounter(map<string, Icon> &icons, Board *board, sf::RenderWindow &window);
Icon& GetNumIcon(map<string, Icon> &icons, Board *board, Tile *tile, sf::RenderWindow &window);
void BlankSquareClicked(map<string, Icon> &icons, Board *board, Tile *tile, sf::RenderWindow &window);
void DebugMode(Board *board);
void RevertDebugMode(Board *board);
void RevealAllMines(Board *board);
void FlagAllMines(Board *board);
void CheckForWin(map<string, Icon> &icons, Board *board, sf::RenderWindow &window);

int main()
{
	map <string, Icon> icons;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

	// Initialize Icons
	Icon debug("../images/debug.png");
	icons.emplace("debug", debug);
	Icon digits("../images/digits.png");
	icons.emplace("digits", digits);
	Icon face_happy("../images/face_happy.png");
	icons.emplace("face_happy", face_happy);
	Icon face_lose("../images/face_lose.png");
	icons.emplace("face_lose", face_lose);
	Icon face_win("../images/face_win.png");
	icons.emplace("face_win", face_win);
	Icon flag("../images/flag.png");
	icons.emplace("flag", flag);
	Icon mine("../images/mine.png");
	icons.emplace("mine", mine);
	Icon number_1("../images/number_1.png");
	icons.emplace("number_1", number_1);
	Icon number_2("../images/number_2.png");
	icons.emplace("number_2", number_2);
	Icon number_3("../images/number_3.png");
	icons.emplace("number_3", number_3);
	Icon number_4("../images/number_4.png");
	icons.emplace("number_4", number_4);
	Icon number_5("../images/number_5.png");
	icons.emplace("number_5", number_5);
	Icon number_6("../images/number_6.png");
	icons.emplace("number_6", number_6);
	Icon number_7("../images/number_7.png");
	icons.emplace("number_7", number_7);
	Icon number_8("../images/number_8.png");
	icons.emplace("number_8", number_8);
	Icon test_1("../images/test_1.png");
	icons.emplace("test_1", test_1);
	Icon test_2("../images/test_2.png");
	icons.emplace("test_2", test_2);
	Icon test_3("../images/test_3.png");
	icons.emplace("test_3", test_3);
	Icon tile_hidden("../images/tile_hidden.png");
	icons.emplace("tile_hidden", tile_hidden);
	Icon tile_revealed("../images/tile_revealed.png");
	icons.emplace("tile_revealed", tile_revealed);

	Board *board = new Board;

	while (window.isOpen())
	{
		window.clear(sf::Color::White);

		// Update tile displays
		InitializeBoard(icons, board, window);

		// Update counter
		InitializeCounter(icons, board, window);
		
		// Update Smiley face
		InitializeSmile(icons, board, window);

		// Set debug icons
		InitializeDebugs(icons, board, window);

		// Check for win
		CheckForWin(icons, board, window);

		window.display();

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{

			// check the type of the event...
			switch (event.type)
			{
				// window closed
				case sf::Event::Closed:
				{
					window.close();
					break;
				}
				// key pressed
				case sf::Event::MouseButtonPressed:
				{
					if (event.mouseButton.button == sf::Mouse::Left) // Left
					{
						// Clicked tile
						if (!board->lose && !board->win)
						{
							for (int i = 0; i < 400; i++)
							{
								if (event.mouseButton.x / 32 == (int)board->tiles.at(i)->position.x / 32
									&& event.mouseButton.y / 32 == (int)board->tiles.at(i)->position.y / 32
									&& board->tiles.at(i)->isMine == false && board->tiles.at(i)->isFlagged == false)
								{
									if (board->tiles.at(i)->isRevealed == false)
									{
										board->tiles.at(i)->isRevealed = true;
										board->numRevealed++;
									}
									break;
								}
								else if (event.mouseButton.x / 32 == (int)board->tiles.at(i)->position.x / 32
									&& event.mouseButton.y / 32 == (int)board->tiles.at(i)->position.y / 32
									&& board->tiles.at(i)->isMine == true && board->tiles.at(i)->isFlagged == false)
								{
									if (board->tiles.at(i)->isRevealed == false)
									{
										board->tiles.at(i)->isRevealed = true;
									}
									board->tiles.at(i)->isMine = true;
									board->lose = true;
									RevealAllMines(board);
									break;
								}
							}
						}
						// Clicked face
						if (event.mouseButton.x > 368 && event.mouseButton.x < 432
							&& event.mouseButton.y > 512 && event.mouseButton.y < 576)
						{
							board = new Board;
							break;
						}
						// Clicked Debug
						if (event.mouseButton.x > 496 && event.mouseButton.x < 560
							&& event.mouseButton.y > 512 && event.mouseButton.y < 576)
						{
							if (!board->inDebugMode)
								DebugMode(board);
							else
								RevertDebugMode(board);
							break;
						}
						// Clicked Test 1
						if (event.mouseButton.x > 560 && event.mouseButton.x < 624
							&& event.mouseButton.y > 512 && event.mouseButton.y < 576)
						{
							board = new Board("../boards/testboard1.brd");
							break;
						}
						// Clicked Test 2
						if (event.mouseButton.x > 624 && event.mouseButton.x < 688
							&& event.mouseButton.y > 512 && event.mouseButton.y < 576)
						{
							board = new Board("../boards/testboard2.brd");
							break;
						}
						// Clicked Test 3
						if (event.mouseButton.x > 688 && event.mouseButton.x < 752
							&& event.mouseButton.y > 512 && event.mouseButton.y < 576)
						{
							board = new Board("../boards/testboard3.brd");
							break;
						}
					}
					else if (!board->lose && !board->win) // Right
					{
						for (int i = 0; i < 400; i++)
						{ 
							if (event.mouseButton.x / 32 == (int)board->tiles.at(i)->position.x / 32
								&& event.mouseButton.y / 32 == (int)board->tiles.at(i)->position.y / 32
								&& board->tiles.at(i)->isRevealed == false && board->tiles.at(i)->isFlagged == false)
							{
								board->tiles.at(i)->isFlagged = true;
								board->numFlags++;
								break;
							}
							else if (event.mouseButton.x / 32 == (int)board->tiles.at(i)->position.x / 32
								&& event.mouseButton.y / 32 == (int)board->tiles.at(i)->position.y / 32
								&& board->tiles.at(i)->isRevealed == false && board->tiles.at(i)->isFlagged == true)
							{
								board->tiles.at(i)->isFlagged = false;
								board->numFlags--;
								break;
							}
						}
					}
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}
	return 0;
}

void InitializeBoard(map<string, Icon> &icons, Board *board, sf::RenderWindow &window)
{
	int i = 0;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 25; x++)
		{
			board->tiles.at(i)->position = sf::Vector2f(x * 32.0f, y * 32.0f);
			// Normal hidden tile
			if (board->tiles.at(i)->isRevealed == false && board->tiles.at(i)->isFlagged == false)
			{
				icons["tile_hidden"].sprite.setPosition(board->tiles.at(i)->position);
				window.draw(icons["tile_hidden"].sprite);
			}
			// Win
			else if (board->win == true && board->tiles.at(i)->isFlagged == true)
			{
				// Grey background tile
				icons["tile_hidden"].sprite.setPosition(board->tiles.at(i)->position);
				window.draw(icons["tile_hidden"].sprite);
				// Mine tile
				icons["mine"].sprite.setPosition(board->tiles.at(i)->position);
				window.draw(icons["mine"].sprite);
				// Flag tile
				icons["flag"].sprite.setPosition(board->tiles.at(i)->position);
				window.draw(icons["flag"].sprite);
			}
			// Flagged tile
			else if (board->tiles.at(i)->isRevealed == false && board->tiles.at(i)->isFlagged == true)
			{
				// Grey background tile
				icons["tile_hidden"].sprite.setPosition(board->tiles.at(i)->position);
				window.draw(icons["tile_hidden"].sprite);
				// Flag tile
				icons["flag"].sprite.setPosition(board->tiles.at(i)->position);
				window.draw(icons["flag"].sprite);
			}
			// Revealed tile
			else if (board->tiles.at(i)->isRevealed == true && board->tiles.at(i)->isMine == false)
			{
				// Grey background tile
				icons["tile_revealed"].sprite.setPosition(board->tiles.at(i)->position);
				window.draw(icons["tile_revealed"].sprite);
				// Number tile
				Icon numberTile = GetNumIcon(icons, board, board->tiles.at(i), window);
				numberTile.sprite.setPosition(board->tiles.at(i)->position);
				window.draw(numberTile.sprite);
				// Check for blank tile
				if (board->tiles.at(i)->numAdjacents == 0)
					BlankSquareClicked(icons, board, board->tiles.at(i), window);
			}
			// Mine
			else if (board->tiles.at(i)->isRevealed == true && board->tiles.at(i)->isMine == true)
			{
				// Grey background tile
				icons["tile_revealed"].sprite.setPosition(board->tiles.at(i)->position);
				window.draw(icons["tile_revealed"].sprite);
				// Mine tile
				icons["mine"].sprite.setPosition(board->tiles.at(i)->position);
				window.draw(icons["mine"].sprite);
			}
			i++;
		}
	}
}

void InitializeSmile(map<string, Icon> &icons, Board *board, sf::RenderWindow &window)
{
	if (board->lose == false && board->win == false)
	{
		icons["face_happy"].position = sf::Vector2f(368, 512);
		icons["face_happy"].sprite.setPosition(sf::Vector2f(368, 512));
		window.draw(icons["face_happy"].sprite);
	}
	else if (board->lose == false && board->win == true)
	{
		icons["face_win"].position = sf::Vector2f(368, 512);
		icons["face_win"].sprite.setPosition(sf::Vector2f(368, 512));
		window.draw(icons["face_win"].sprite);
	}
	else if (board->lose == true && board->win == false)
	{
		icons["face_lose"].position = sf::Vector2f(368, 512);
		icons["face_lose"].sprite.setPosition(sf::Vector2f(368, 512));
		window.draw(icons["face_lose"].sprite);
	}
}

void InitializeDebugs(map<string, Icon> &icons, Board *board, sf::RenderWindow &window)
{
	icons["debug"].sprite.setPosition(sf::Vector2f(496, 512));
	window.draw(icons["debug"].sprite);

	icons["test_1"].sprite.setPosition(sf::Vector2f(560, 512));
	window.draw(icons["test_1"].sprite);

	icons["test_2"].sprite.setPosition(sf::Vector2f(624, 512));
	window.draw(icons["test_2"].sprite);

	icons["test_3"].sprite.setPosition(sf::Vector2f(688, 512));
	window.draw(icons["test_3"].sprite);
}

void InitializeCounter(map<string, Icon> &icons, Board *board, sf::RenderWindow &window)
{
	int counter = board->numMines - board->numFlags;
	string counterStr = to_string(counter);
	int digits;
	if (abs(counter) > 99)
		digits = 3;
	else if (abs(counter) > 9)
		digits = 2;
	else
		digits = 1;
	int zeros = 3 - digits;
 
	// Negative sign if necessary
	if (counter < 0)
	{
		icons["digits"].sprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
		icons["digits"].sprite.setPosition(sf::Vector2f(0, 512));
		window.draw(icons["digits"].sprite);
		zeros--;
	}
	// Set zeros
	for (int i = 0; i < zeros; i++)
	{
		icons["digits"].sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
		if (counter < 0)
			icons["digits"].sprite.setPosition(sf::Vector2f(i * 21.0f + 21, 512.0f));
		else
			icons["digits"].sprite.setPosition(sf::Vector2f(i * 21.0f, 512.0f));
		window.draw(icons["digits"].sprite);
	}
	// Set digits
	for (int i = 0; i < digits; i++)
	{
		if (counter < 0)
			i++;

		int counterDigInt = counterStr[i] - '0';
		icons["digits"].sprite.setTextureRect(sf::IntRect(counterDigInt * 21, 0, 21, 32));

		if (counter < 0)
		{
			i--;
			icons["digits"].sprite.setPosition(sf::Vector2f((zeros * 21.0f) + (i * 21.0f) + 21, 512.0f));
		}
		else
			icons["digits"].sprite.setPosition(sf::Vector2f((zeros * 21.0f) + (i * 21.0f), 512.0f));

		window.draw(icons["digits"].sprite);
	}
}

Icon& GetNumIcon(map<string, Icon> &icons, Board *board, Tile *tile, sf::RenderWindow &window)
{
	if (tile->numAdjacents == 0)
		return icons["tile_revealed"];
	else if (tile->numAdjacents == 1)
		return icons["number_1"];
	else if (tile->numAdjacents == 2)
		return icons["number_2"];
	else if (tile->numAdjacents == 3)
		return icons["number_3"];
	else if (tile->numAdjacents == 4)
		return icons["number_4"];
	else if (tile->numAdjacents == 5)
		return icons["number_5"];
	else if (tile->numAdjacents == 6)
		return icons["number_6"];
	else if (tile->numAdjacents == 7)
		return icons["number_7"];
	else if (tile->numAdjacents == 8)
		return icons["number_8"];
	return icons["number_8"];
}

void BlankSquareClicked(map<string, Icon> &icons, Board *board, Tile *tile, sf::RenderWindow &window)
{
	for (int i = 0; i < 8; i++)
	{
		if (tile->adjacents.at(i) != nullptr && !tile->adjacents.at(i)->isRevealed 
			&& !tile->adjacents.at(i)->isFlagged)
		{
			tile->adjacents.at(i)->isRevealed = true;
			board->numRevealed++;
		}
	}
}

void DebugMode(Board *board)
{
	board->inDebugMode = true;
	for (int i = 0; i < 400; i++)
	{
		if (board->tiles.at(i)->isMine)
			board->tiles.at(i)->isRevealed = true;
	}
}
void RevertDebugMode(Board *board)
{
	board->inDebugMode = false;
	for (int i = 0; i < 400; i++)
	{
		if (board->tiles.at(i)->isRevealed && board->tiles.at(i)->isMine)
			board->tiles.at(i)->isRevealed = false;
	}
}

void RevealAllMines(Board *board)
{
	for (int i = 0; i < 400; i++)
	{
		if (board->tiles.at(i)->isRevealed == false && board->tiles.at(i)->isMine == true)
			board->tiles.at(i)->isRevealed = true;
	}
}

void FlagAllMines(Board *board)
{
	for (int i = 0; i < 400; i++)
	{
		if (board->tiles.at(i)->isFlagged == false && board->tiles.at(i)->isMine == true)
		{
			board->tiles.at(i)->isFlagged = true;
		}
	}
}

void CheckForWin(map<string, Icon> &icons, Board *board, sf::RenderWindow &window)
{
	if (board->numRevealed == board->numSafe)
	{
		board->win = true;
		RevealAllMines(board);
		FlagAllMines(board);
		InitializeCounter(icons, board, window);
	}
}