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

std::vector<Card> Hand::cardsForSuit(Suit suit)
{
    std::vector<Card> cardsForSuit;
    for (auto c : _cards) {
        if (c.getSuit() == suit) {
            cardsForSuit.push_back(c);
        }
    }
    return cardsForSuit;
}

std::vector<Card> cardsForSuit(std::vector<Card> cards, Suit suit)
{
    std::vector<Card> cardsForSuit;
    for (auto c : cards) {
        if (c.getSuit() == suit) {
            cardsForSuit.push_back(c);
        }
    }
    return cardsForSuit;
}
