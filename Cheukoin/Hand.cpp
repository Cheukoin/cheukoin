#include "Hand.h"

Hand::Hand(): _cards()
{
}

Hand::~Hand()
{
}

void Hand::removeCard(Card const& card)
{
    int i = 0;
    if (_cards.size()!=0)
        for (i;i< _cards.size() ;i++)
            if ( _cards[i] == card)
                _cards.erase(_cards.begin()+i);
}

void Hand::addCard(Card const& card)
{
    _cards.push_back(card);
}


