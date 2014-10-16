#include "Hand.h"

Hand::Hand(std::vector<Card> cards, Position position)
    : _cards(cards)
    , _position(position)

{
#warning TODO : search another way WIP
    auto x = Game::getInstance().getWindow()->getSize().x;
    auto y = Game::getInstance().getWindow()->getSize().y;
    auto xnew = (x - (7 * _cards[0].sprite->getLocalBounds().height) / 50);
    switch (_position) {
    case Left:
        for (int i = 0; i < _cards.size(); i++) {
            _cards[i].sprite->setPosition(0, (i + 1) * y / 10);
        }
        break;

    case Right:
        for (int i = 0; i < _cards.size(); i++) {
            _cards[i].sprite->setRotation(_cards[i].sprite->getRotation() + 90);
            _cards[i].sprite->setPosition(xnew, (i + 1) * y / 10);
        }
        break;

    case Up:
        for (int i = 0; i < _cards.size(); i++) {
            _cards[i].sprite->setPosition(x / 10 * (1 + i), 0);
        }
        break;

    case Down:
        for (int i = 0; i < _cards.size(); i++) {
            _cards[i].sprite->setPosition(x / 10 * (1 + i), 9 * y / 10);
        }
        break;

    default:
        break;
    }

#warning TODO : search another way
}

Hand::~Hand()
{
}

Hand::Hand()
{
}

void Hand::playCard(Card card)
{
    int i = 0;
    if (_cards.size() != 0)
        for (i = 0; i < _cards.size(); i++)
            if (_cards[i] == card) {
                _cards[i].flip();
                _cards[i].move();
            }
}

void Hand::removeCard(Card const& card)
{
    int i = 0;
    if (_cards.size() != 0) {
        for (i = 0; i < _cards.size(); i++) {
            if (_cards[i] == card) {
                _cards.erase(_cards.begin() + i);
            }
        }
    }
}

void Hand::addCard(Card const& card)
{
    _cards.push_back(card);
}

std::vector<Card> Hand::getCards() const
{
    return _cards;
}

void Hand::draw() const
{

    for (Card card : _cards) {
        card.draw();
    }
}

Position Hand::getPosition() const
{
    return _position;
}
void Hand::setPosition(Position position)
{
    _position = position;
}

std::vector<Card> Hand::cardsForSuit(Suit suit)
{
#warning TODO : appeler l'equivalent ds rules
    std::vector<Card> cardsForSuit;
    for (auto c : _cards) {
        if (c.getSuit() == suit) {
            cardsForSuit.push_back(c);
        }
    }
    return cardsForSuit;
}
Hand& Hand::operator=(Hand const& hand)
{
    setPosition(hand.getPosition());
    _cards = hand.getCards();
}