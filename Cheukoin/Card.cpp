#include "Card.h"

using namespace std;

vector<string> Card::SuitNames = {
    "clubs",
    "hearts",
    "diamonds",
    "spades"
};

vector<string> Card::ValueNames = {
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
    return ValueNames[_value] + "_of_" + SuitNames[_suit] + ".png";
}

void Card::moveTo(sf::Vector2u const& position)
{
// TODO : animate stuff
    //    auto pos = this->sprite->getPosition();
    //    float a = fabs((x - pos.x) / 10);
    //    float b = fabs(y - pos.y) / 10;
    //
    //    sf::Vector2i v(a, b);
    //    if (pos.y > y) {
    //        if (pos.x > x)
    //            this->sprite->setPosition(pos.x - v.x, pos.y - v.y);
    //        if (pos.x < x)
    //            this->sprite->setPosition(pos.x + v.x, pos.y - v.y);
    //    }
    //    else {
    //        if (pos.x > x)
    //            this->sprite->setPosition(pos.x - v.x, pos.y + v.y);
    //        else
    //            this->sprite->setPosition(pos.x + v.x, pos.y + v.y);
    //    }
    //
    //    if ((pos.x == x) && (pos.y == y)) {
    //        v.x = 0;
    //        v.y = 0;
    //        this->sprite->setPosition(pos.x, pos.y);
    //    }

    sprite->setPosition(position.x, position.y);
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

void Card::move()
{
    //    if (_position == Left)
    //        c.moveTo(300, 225);
    //    if (_position == Right)
    //        c.moveTo(400, 225);
    //    if (_position == Up)
    //        c.moveTo(350, 175);
    //    if (_position == Down)
    //        c.moveTo(350, 275);
}

Value Card::getValue() const
{
    return _value;
}

Suit Card::getSuit() const
{
    return _suit;
}

sf::Vector2u Card::getGlobalSize() const
{
    return sf::Vector2u(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height);
}

void Card::draw() const
{
    Application::getInstance().getWindow()->draw(*sprite.get());
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
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

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
