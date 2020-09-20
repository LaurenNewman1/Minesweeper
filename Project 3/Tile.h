#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace sf;

struct Tile
{
public:
	bool isMine;
	bool isFlagged;
	bool isRevealed;
	bool onLeftEdge;
	bool onRightEdge;
	vector<Tile*> adjacents;
	Vector2f position;
	int numAdjacents;
	Tile();
	Tile(bool isMine);
};
