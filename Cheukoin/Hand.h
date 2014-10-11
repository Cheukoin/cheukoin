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

    Hand(std::vector<Card> cards, Position position);
    ~Hand();
    Hand();

private:
    std::vector<Card> _cards;
    Position _position;
};

#endif
