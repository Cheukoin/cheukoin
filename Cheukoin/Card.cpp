#include "Card.h"
#include "ResourcePath.h"

Card::Card():
textureBack(new sf::Texture())
{
	if (!textureBack->loadFromFile(resourcePath("cardBack.png"))) {
		// handle texture not loaded
		puts("Texture file not loaded");
	}

	sprite.setTextureRect(sf::IntRect(0, 0, 342, 480));
	sprite.setTexture(*textureBack);
	sprite.setScale(sf::Vector2f(0.3, 0.3));
}


Card::~Card()
{
	puts("Card destroyed");
}

