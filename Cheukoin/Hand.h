#ifndef __Cheukoin_Hand__
#define __Cheukoin_Hand__

#include "Card.h"

class Hand {
public:
    void removeCard(Card const& card);
    void addCard(Card const& card);
    void displayCards(std::ostream& flux) const;
    std::vector<Card> getCards();
    bool isHandValid();
    std::vector<Card> cardsForSuit(Suit suit);

    Hand();
    ~Hand();

private:
    std::vector<Card> _cards;
};

std::ostream& operator<<(std::ostream& flux, Hand const& hand);
std::vector<Card> cardsForSuit(std::vector<Card> cards, Suit suit); //same as member function, but for any vector of cards (useful to analyse parts of hands, parts of tricks, etc...)

#endif