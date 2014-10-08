#pragma once
#include <vector>
#include "Card.h"

class Trick
{
public:
	Trick();
    Trick(int number);
	~Trick();
    void setNumber(int number);
    int getNumber();
    void addCard(Card const& Card);
    std::vector<Card> getComposition();
    Card winningCard(Suit const& suit);
    
    
private:
    int _number;
    std::vector<Card> _composition;
};

