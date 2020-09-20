#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Tile.h"
#include <vector>
using namespace std;

struct Board
{
public:
	bool win;
	bool lose;
	bool inDebugMode;
	int numFlags;
	int numRevealed;
	int numSafe;
	int numMines;
	vector<Tile*> tiles;
	Board();
	Board(string filename);
	void SetPointers();
	void SetEdges();
	void SetAdjacents();
};
