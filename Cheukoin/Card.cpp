#include "Card.h"
#include "ResourcePath.h"
#include <map>

using namespace std;

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
    _cardValues = {
        {Seven,0},
        {Eight,0},
        {Nine,0},
        {Ten,10},
        {Jack,2},
        {Queen,3},
        {King,4},
        {Ace,11}
    };
    
    _cardValuesAsset = {
        {Seven, 0},
        {Eight, 0},
        {Nine, 14},
        {Ten, 10},
        {Jack, 20},
        {Queen, 3},
        {King, 4},
        {Ace, 11},
    };
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

bool Card::isGreater(Card card, Suit suit) const
{
    
    
    if (_suit != suit && card.getSuit() == suit)
    {
        return false;
    }
    else if (_suit == suit && card.getSuit() != suit)
    {
        return true;
    }
    else
    {
        map <Value, int> order;
        
        if (card._suit == suit)
        {
            order = _cardValuesAsset;
        }
        else
        {
            order = _cardValues;
        }
        
        if (_value > card.getValue())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

