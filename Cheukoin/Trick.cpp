#include "Trick.h"
using namespace std;

Trick::Trick()
{
}

Trick::Trick(int number, Bid bid): _number(number), _bid(bid)
{
    
}

Trick::~Trick()
{
}

void Trick::setNumber(int number)
{
    _number=number;
}

int Trick::getNumber()
{
    return _number;
}

void Trick::addCard(Card const& card)
{
    _composition.push_back(card);
}

vector<Card> Trick::getComposition()
{
    return _composition;
}

Card Trick::winningCard()
{
    Card max = _composition[0];
    for (int i = 0; i < _composition.size(); i++)
    {
        if (_composition[i].isGreater(max, _bid.getSuit()))
        {
            max = _composition[i];
        }
    }
    return max;
}