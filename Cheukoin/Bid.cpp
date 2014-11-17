#include "Bid.h"

using namespace std;

Bid::Bid(Suit suit, int amount, string playerName)
    : _suit(suit)
    , _amount(amount)
    , _playerName(playerName)
{
}
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

string Bid::getPlayerName()
{
    return _playerName;
}
