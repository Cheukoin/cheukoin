#include "Card.h"
#include "ResourcePath.h"
#include <map>
#include <string>

using namespace std;

Card::Card(Suit suit, Value value)
    : textureBack(new sf::Texture())
    , _suit(suit)
    , _value(value)
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

Value Card::getValue() const
{
    return _value;
}


Suit Card::getSuit() const
{
    return _suit;
}

bool Card::isEqual(Card const& a) const
{
    return (a.getSuit() == _suit) && (a.getValue() == _value);
}

bool operator==(Card const& a, Card const& b)
{
    return a.isEqual(b);
}

string Card::toString()
{
    return "test";
}

