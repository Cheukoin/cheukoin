#include "Card.h"
#include "ResourcePath.h"
#include <map>
#include <string>

using namespace std;

Card::Card(Suit suit, Value value)
    : _texture(sf::Texture())
    , _suit(suit)
    , _value(value)
    , sprites2(new sf::Sprite())
{
    if (!_texture.loadFromFile(resourcePath("cardBack.png"))) {
        // handle texture not loaded
        puts("Texture file not loaded");
    }
    sprites2->setTextureRect(sf::IntRect(0, 0, 342, 480));
    sprites2->setTexture(_texture);
    sprites2->setScale(sf::Vector2f(0.3, 0.3));
}

Card::~Card()
{
}
void Card::changeTexture(sf::Texture texture2)
{
    _texture = texture2;
}
sf::Texture Card::getTexture() const
{
    return _texture;
}

void Card::turn()
{
    sf::Texture test;
    std::string str;
    str = "ClubsNine.png"; //getFileName

    if (!test.loadFromFile(resourcePath(str))) {
        // handle texture not loaded
        puts("Texture file not loaded");
    }
    this->changeTexture(test);
    sprites2->setTextureRect(sf::IntRect(0, 0, 342, 480));
    sprites2->setTexture(_texture);
    sprites2->setScale(sf::Vector2f(0.3, 0.3));
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

ostream& operator<<(ostream& os, const Card& card)
{
    os << "<Card suit: " << card.getSuit() << ", value: " << card.getValue() << ">";
    return os;
}
