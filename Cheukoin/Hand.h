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
    void displayCards(sf::RenderWindow& window) const;
    std::vector<Card> getCards();
    bool isHandValid();

    Position getPosition(Hand hand) const;
    void setPosition(Hand hand);
    //void turn(Hand hand, Position position);

    std::vector<Card> cardsForSuit(Suit suit);
    void move(Card c);
    void playOneCard(sf::RenderWindow& window, Card c);
    void playByClick(sf::RenderWindow& window);
    Hand(std::vector<Card> cards, Position position);
    ~Hand();
    Hand();
    bool cardRemoved();
    bool cardPlayed();

private:
    std::vector<Card> _cards;
    Position _position;
    bool _cardRemoved;
    bool _cardPlayed;
};

std::vector<Card> cardsForSuit(std::vector<Card> cards, Suit suit); //same as member function, but for any vector of cards (useful to analyse parts of hands, parts of tricks, etc...)

#endif
