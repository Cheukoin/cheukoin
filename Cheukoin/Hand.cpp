#include "Hand.h"

Hand::Hand()
    : _cards()
{
}

Hand::~Hand()
{
}

void Hand::removeCard(Card const& card)
{
    int i = 0;
    if (_cards.size() != 0)
        for (i = 0; i < _cards.size(); i++)
            if (_cards[i] == card)
                _cards.erase(_cards.begin() + i);
}

void Hand::addCard(Card const& card)
{
    _cards.push_back(card);
}

bool Hand::isHandValid()
{
    return (_cards.size() <= 8);
}

std::vector<Card> Hand::getCards()
{
    return _cards;
}

void Hand::displayCards(std::ostream& flux) const
{
    int i = 0;
    for (i = 0; i < _cards.size(); i++) {
        flux << &_cards[i];
    }
}

std::ostream& operator<<(std::ostream& flux, Hand const& hand)
{
    hand.displayCards(flux);
    return flux;
}
