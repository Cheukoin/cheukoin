#include "Trick.h"

using namespace std;

Trick::Trick()
    : _cardValuesAsset({ { Seven, 0 }, { Eight, 0 }, { Nine, 14 }, { Ten, 10 }, { Jack, 20 }, { Queen, 3 }, { King, 4 }, { Ace, 11 } })
    , _cardValues({ { Seven, 0 }, { Eight, 0 }, { Nine, 0 }, { Ten, 10 }, { Jack, 2 }, { Queen, 3 }, { King, 4 }, { Ace, 11 } })
{
}

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
    _composition.push_back(card);
}

vector<Card> Trick::getComposition()
{
    return _composition;
}
