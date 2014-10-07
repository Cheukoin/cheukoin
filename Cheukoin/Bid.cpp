#include "Bid.h"
using namespace std;



Bid::Bid()
{
}


Bid::~Bid()
{
}

Value Bid::getValue()
{
    return _value;
}

void Bid::setValue(Value value)
{
    _value=value;
}

void Bid::setSuit(Suit suit)
{
    _suit=suit;
}

Suit Bid::getSuit()
{
    return _suit;
}

bool Bid::isBidValid(Bid previousBid)
{
    
}





