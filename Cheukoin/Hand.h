#pragma once
#include <vector>
#include "Card.h"

class Hand {
public:
    void removeCard();
    void addCard(Card card);
    std::vector<std::pair<int, std::string> > getCards();
    bool isHandValid();

    Hand();
    ~Hand();

private:
    std::vector<std::pair<int, std::string> > _cards;
};
