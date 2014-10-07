#pragma once
#include <vector>
#include "Card.h"

class Trick
{
public:
	Trick();
	~Trick();
    void setNumber(int number);
    int getNumber();
    void addCard(Card const& Card);
    std::vector<Card> getComposition();
    
    
private:
    int _number;
    std::vector<Card> _composition;
};

