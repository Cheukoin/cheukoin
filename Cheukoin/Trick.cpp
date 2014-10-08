#include "Trick.h"
using namespace std;

Trick::Trick(): _cardValuesAsset({{Seven, 0}, {Eight, 0}, {Nine, 14}, {Ten, 10}, {Jack, 20}, {Queen, 3}, {King, 4}, {Ace, 11}}), _cardValues({{Seven,0},{Eight,0},{Nine,0},{Ten,10},{Jack,2},{Queen,3},{King,4},{Ace,11}})
{
    
}

Trick::Trick(int number): _number(number)
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

bool Trick::isGreater(Card card1, Card card2, Suit suit) const //greater meaning beats (takes asset's cut into account)
{
    
    
    if (card1.getSuit() != suit && card2.getSuit() == suit)
    {
        return false;
    }
    else if (card1.getSuit() == suit && card2.getSuit() != suit)
    {
        return true;
    }
    else
    {
        map <Value, int> order;
        
        if (card1.getSuit() == suit)
        {
            order = _cardValuesAsset;
        }
        else
        {
            order = _cardValues;
        }
        
        if (card1.getValue() > card2.getValue())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}


Card Trick::winningCard(Suit const& suit)
{
    Card max = _composition[0];
    for (int i = 0; i < _composition.size(); i++)
    {
        if (isGreater(_composition[i], max, suit))
        {
            max = _composition[i];
        }
    }
    return max;
}