#include "Card.h"

using namespace std;

Card::Card(Suit suit, Value value)
    : _texture(sf::Texture())
    , _suit(suit)
    , _value(value)
    , sprites(new sf::Sprite())
{
    if (!_texture.loadFromFile(resourcePath("cardBack.png"))) {
        // handle texture not loaded
        puts("Texture file not loaded");
    }
    sprites->setTextureRect(sf::IntRect(0, 0, 342, 480));
    sprites->setTexture(_texture);
    sprites->setScale(sf::Vector2f(0.3, 0.3));
}

Card::~Card()
{
}
void Card::changeTexture(sf::Texture texture2)
{
    _texture = texture2;
    _sprite.setTexture(_texture);
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
    sprites->setTextureRect(sf::IntRect(0, 0, 342, 480));
    sprites->setTexture(_texture);
    sprites->setScale(sf::Vector2f(0.3, 0.3));
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

bool operator!=(Card const& a, Card const& b)
{
    return not(a.isEqual(b));
}

float Card::getLeft()
{
    auto pos = this->sprites->getPosition();
    sf::Vector2f size(342, 480);
    sf::FloatRect rect(pos, size);
    return rect.left;
}
float Card::getRight()
{
    auto pos = this->sprites->getPosition();
    sf::Vector2f size(342, 480);
    sf::FloatRect rect(pos, size);
    return rect.left + 50;
}
float Card::getTop()
{
    auto pos = this->sprites->getPosition();
    sf::Vector2f size(342, 480);
    sf::FloatRect rect(pos, size);
    return rect.top;
}
float Card::getBottom()
{
    auto pos = this->sprites->getPosition();
    sf::Vector2f size(342, 480);
    sf::FloatRect rect(pos, size);
    return rect.height + rect.top;
}
ostream& operator<<(ostream& os, const Card& card)
{
    os << "<Card suit: " << card.getSuit() << ", value: " << card.getValue() << ">";
    return os;
}

sf::Sprite Card::getSprite()
{
    return _sprite;
}

void Card::displayCard(sf::RenderWindow& window)
{
    window.draw(_sprite);
}
