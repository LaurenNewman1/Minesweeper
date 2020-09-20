#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
using namespace std;
using namespace sf;

struct Icon
{
public:
	string name;
	Texture texture;
	Sprite sprite;
	Vector2f position;
	Icon();
	Icon(string filename);
};