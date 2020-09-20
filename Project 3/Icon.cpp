#include "Icon.h"
#include <iostream>
using namespace std;

Icon::Icon()
{
	name = "";
}

Icon::Icon(string filename)
{
	name = filename.substr(0, filename.size() - 4);
	texture.loadFromFile(filename);
	sprite.setTexture(texture);
}