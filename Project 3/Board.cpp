#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <fstream>
#include "Board.h"
using namespace std;

Board::Board()
{
	win = false;
	lose = false;
	inDebugMode = false;
	numFlags = 0;
	numRevealed = 0;
	numSafe = 350;
	numMines = 50;
	// Create 400 tiles
	for (int i = 0; i < 400; i++)
	{
		Tile *newTile = new Tile;
		tiles.push_back(newTile);
	}
	// Randomly select 50 to be mines
	vector<int> used;
	for (int i = 0; i < 50; i++)
	{
		int random = rand() % 400;
		if (find(used.begin(), used.end(), random) != used.end())
			i--;
		else
		{
			tiles.at(random)->isMine = true;
			used.push_back(random);
		}
	}
	SetEdges();
	SetPointers();
	SetAdjacents();
}

Board::Board(string filename)
{
	win = false;
	lose = false;
	inDebugMode = false;
	numFlags = 0;
	numRevealed = 0;
	numSafe = 0;
	numMines = 0;

	for (int i = 0; i < 400; i++)
	{
		Tile *newTile = new Tile;
		tiles.push_back(newTile);
	}

	ifstream file(filename);
	string line;
	string binary = "";

	if (file.is_open())
	{
		while (getline(file, line))
		{
			binary = binary + line;
		}

		for (int i = 0; i < 400; i++)
		{
			if (binary[i] == '1')
			{
				tiles.at(i)->isMine = true;
				numMines++;
			}
		}
		numSafe = 400 - numMines;
		file.close();
	}
	SetEdges();
	SetPointers();
	SetAdjacents();
}

void Board::SetPointers()
{
	// Create pointers to adjacent tiles
	for (int i = 0; i < 400; i++)
	{
		int topLeft = i - 26;
		int top = i - 25;
		int topRight = i - 24;
		int right = i + 1;
		int botRight = i + 26;
		int bot = i + 25;
		int botLeft = i + 24;
		int left = i - 1;

		if (topLeft >= 0 && topLeft <= 399 && !tiles.at(i)->onLeftEdge)
			tiles.at(i)->adjacents.push_back(tiles.at(topLeft));
		else
			tiles.at(i)->adjacents.push_back(nullptr);
		if (top >= 0 && top <= 399)
			tiles.at(i)->adjacents.push_back(tiles.at(top));
		else
			tiles.at(i)->adjacents.push_back(nullptr);
		if (topRight >= 0 && topRight <= 399 && !tiles.at(i)->onRightEdge)
			tiles.at(i)->adjacents.push_back(tiles.at(topRight));
		else
			tiles.at(i)->adjacents.push_back(nullptr);
		if (right >= 0 && right <= 399 && !tiles.at(i)->onRightEdge)
			tiles.at(i)->adjacents.push_back(tiles.at(right));
		else
			tiles.at(i)->adjacents.push_back(nullptr);
		if (botRight >= 0 && botRight <= 399 && !tiles.at(i)->onRightEdge)
			tiles.at(i)->adjacents.push_back(tiles.at(botRight));
		else
			tiles.at(i)->adjacents.push_back(nullptr);
		if (bot >= 0 && bot <= 399)
			tiles.at(i)->adjacents.push_back(tiles.at(bot));
		else
			tiles.at(i)->adjacents.push_back(nullptr);
		if (botLeft >= 0 && botLeft <= 399 && !tiles.at(i)->onLeftEdge)
			tiles.at(i)->adjacents.push_back(tiles.at(botLeft));
		else
			tiles.at(i)->adjacents.push_back(nullptr);
		if (left >= 0 && left <= 399 && !tiles.at(i)->onLeftEdge)
			tiles.at(i)->adjacents.push_back(tiles.at(left));
		else
			tiles.at(i)->adjacents.push_back(nullptr);
	}
}

void Board::SetAdjacents()
{
	// Determine how many adjacent mines
	for (int i = 0; i < 400; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tiles.at(i)->adjacents.at(j) != nullptr && tiles.at(i)->adjacents.at(j)->isMine == true)
				tiles.at(i)->numAdjacents++;
		}
	}
}

void Board::SetEdges()
{
	for (int i = 0; i < 400; i += 25)
		tiles.at(i)->onLeftEdge = true;
	for (int i = 24; i < 400; i += 25)
		tiles.at(i)->onRightEdge = true;
}