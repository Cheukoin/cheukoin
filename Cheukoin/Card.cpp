#include "Card.h"
#include "Rules.h"

using namespace std;

Card::Card()
    : AnimatedObject("cardBack.png", sf::Vector2f(150, 218))
    , _shown(false)
{
}

Card::Card(Suit suit, Value value)
    : AnimatedObject("cardBack.png", sf::Vector2f(150, 218))
    , _suit(suit)
    , _value(value)
    , _shown(false)
{
}

Card::~Card()
{
}

std::string Card::_getFilename()
{
    return ValueNames.at(_value) + "_of_" + SuitNames.at(_suit) + ".png";
}

void Card::show()
{
    if (_shown) {
        return;
    }

    std::string str = _getFilename();
    if (!_texture->loadFromFile(resourcePath(str))) {
        // handle _texture not loaded
        puts("_texture file not loaded");
    }
    _sprite->setTexture(*_texture);

    _shown = true;
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

bool Card::isGreaterThan(Card other, Suit askedSuit) const
{
    Suit asset = Application::getInstance().getGame()->getRules()->getAsset();
    if (_suit != asset && other.getSuit() == asset) {
        return false;
    }
    else if (_suit == asset && other.getSuit() != asset) {
        return true;
    }
    else if (_suit != askedSuit && other.getSuit() == askedSuit) {
        return false;
    }
    else if (_suit == askedSuit && other.getSuit() != askedSuit) {
        return true;
    }
    else if (_suit != other.getSuit()) {
        return true;
    }
    else {
        // 2 cards are from same suit
        map<Value, int> order = _suit == asset ? Rules::CardValuesAsset : Rules::CardValues;
        if (order[_value] == order[other.getValue()]) {
            return (int)_value < (int)other.getValue();
        }
        return order[_value] > order[other.getValue()];
    }
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
       << ValueNames.at(card.getValue())
       << " of "
       << SuitNames.at(card.getSuit())
       << ">";

    return os;
}
