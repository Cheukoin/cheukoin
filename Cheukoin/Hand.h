#ifndef __Cheukoin_Hand__
#define __Cheukoin_Hand__

#include "Card.h"
#include <iostream>
#include <algorithm>
#include "Game.h"

enum Position {
    Left,
    Right,
    Up,
    Down
};

class Hand {
public:
    Hand(std::vector<Card> cards, Position position);
    ~Hand();
    Hand();
#warning TODO : to be removed when instanciated in Player

    void addCard(Card const& card);
    void removeCard(Card const& card);
    std::vector<Card> getCards() const;

    void draw() const;

    Position getPosition() const;
    void setPosition(Position position);

    std::vector<Card> cardsForSuit(Suit suit);
    void playCard(Card card);
    Hand& operator=(Hand const& hand);

private:
    std::vector<Card> _cards;
    Position _position;
};

#endif
