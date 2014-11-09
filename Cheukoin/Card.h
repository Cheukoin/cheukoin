#ifndef __Cheukoin_Card__
#define __Cheukoin_Card__

#include <math.h>
#include <iostream> // std::cout
#include <algorithm> // std::shuffle
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "Application.h"
#include "ResourcePath.h"
#include "AnimatedObject.h"

class Card : public AnimatedObject {
public:
    Card();
    Card(Suit suit, Value value);
    virtual ~Card();

    void bidCard();
    Value getValue() const;
    Suit getSuit() const;

    void flip();

    static std::vector<Card> getAllCards();
    static std::vector<Card> getAllCardsShuffled();

    bool isGreaterThan(Card other, Suit askedSuit) const;

    static const std::vector<std::string> SuitNames;
    static const std::vector<std::string> ValueNames;

private:
    Suit _suit;
    Value _value;

    std::string _getFilename();
};

bool operator==(Card const& a, Card const& b);
bool operator!=(Card const& a, Card const& b);

std::ostream& operator<<(std::ostream& os, const Card& card);

#endif