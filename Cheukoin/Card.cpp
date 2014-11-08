#include "Card.h"

using namespace std;

vector<string> const Card::SuitNames = {
    "clubs",
    "hearts",
    "diamonds",
    "spades"
};

vector<string> const Card::ValueNames = {
    "ace",
    "king",
    "queen",
    "jack",
    "10",
    "9",
    "8",
    "7"
};

Card::Card()
    : AnimatedObject()
{
    if (!_texture->loadFromFile(resourcePath("cardBack.png"))) {
        puts("_texture file not loaded");
    }
    _texture->setSmooth(true);
    _sprite->setTextureRect(sf::IntRect(0, 0, _size.x, _size.y));
    _sprite->setTexture(*_texture);
    _sprite->setScale(sf::Vector2f(0.3, 0.3));

    _size = sf::Vector2f(500, 726);
}

Card::Card(Suit suit, Value value)
    : AnimatedObject()
    , _suit(suit)
    , _value(value)
{
    if (!_texture->loadFromFile(resourcePath("cardBack.png"))) {
        puts("_texture file not loaded");
    }
    _texture->setSmooth(true);
    _sprite->setTextureRect(sf::IntRect(0, 0, _size.x, _size.y));
    _sprite->setTexture(*_texture);
    _sprite->setScale(sf::Vector2f(0.3, 0.3));

    _size = sf::Vector2f(500, 726);
}

Card::~Card()
{
}

void Card::bidCard()
{
    if (!_texture->loadFromFile(resourcePath("c.png"))) {
        puts("_texture file not loaded");
    }
    sf::Vector2u winSize = Application::getInstance().getWindow()->getSize();
    _texture->setSmooth(true);
    _sprite->setTextureRect(sf::IntRect(0, 0, 960, 720));
    _sprite->setTexture(*_texture);
    sf::Vector2u pos = sf::Vector2u(winSize.x / 3, winSize.y / 3);
    _sprite->setPosition(pos.x, pos.y);
}

std::string Card::_getFilename()
{
    return ValueNames[_value] + "_of_" + SuitNames[_suit] + ".png";
}

void Card::flip()
{
    std::string str = _getFilename();
    if (!_texture->loadFromFile(resourcePath(str))) {
        // handle _texture not loaded
        puts("_texture file not loaded");
    }

    _sprite->setTextureRect(sf::IntRect(0, 0, _size.x, _size.y));
    _sprite->setTexture(*_texture);
    _sprite->setScale(sf::Vector2f(0.3, 0.3));
}

Value Card::getValue() const
{
    return _value;
}

Suit Card::getSuit() const
{
    return _suit;
}

vector<Card> Card::getAllCards()
{
    vector<Card> cards;
    for (int suit = 0; suit < 4; suit++) {
        for (int value = 0; value < 8; value++) {
            cards.push_back(Card((Suit)suit, (Value)value));
        }
    }
    return cards;
}

vector<Card> Card::getAllCardsShuffled()
{
    vector<Card> cards = getAllCards();

    // initialize pseudo random number genrator
    unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());

    // actually shuffle the cards
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));

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
    os << "<Card: "
       << Card::ValueNames[card.getValue()]
       << " of "
       << Card::SuitNames[card.getSuit()]
       << ">";

    return os;
}
