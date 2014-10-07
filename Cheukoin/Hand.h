#pragma once
#include <vector>
#include "Card.h"

class Hand {
public:
    void removeCard();
    void addCard(Card card);
    std::vector<Card> getCards();
    bool isHandValid();

    Hand();
    ~Hand();

private:
    std::vector<Card> _cards;
};
