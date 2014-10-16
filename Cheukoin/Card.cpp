#include "Card.h"

using namespace std;

Card::Card()
{
}

Card::Card(Suit suit, Value value)
    : texture(make_shared<sf::Texture>())
    , sprite(make_shared<sf::Sprite>())
    , _suit(suit)
    , _value(value)
    , _size(sf::Vector2u(500, 726))
{
    if (!texture->loadFromFile(resourcePath("cardBack.png"))) {
        puts("Texture file not loaded");
    }
    texture->setSmooth(true);
    sprite->setTextureRect(sf::IntRect(0, 0, _size.x, _size.y));
    sprite->setTexture(*texture);
    sprite->setScale(sf::Vector2f(0.3, 0.3));
}

Card::~Card()
{
}

std::string Card::_getFilename()
{
    std::vector<std::string> suits = {
        "clubs",
        "hearts",
        "diamonds",
        "spades"
    };
    std::vector<std::string> values = {
        "ace",
        "king",
        "queen",
        "jack",
        "10",
        "9",
        "8",
        "7"
    };

    return values[_value] + "_of_" + suits[_suit] + ".png";
}

void Card::moveTo(float x, float y)
{
#warning TODO : animate stuff
    auto pos = this->sprite->getPosition();
    float a = fabs((x - pos.x) / 10);
    float b = fabs(y - pos.y) / 10;

    sf::Vector2i v(a, b);
    if (pos.y > y) {
        if (pos.x > x)
            this->sprite->setPosition(pos.x - v.x, pos.y - v.y);
        if (pos.x < x)
            this->sprite->setPosition(pos.x + v.x, pos.y - v.y);
    }
    else {
        if (pos.x > x)
            this->sprite->setPosition(pos.x - v.x, pos.y + v.y);
        else
            this->sprite->setPosition(pos.x + v.x, pos.y + v.y);
    }

    if ((pos.x == x)
        && (pos.y == y)) {
        v.x = 0;
        v.y = 0;
        this->sprite->setPosition(pos.x, pos.y);
    }
}

sf::Texture Card::getTexture() const
{
    return *texture;
}

void Card::flip()
{
    std::string str = _getFilename();
    if (!texture->loadFromFile(resourcePath(str))) {
        // handle texture not loaded
        puts("Texture file not loaded");
    }

    sprite->setTextureRect(sf::IntRect(0, 0, _size.x, _size.y));
    sprite->setTexture(*texture);
    sprite->setScale(sf::Vector2f(0.3, 0.3));
}

Value Card::getValue() const
{
    return _value;
}

Suit Card::getSuit() const
{
    return _suit;
}

void Card::draw() const
{
    Game::getInstance().getWindow()->draw(*sprite.get());
}

vector<Card> Card::getAllCardsShuffled()
{
    vector<Card> cards;
    for (int suit = 0; suit < 4; suit++) {
        for (int value = 0; value < 8; value++) {
            cards.push_back(Card((Suit)suit, (Value)value));
        }
    }

    random_shuffle(cards.begin(), cards.end());

    return cards;
}

bool operator==(Card const& a, Card const& b)
{
    return (a.getSuit() == b.getSuit()) && (a.getValue() == b.getValue());
}

bool operator!=(Card const& a, Card const& b)
{
    return !(a == b);
}

ostream& operator<<(ostream& os, const Card& card)
{
    os << "<Card suit: " << card.getSuit() << ", value: " << card.getValue() << ">";
    return os;
}
