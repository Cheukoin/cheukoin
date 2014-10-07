#include "Trick.h"
using namespace std;

Trick::Trick()
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