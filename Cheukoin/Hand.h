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
    Hand(std::vector<Card> cards, Position position);
    ~Hand();
    Hand();
#warning TODO : to be removed when instanciated in Player

    void addCard(Card const& card);
    void removeCard(Card const& card);
    std::vector<Card> getCards();

    void draw() const;

    Position getPosition(Hand hand) const;
    void setPosition(Hand hand);

    std::vector<Card> cardsForSuit(Suit suit);
    void playCard(sf::RenderWindow& window, Card card);
#warning TODO : plus besoin de window
    
#warning TODO : rien a foutre ds hand + pas besoind e window

#warning TODO : bouge le dans card
    void moveToTrick(Card c);
    void move(Card c);

private:
    std::vector<Card> _cards;
    Position _position;
};

#endif
