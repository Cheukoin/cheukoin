#include "Card.h"
#include "ResourcePath.h"

Card::Card()
    : textureBack(new sf::Texture())
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

bool Card::isEqual(Card const& a) const
{
    if ((a.suit == suit) && (a.value == value))
        return true;
    else
        return false;
}

bool operator==(Card const& a, Card const& b)
{
    if (a.isEqual(b))
        return true;
    else
        return false;
}