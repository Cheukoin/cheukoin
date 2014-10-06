#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

using namespace std;


class Card
{
public:
	string name;
	sf::Sprite sprite;
	shared_ptr<sf::Texture> textureBack;

	void playCard();
	void makeBid();

	Card();
	~Card();
};

