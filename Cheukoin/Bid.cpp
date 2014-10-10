#include "Bid.h"

Bid::Bid()
{
}

Bid::~Bid()
{
}

int Bid::getAmount()
{
    return _amount;
}

void Bid::setAmount(int amount)
{
    _amount = amount;
}

void Bid::setSuit(Suit suit)
{
    _suit = suit;
}

Suit Bid::getSuit()
{
    return _suit;
}

bool Bid::isBidValid(Bid previousBid)
{
    return false;
}
