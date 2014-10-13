#include "Card.h"
#include <math.h>
using namespace std;

Card::Card(Suit suit, Value value)
    : _texture(new sf::Texture())
    , _suit(suit)
    , _value(value)
    , sprites(new sf::Sprite())
{
    if (!_texture->loadFromFile(resourcePath("cardBack.png"))) {
        // handle texture not loaded
        puts("Texture file not loaded");
    }
    sprites->setTextureRect(sf::IntRect(0, 0, 342, 480));
    sprites->setTexture(*_texture);
    sprites->setScale(sf::Vector2f(0.3, 0.3));
}

Card::~Card()
{
}
std::string Card::getFileName(Card& c)
{
    string str;
    str = to_string(_suit) + to_string(_value) + ".png";
    return str;
}
void Card::moveTo(float x, float y)
{

    auto pos = this->sprites->getPosition();
    float a = fabs((x - pos.x) / 10);
    float b = fabs(y - pos.y) / 10;

    sf::Vector2i v(a, b);
    if (pos.y > y) {
        if (pos.x > x)
            this->sprites->setPosition(pos.x - v.x, pos.y - v.y);
        if (pos.x < x)
            this->sprites->setPosition(pos.x + v.x, pos.y - v.y);
    }
    else {
        if (pos.x > x)
            this->sprites->setPosition(pos.x - v.x, pos.y + v.y);
        else
            this->sprites->setPosition(pos.x + v.x, pos.y + v.y);
    }
    if ((pos.x == x)
        && (pos.y == y)) {
        v.x = 0;
        v.y = 0;
        this->sprites->setPosition(pos.x, pos.y);
    }
}

sf::Texture Card::getTexture() const
{
    return *_texture;
}

void Card::turn()
{
    std::string str = getFileName(*this);
    if (!_texture->loadFromFile(resourcePath(str))) {
        // handle texture not loaded
        puts("Texture file not loaded");
    }

    sprites->setTextureRect(sf::IntRect(0, 0, 342, 480));
    sprites->setTexture(*_texture);
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
    if ((pos.x < 100) || (pos.x > 700)) {
        return rect.left + rect.width;
    }
    else
        return rect.left + 40;
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
    if ((pos.x < 100) || (pos.x > 700)) {
        return rect.top + 40;
    }
    else {
        return rect.height + rect.top;
    }
}
ostream& operator<<(ostream& os, const Card& card)
{
    os << "<Card suit: " << card.getSuit() << ", value: " << card.getValue() << ">";
    return os;
}
