#pragma once
#include <vector>
#include "Card.h"

class Hand {
public:
    void removeCard(Card const& card);
    void addCard(Card const& card);
    std::vector<Card> getCards();
    bool isHandValid();

    Hand();
    ~Hand();

private:
    std::vector<Card> _cards;
};
