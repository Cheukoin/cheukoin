#pragma once
#include <vector>
#include "Card.h"

class Hand
{

private:
    std::vector<int, string> _cards;

public:
	void removeCard();
	void addCard(Card card);
	std::vector <int, string> getCards();
	bool isHandValid();
    Hand();
    ~Hand();
};


