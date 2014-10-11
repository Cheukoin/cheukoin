#ifndef __Cheukoin_Hand__
#define __Cheukoin_Hand__

#include "Card.h"
#include <iostream>
enum Position {
    Left,
    Right,
    Up,
    Down
};

class Hand {
public:
    void removeCard(Card const& card);
    void addCard(Card const& card);
    std::vector<sf::Sprite> displayCards() const;
    std::vector<Card> getCards();
    bool isHandValid();

    Position getPosition(Hand hand) const;
    void setPosition(Hand hand);
    void turn(Hand hand, Position position);

    std::vector<Card> cardsForSuit(Suit suit);

    Hand(std::vector<Card> cards, Position position);
    ~Hand();
    Hand();

private:
    std::vector<Card> _cards;
    Position _position;
};

std::vector<Card> cardsForSuit(std::vector<Card> cards, Suit suit); //same as member function, but for any vector of cards (useful to analyse parts of hands, parts of tricks, etc...)

#endif
