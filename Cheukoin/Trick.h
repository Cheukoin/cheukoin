#pragma once
#include <vector>
#include "Card.h"
#include "Bid.h"

class Trick
{
public:
	Trick();
    Trick(int number, Bid bid);
	~Trick();
    void setNumber(int number);
    int getNumber();
    void addCard(Card const& Card);
    std::vector<Card> getComposition();
    Card winningCard();
    
    
private:
    int _number;
    std::vector<Card> _composition;
    Bid _bid;
};

