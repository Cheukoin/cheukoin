#include "Trick.h"

using namespace std;

Trick::Trick(int number)
    : _number(number)
{
}

Trick::~Trick()
{
}

void Trick::setNumber(int number)
{
    _number = number;
}

int Trick::getNumber()
{
    return _number;
}

void Trick::addCard(Card const& card)
{
    _cards.push_back(card);
}

vector<Card> Trick::getCards()
{
    return _cards;
}
