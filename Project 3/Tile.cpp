#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Tile.h"
using namespace std;

Tile::Tile()
{
	isMine = false;
	isRevealed = false;
	isFlagged = false;
	onLeftEdge = false;
	onRightEdge = false;
	numAdjacents = 0;
}

Tile::Tile(bool isMine)
{
	this->isMine = isMine;
	isRevealed = false;
	isFlagged = false;
	onLeftEdge = false;
	onRightEdge = false;
	numAdjacents = 0;
}